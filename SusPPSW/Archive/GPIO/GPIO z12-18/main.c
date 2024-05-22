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

enum ButtonState {PRESSED, RELEASED};

//Funkcje
void Delay(int iDelayTime) {
	int iLoopCount = 12000;
	for(iLoopCount *= iDelayTime; iLoopCount > 0; iLoopCount--) {
		
	}
}

void LedInit(void) {
	IO1DIR = IO1DIR | LED0_bm;
	IO1DIR = IO1DIR | LED1_bm;
	IO1DIR = IO1DIR | LED2_bm;
	IO1DIR = IO1DIR | LED3_bm;
	IO1SET = LED0_bm;
}

enum ButtonState ReadButton1() {
	if((IO0PIN & S0_bm) == 0) {
		return PRESSED;
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
	IO0DIR = IO0DIR | S0_bm;
	IO0DIR = IO0DIR | S1_bm;
	IO0DIR = IO0DIR | S2_bm;
	IO0DIR = IO0DIR | S3_bm;
}

int main() {
	LedInit();
	KeyboardInit();


	while(1) {
		if(ReadButton1() == RELEASED) {
			IO1CLR = LED1_bm;
		} else {
			LedOn(1);
		}
	}
/*
	while(1) {
		LedInit();
		Delay(250);
		IO1CLR = LED0_bm;
		LedOn(1);
		Delay(250);
		IO1CLR = LED1_bm;
		LedOn(2);
		Delay(250);
		IO1CLR = LED2_bm;
		LedOn(3);
		Delay(250);
		IO1CLR = LED3_bm;
	}
	*/
}
