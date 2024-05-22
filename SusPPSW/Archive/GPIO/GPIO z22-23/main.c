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
#define LEDCLR_bm LED0_bm | LED1_bm | LED2_bm | LED3_bm

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
	IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
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

enum StepDirection {RIGHT, LEFT};

void LedStep(enum StepDirection eLedDirection) {
	static unsigned int uiLedStep;
	if(eLedDirection == RIGHT) {
		uiLedStep = uiLedStep - 1;
	} else {
		uiLedStep = uiLedStep + 1;
	}
	LedOn(uiLedStep % 4);
}

int main() {
	unsigned char ucRightCounter;
	unsigned char ucLeftCounter;
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
				IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
		}
	}
*/
	Delay(250);
	IO1CLR = LEDCLR_bm;
	while(1) {
		for(ucRightCounter = 0; ucRightCounter < 9; ucRightCounter++) {
			LedStep(RIGHT);
			Delay(250);
			IO1CLR = LEDCLR_bm;
		}
		for(ucLeftCounter = 0; ucLeftCounter < 9; ucLeftCounter++) {
			LedStep(LEFT);
			Delay(250);
			IO1CLR = LEDCLR_bm;
		}
	}
}
