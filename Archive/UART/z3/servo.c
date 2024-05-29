#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"
#include <LPC21xx.H>

#define DETECTOR_bm (1<<10)

void DetectorInit(void) {
	IO0DIR = IO0DIR & (~DETECTOR_bm);
}

enum DetectorState {ACTIVE, INACTIVE};

enum DetectorState eReadDetector(void) {
	if((IO0PIN & DETECTOR_bm) == 0) {
		return ACTIVE;
	}
	return INACTIVE;
}

enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo {
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPostion;
};

struct Servo sServo;

void Automat() {

	switch(sServo.eState) {
		case IDLE:
			if(sServo.uiCurrentPosition == sServo.uiDesiredPostion) {
				sServo.eState = IDLE;
			} else {
				sServo.eState = IN_PROGRESS;
			}
			break;
		case IN_PROGRESS:
			if(sServo.uiCurrentPosition < sServo.uiDesiredPostion) {
				LedStepRight();
				sServo.uiCurrentPosition += 1;
			} else if(sServo.uiCurrentPosition > sServo.uiDesiredPostion) {
				LedStepLeft();
				sServo.uiCurrentPosition -= 1;
			} else {
				sServo.eState = IDLE;
			}
			break;
		case CALLIB:
			if(eReadDetector() == INACTIVE) {
				LedStepLeft();
			} else if(eReadDetector() == ACTIVE) {
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPostion = 0;
				sServo.eState = IDLE;
			} else {
				sServo.eState = CALLIB;
			}
			break;
	}
}

void ServoInit(unsigned int uiServoFrequency) {
	uiServoFrequency = (1000000/uiServoFrequency);
	LedInit();
	sServo.eState = CALLIB;
	Timer0Interrupts_Init(uiServoFrequency, &Automat);
}

void ServoCallib(void) {
	
	sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition) {
	sServo.uiDesiredPostion = uiPosition;
}
