#include "motor.h"

int Motor::counter = 2;

void Motor::setMotorDefinitions(unsigned char startAngle, unsigned char beginLimit, unsigned char endLimit){
  servo.attach(counter++);
  limitAngle[0] = beginLimit;
  limitAngle[1] = endLimit;
  goTo(startAngle);
}

void Motor::goTo(unsigned char angle){
  angle = angle <= 0 ? 0 : angle;
  angle = angle >= 100 ? 100 : angle;

  int new_angle = map(angle, 0, 100, limitAngle[0], limitAngle[1]);

  Serial.print("ANGLE TO GO: ");
  Serial.println(new_angle);
  servo.write(new_angle);
}

unsigned char Motor::checkRange(unsigned char targetPos){
 if (targetPos < limitAngle[0]){
   return limitAngle[0];
 }
 else if (targetPos > limitAngle[1]){
   return limitAngle[1];
 }
 else return targetPos;
}

void Motor::returnCount(){
  Serial.println(counter);
}
