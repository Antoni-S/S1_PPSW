#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE (1<<0)
#define COUNTER_RESET (1<<1)
#define MR0_RESET (1<<1)
#define MR0_INTERRUPT (1<<0)
#define MR0_FLAG (1<<0)

void InitTimer0(void) {
	
	T0TCR = COUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime) {
	
	T0TCR = T0TCR | COUNTER_RESET;
	T0TCR = T0TCR & (~(COUNTER_RESET));
	while(T0TC <= (uiTime * 15)) {};
}

void InitTimer0Match0(unsigned int uiDelayTime) {
	
	T0MR0 = (uiDelayTime * 15);
	T0MCR = T0MCR | MR0_RESET;
	T0MCR = T0MCR | MR0_INTERRUPT;
	T0TCR = T0TCR | COUNTER_RESET;
	T0TCR = T0TCR & (~(COUNTER_RESET));
	T0TCR = COUNTER_ENABLE;
}

void WaitOnTimer0Match0(void) {
	
	while(T0IR != MR0_FLAG) {}
	T0IR = MR0_FLAG;
}
