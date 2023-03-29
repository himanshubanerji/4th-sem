#include <LPC17xx.h>

unsigned int i,j;

int main() {
	SystemInit(); //Add these two function for its internal operation
	SystemCoreClockUpdate();
	
	LPC_GPIO0->FIODIR |= 0xFF0;
	
	while (1){
		for(i=0; i<256; i++) {
			LPC_GPIO0->FIOPIN = i<<4;
			for(j=0; j<100000; j++);
		}
	}
}	