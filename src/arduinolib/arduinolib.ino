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

enum motores : byte {
  EYELID, EYEBROWM, EYE, MOUTH
};

Motor motor[12];
DynamixelProtocol dxl(BAUDRATE, ID);
unsigned char address;
unsigned char angle;

void setup() {
  dxl.init();
  Serial.begin(BAUDRATE); //BAUDRATE
  Serial.flush();
  
  motor[EYEBROW_HEIGHT_RIGHT].setMotorDefinitions(20, 0, 150); 
  motor[EYEBROW_HEIGHT_LEFT].setMotorDefinitions(20, 150, 0);
  motor[EYEBROW_ANGLE_RIGHT].setMotorDefinitions(50, 0, 100); 
  motor[EYEBROW_ANGLE_LEFT].setMotorDefinitions(50, 100, 0); 
  motor[EYELID_UP_RIGHT].setMotorDefinitions(20, 75, 39);   
  motor[EYELID_UP_LEFT].setMotorDefinitions(20, 10, 45); 
  motor[EYELID_DOWN_RIGHT].setMotorDefinitions(20, 0, 65); 
  motor[EYELID_DOWN_LEFT].setMotorDefinitions(20, 58, 15); 
  motor[EYE_HORIZONTAL].setMotorDefinitions(40, 0, 100); 
  motor[EYE_VERTICAL].setMotorDefinitions(85, 0, 100);
  motor[JAW_CLOCKWISE].setMotorDefinitions(100, 42, 53);
  motor[JAW_ANTICLOCKWISE].setMotorDefinitions(0, 0, 100);
}


void loop() {
  dxl.checkMessages();
 
  if(dxl.instruction != DXL_NO_DATA && dxl.id == ID) {
    switch(dxl.instruction) {
      case DXL_WRITE_DATA:
        address = dxl.parameters[0];
        angle = dxl.parameters[1];
        Serial.print(angle);
//        switch(address) {
//          case EYELID:
//            // angle has 4 bytes
//            break;
//          case EYEBROWM:
//            // angle has 4 bytes
//            break;
//          case EYE:
//            // angle has 2 bytes
//            break;
//          case MOUTH:
//            // angle has 1 byte
//          default:
//            break;
//        }
        switch(address) {
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
