#include <LPC17xx.h>

unsigned int i,j;

int main() {
	SystemInit(); //Add these two function for its internal operation
	SystemCoreClockUpdate();
	
	LPC_GPIO0->FIODIR |= 0xFF0;
	LPC_GPIO2->FIODIR &= 0xFFFFEFFF;
	
	while (1){
		
		/*if (LPC_GPIO2->FIOPIN & (1<<12)){
		for(i=0; i<256; i++) {
			LPC_GPIO0->FIOPIN = i<<4;
			for(j=0; j<100000; j++);
		}}
		
		else{
		for(i=255; i>=0; i--) {
			LPC_GPIO0->FIOPIN = i<<4;
			for(j=0; j<100000; j++);
		}}*/
		
		for (i = 0; i<256;i++){
			if (LPC_GPIO2->FIOPIN & (1<<12)){
				LPC_GPIO0->FIOPIN = i<<4;
				for(j=0; j<100000; j++);
			}
			
			else{
				LPC_GPIO0->FIOPIN = (255-i)<<4;
				for(j=0; j<100000; j++);
			}
		}
		
		}
}	