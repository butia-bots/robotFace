#!/usr/bin/env python3

from __future__ import division
import rospy
import time
import threading
from std_msgs.msg import (Int16MultiArray, Int16)
import map as mp

# Define normal statics parameters
h = 50
frequency = 3.5

EMOTIONS = {
    "standard": 0,
    "happy": 1,
    "sad": 2,
    "rage": 3,
    "scared": 4,
}

class eyelidEnable():
    def __init__(self):
        rospy.init_node('eyelidEnable', anonymous=False)
        pub = rospy.Publisher('eyelid', Int16MultiArray, queue_size=10)

        self.sub_eyelid_st = rospy.Subscriber('emotion', Int16, self.getEyelid_st)
        # self.sub_eyelid_dn = Int16MultiArray()
        # self.sub_eyelid_dn.data = []   
        # self.sub_eyelid_dn = rospy.Subscriber('eye', Int16MultiArray, self.getEyelid_dn)
        
        rate = rospy.Rate(30)

        # Define the output vector
        self.output = Int16MultiArray()
        self.output.data = []

        self.y = 50
        self.animation = 0
        self.upper = 0
        self.down = 0

        self._readParameters()

        # Start blink thread
        blinkLoop = threading.Thread(name = 'blink', target = eyelidEnable.blink, args = (self,))
        blinkLoop.setDaemon(True)
        blinkLoop.start()

        while not rospy.is_shutdown():
            self.getOutput()
            pub.publish(self.output)
            rate.sleep()
        
    def getOutput(self):
        if (self.animation == 1):
            pass
        elif(self.animation == 0): 
            self.setValues()
    
    def setValues(self):
        if(self.y > 50):
            self.upper = (h + self.y*2 - 140)
            self.down = 140
            self.output.data = [self.upper, self.upper, self.down, self.down]
        elif(self.y < 50):
            self.upper = h
            self.down = 140 - (h + self.y)
            self.output.data = [self.upper, self.upper, self.down, self.down]
        elif(self.y == 50):
            self.upper = 100-h
            self.down = 100-h
            self.output.data = [self.upper, self.upper, self.down, self.down]

    def getEyelid_dn(self, msg):
        self.data = msg.data
        self.y = 50

    def getEyelid_st(self, msg):
        global h
        global frequency
        self.data = msg.data
        if(self.data == EMOTIONS["standard"]):
            h = self.h_standard_params
            frequency = self.frequency_standard_params
        elif(self.data == EMOTIONS["happy"]):
            h = self.h_happy_params 
            frequency = self.frequency_happy_params 
        elif(self.data == EMOTIONS["sad"]):   
            h = self.h_sad_params
            frequency = self.frequency_sad_params
        elif(self.data == EMOTIONS["rage"]):
            h = self.h_rage_params
            frequency = self.frequency_rage_params
        elif(self.data == EMOTIONS["scared"]):  
            h = self.h_scared_params
            frequency = self.frequency_scared_params

    def _readParameters(self):
        self.h_standard_params = rospy.get_param("butia_emotions/eyelid/standard/h")
        self.frequency_standard_params = rospy.get_param("butia_emotions/eyelid/standard/frequency")

        self.h_happy_params = rospy.get_param("butia_emotions/eyelid/happy/h")
        self.frequency_happy_params = rospy.get_param("butia_emotions/eyelid/happy/frequency")

        self.h_sad_params = rospy.get_param("butia_emotions/eyelid/sad/h")
        self.frequency_sad_params = rospy.get_param("butia_emotions/eyelid/sad/frequency")

        self.h_rage_params = rospy.get_param("butia_emotions/eyelid/rage/h")
        self.frequency_rage_params = rospy.get_param("butia_emotions/eyelid/rage/frequency")

        self.h_scared_params = rospy.get_param("butia_emotions/eyelid/scared/h")
        self.frequency_scared_params = rospy.get_param("butia_emotions/eyelid/scared/frequency")

        self.frequency_blink = rospy.get_param("butia_emotions/eyelid/blink/frequency")
    
    def blink(self):
        while(True):
            time.sleep(0.3)
            self.output.data = [100, 100, 100, 100]
            self.animation = 1
            time.sleep(0.3)
            self.setValues()
            self.animation = 0
            
            time.sleep(self.frequency_blink)  
            

if __name__ == '__main__':
    try:
        eyelidEnable()
    except rospy.ROSInterruptException:
        pass