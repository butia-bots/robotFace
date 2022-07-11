#include "motor.h"
#include "thread.h"

#include <DynamixelProtocol.h>
#include <Servo.h>

#define ID 128
#define BAUDRATE 1000000

enum motors : byte {
  EYEBROW_HEIGHT_RIGHT, EYEBROW_HEIGHT_LEFT, EYEBROW_ANGLE_RIGHT, EYEBROW_ANGLE_LEFT,
  EYELID_UP_RIGHT, EYELID_UP_LEFT, EYELID_DOWN_RIGHT, EYELID_DOWN_LEFT,
  EYE_HORIZONTAL, EYE_VERTICAL,
  JAW_CLOCKWISE, JAW_ANTICLOCKWISE
};

Motor motor[12];
DynamixelProtocol dxl(BAUDRATE, ID);
unsigned char adress;
unsigned char angle;

void setup() {
  dxl.init();
  Serial.begin(BAUDRATE); //BAUDRATE
  Serial.flush();
  motor[EYEBROW_HEIGHT_RIGHT].setMotorDefinitions(20, 0, 150); 
  motor[EYEBROW_HEIGHT_LEFT].setMotorDefinitions(20, 150, 0);
  motor[EYEBROW_ANGLE_RIGHT].setMotorDefinitions(50, 0, 100); 
  motor[EYEBROW_ANGLE_LEFT].setMotorDefinitions(50, 100, 0); 
  motor[EYELID_UP_RIGHT].setMotorDefinitions(20, 75, 39); //OK    
  motor[EYELID_UP_LEFT].setMotorDefinitions(20, 10, 45); //Ok
  motor[EYELID_DOWN_RIGHT].setMotorDefinitions(20, 0, 65); //Zero eh abrir //Ok
  motor[EYELID_DOWN_LEFT].setMotorDefinitions(20, 58, 15); //Ok
  motor[EYE_HORIZONTAL].setMotorDefinitions(40, 0, 100); 
  motor[EYE_VERTICAL].setMotorDefinitions(85, 0, 100);
  motor[JAW_CLOCKWISE].setMotorDefinitions(100, 42, 53);
  motor[JAW_ANTICLOCKWISE].setMotorDefinitions(0, 0, 100);
}

int angles2;

void loop() {
  /*if(Serial.available())
  {
     angles2 = Serial.parseInt();
     Serial.print("Input: ");
     Serial.println(angles2);
     motor[JAW_CLOCKWISE].goTo(angles2);
  }
}*/
//  dxl.checkMessages();
//  
  dxl.checkMessages();
 
  if(dxl.instruction != DXL_NO_DATA && dxl.id == ID) {
    switch(dxl.instruction) {
      case DXL_WRITE_DATA:
        adress = dxl.parameters[0];
        angle = dxl.parameters[1];
        switch(adress) {
          case EYEBROW_HEIGHT_RIGHT:
            motor[EYEBROW_HEIGHT_RIGHT].goTo(angle);
            break;
          case EYEBROW_HEIGHT_LEFT:
            motor[EYEBROW_HEIGHT_LEFT].goTo(angle);
            break;
          case EYEBROW_ANGLE_RIGHT:
            motor[EYEBROW_ANGLE_RIGHT].goTo(angle);
            break;
          case EYEBROW_ANGLE_LEFT:
            motor[EYEBROW_ANGLE_LEFT].goTo(angle);
            break;
          case EYELID_UP_RIGHT:
            motor[EYELID_UP_RIGHT].goTo(angle);
            break;
          case EYELID_UP_LEFT:
            motor[EYELID_UP_LEFT].goTo(angle);
            break;
          case EYELID_DOWN_RIGHT:
            motor[EYELID_DOWN_RIGHT].goTo(angle);
            break;
          case EYELID_DOWN_LEFT:
            motor[EYELID_DOWN_LEFT].goTo(angle);
            break;
          case EYE_HORIZONTAL:
            motor[EYE_HORIZONTAL].goTo(angle);
            break;
          case EYE_VERTICAL:
            motor[EYE_VERTICAL].goTo(angle);
            break;
          case JAW_CLOCKWISE:
            motor[JAW_CLOCKWISE].goTo(angle);
            motor[JAW_ANTICLOCKWISE].goTo(angle);         
            break;
          default:
            break;
        }
      default:
        break;
    }   
  }
}
