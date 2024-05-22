#include <LPC21xx.H>

//Definicje
#define LED0_bm 1<<16
#define LED3_bm 1<<19

//Deklaracje funkcji
void Delay(int iDelayTime) {
	//Podczas testowania programu ustalilem, ze wartosc 1 milisekundy to 2400 powtorzen petli
	int iLoopCount = 2400;
	for(iLoopCount *= iDelayTime; iLoopCount > 0; iLoopCount--) {
		
	}
}

int main() {
	// Deklaracja zmiennych i portow
	IO1DIR = LED3_bm;
	IO1SET = LED3_bm;
	IO1CLR = LED3_bm;
	
	// Petla wykonujaca
	while(1) {
		//Zadanie 4.2, punkt 3
		IO1SET = LED3_bm;
		Delay(100);
		IO1CLR = LED3_bm;
		Delay(100);
	}
}
