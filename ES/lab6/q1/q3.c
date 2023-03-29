#include <LPC17xx.h>

unsigned int i,j;
int v =1;

int main() {
	SystemInit(); //Add these two function for its internal operation
	SystemCoreClockUpdate();
	
	LPC_GPIO0->FIODIR |= 0xFF0;
	
	while (1){
		
			if (LPC_GPIO2->FIOPIN & (1<<12)){
				LPC_GPIO0->FIOPIN = v<<4;
				v*=2;
				if (v>255){
					v=1;}
				for(j=0; j<100000; j++);
			}
			else{
			  v = 1;}
		}
}	
