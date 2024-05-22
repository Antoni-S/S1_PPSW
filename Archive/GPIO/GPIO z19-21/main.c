#include <LPC21xx.H>

//Definicje
#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19
#define S0_bm 1<<4
#define S1_bm 1<<6
#define S2_bm 1<<5
#define S3_bm 1<<7

enum KeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

//Funkcje
void Delay(int iDelayTime) {
	int iLoopCount = 12000;
	for(iLoopCount *= iDelayTime; iLoopCount > 0; iLoopCount--) {
		
	}
}

void LedInit(void) {
	IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET = LED0_bm;
}

enum KeyboardState eKeyboardRead() {
	if((IO0PIN & S0_bm) == 0) {
		return BUTTON_0;
	} else if((IO0PIN & S1_bm) == 0) {
		return BUTTON_1;
	} else if((IO0PIN & S2_bm) == 0) {
		return BUTTON_2;
	} else if((IO0PIN & S3_bm) == 0) {
		return BUTTON_3;
	} else {
		return RELEASED;
	}
}

void LedOn(unsigned char ucLedIndeks) {
	switch(ucLedIndeks) {
		case 0:
			IO1SET = LED0_bm;
			break;
		case 1:
			IO1SET = LED1_bm;
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
	}
}

void KeyboardInit(void) {
	IO0DIR = IO0DIR & (~(S0_bm | S1_bm | S2_bm | S3_bm));
}

unsigned int uiLeftStep = 0;

void StepLeft(void) {
	uiLeftStep = uiLeftStep + 1;
	LedOn(uiLeftStep % 4);
}

unsigned int uiRightStep = 3;

void StepRight(void) {
	uiRightStep = uiRightStep + 1;
	LedOn(3 - uiRightStep % 4);
}

int main() {
	LedInit();
	KeyboardInit();
/*
//Test do punktu 19
	while(1) {
		enum KeyboardState eButtonState = eKeyboardRead();
		switch(eButtonState) {
			case BUTTON_0:
				LedOn(0);
				break;
			case BUTTON_1:
				LedOn(1);
				break;
			case BUTTON_2:
				LedOn(2);
				break;
			case BUTTON_3:
				LedOn(3);
				break;
			case RELEASED:
				IO1CLR = LED0_bm;
				IO1CLR = LED1_bm;
				IO1CLR = LED2_bm;
				IO1CLR = LED3_bm;
		}
	}
*/
	Delay(250);
	IO1CLR = LED0_bm;
//Test do punktu 20
/*
	while(1) {
		StepLeft();
		Delay(250);
		IO1CLR = LED1_bm;
		StepLeft();
		Delay(250);
		IO1CLR = LED2_bm;
		StepLeft();
		Delay(250);
		IO1CLR = LED3_bm;
		StepLeft();
		Delay(250);
		IO1CLR = LED0_bm;
	}
*/
//Test do punktu 21

	while(1) {
		StepRight();
		Delay(250);
		IO1CLR = LED3_bm;
		StepRight();
		Delay(250);
		IO1CLR = LED2_bm;
		StepRight();
		Delay(250);
		IO1CLR = LED1_bm;
		StepRight();
		Delay(250);
		IO1CLR = LED0_bm;
	}
}
