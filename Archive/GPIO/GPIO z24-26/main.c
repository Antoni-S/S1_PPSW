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

//Funkcje
void Delay(int iDelayTime) {
	int iLoopCount = 12000;
	for(iLoopCount *= iDelayTime; iLoopCount > 0; iLoopCount--) {}
}

void LedInit(void) {
	IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET = LED0_bm;
}

enum KeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

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
	//Maska bitowa ustawia 1 na dany bit, uzywamy negacji aby w zamian wpisac 0,
	//co powoduje, ze dany pin bedzie pinem wejsciowym
}

enum StepDirection {RIGHT, LEFT};

void LedStep(enum StepDirection eLedDirection) {
	static unsigned int uiLedStep;
	switch(eLedDirection) {
		case RIGHT:
			uiLedStep = uiLedStep - 1;
			break;
		case LEFT:
			uiLedStep = uiLedStep + 1;
			break;
	}
	LedOn(uiLedStep % 4);
}

void LedStepLeft(void) {
	LedStep(LEFT);
}

void LedStepRight(void) {
	LedStep(RIGHT);
}

int main() {
	LedInit();
	KeyboardInit();

	while(1) {
		enum KeyboardState eKeyPressed = eKeyboardRead();
		switch(eKeyPressed) {
			case BUTTON_1:
				LedStepRight();
				break;
			case BUTTON_2:
				LedStepLeft();
				break;
			default:
				break;
		}
		Delay(1000);
	}
}
