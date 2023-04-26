motor)/********************************************************************************************************************************************************/

#include <LPC17xx.H>
void clock_wise(void);
void anti_clock_wise(void);
unsigned long int var1,var2;
unsigned int i=0,j=0,k=0;
 
int main(void)
{
SystemInit();
SystemCoreClockUpdate();
LPC_PINCON->PINSEL0 = 0xFFFF00FF; //P0.4 to P0.7 GPIO
LPC_GPIO0->FIODIR = 0x000000F0; //P0.4 to P0.7 output
LPC_PINCON->PINSEL4 &= 0XFCFFFFFF;
LPC_GPIO2->FIODIR &= 0XFFFFEFFF;
while(1)
{
if((LPC_GPIO2->FIOPIN & (1<<12)))
{
for(j=0;j<50;j++)
{
clock_wise();
}
for(k=0;k<65000;k++); // Delay to show anti_clock Rotation
}
else if(!(LPC_GPIO2->FIOPIN & (1<<12)))
{
for(j=0;j<50;j++)
{
anti_clock_wise();
}
for(k=0;k<65000;k++); // Delay to show clock Rotation 
}
} // End of while(1)
} // End of main
void clock_wise(void)
{
var1 = 0x00000008; //For Clockwise
for(i=0;i<=3;i++) // for A B C D Stepping
{
var1 = var1<<1; //For Clockwise
LPC_GPIO0->FIOPIN = var1;
for(k=0;k<3000;k++); //for step speed variation 
}
}
void anti_clock_wise(void)
{
var1 = 0x00000100; //For Anticlockwise
for(i=0;i<=3;i++) // for A B C D Stepping
{
var1 = var1>>1; //For Anticlockwise
LPC_GPIO0->FIOPIN = var1;
 
for(k=0;k<3000;k++); //for step speed variation 
}
 

}









burst)/********************************************************************************************************************************************************/

#include <LPC17xx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

unsigned char str[]={"0123456789"};
unsigned long x;
float t1=0,t2=0;
unsigned char vtg1[7],vtg2[7];

void lcd_init(void);
void lcd_comdata(int temp1, int type);
void write(int temp2, int type);
void delay_lcd(unsigned int r1);
void clear_ports(void);
void lcd_puts(unsigned char *buf1);

int main(void)
{
    
    lcd_init();
    LPC_PINCON->PINSEL3=(0xF)<<28; //P1.30 as AD0.4 and P1.31 as AD0.5
    LPC_SC->PCONP |=(1<<12);
    LPC_ADC->ADCR = (1 << 4 | 1 << 5 | 1 << 16 | 1 << 21);
    LPC_ADC->ADINTEN = (1<<4|1<<5);
    NVIC_EnableIRQ(ADC_IRQn);
    while(1);
}
void ADC_IRQHandler(void)
{x=LPC_ADC->ADSTAT&(3<<4);
 
    if(x>>4 & 1) {
        t1 = (LPC_ADC->ADDR4>>4)&0xFFF;
        t1 = (float)((t1*3.3)/4096);
        sprintf(vtg1,"%3.2fV",t1);
      lcd_comdata(0x80,0);
      delay_lcd(800);
      lcd_puts(&vtg1[0]);
    } if(x>>5 & 1){
        t2 = (LPC_ADC->ADDR5>>4)&0xFFF;
        t2 = (float)((t2*3.3)/4096);
      sprintf(vtg2,"%3.2fV",t2);
      lcd_comdata(0xc0,0);
      delay_lcd(800);
      lcd_puts(&vtg2[0]);
    }
}

void lcd_init()
{
/*Ports initialized as GPIO */
 LPC_PINCON->PINSEL1 &= 0xFC003FFF; //P0.23 to P0.28
/*Setting the directions as output */
 LPC_GPIO0->FIODIR |= 0x0F<<23 | 1<<27 | 1<<28;
 
 clear_ports();
delay_lcd(3200);
lcd_comdata(0x33, 0); 
delay_lcd(30000); 
lcd_comdata(0x32, 0);
delay_lcd(30000);
lcd_comdata(0x28, 0); //function set
delay_lcd(30000);
lcd_comdata(0x0c, 0);//display on cursor off
delay_lcd(800);
lcd_comdata(0x06, 0); //entry mode set increment cursor right
delay_lcd(800);
lcd_comdata(0x01, 0); //display clear
delay_lcd(10000);
return;
}
void lcd_comdata(int temp1, int type)
{
int temp2 = temp1 & 0xf0; //move data (26-8+1) times : 26 - HN place, 4 - Bits
temp2 = temp2 << 19; //data lines from 23 to 26
write(temp2, type);
temp2 = temp1 & 0x0f; //26-4+1
temp2 = temp2 << 23; 
write(temp2, type);
delay_lcd(1000);
return;
}
void write(int temp2, int type) //write to command/data reg
{ 
clear_ports();
LPC_GPIO0->FIOPIN = temp2; // Assign the value to the data lines 
if(type==0)
LPC_GPIO0->FIOCLR = 1<<27; // clear bit RS for Command
else
LPC_GPIO0->FIOSET = 1<<27; // set bit RS for Data
LPC_GPIO0->FIOSET = 1<<28; // EN=1
delay_lcd(25);
LPC_GPIO0->FIOCLR = 1<<28; // EN =0
 return;
}
void delay_lcd(unsigned int r1)
{
 unsigned int r;
 for(r=0;r<r1;r++);
 return;
}
void clear_ports(void)
{
 /* Clearing the lines at power on */
LPC_GPIO0->FIOCLR = 0x0F<<23; //Clearing data lines
LPC_GPIO0->FIOCLR = 1<<27; //Clearing RS line
LPC_GPIO0->FIOCLR = 1<<28; //Clearing Enable line
 
 return;
}
void lcd_puts(unsigned char *buf1)
{
 unsigned int i=0;
unsigned int temp3;
 while(buf1[i]!='\0')
 {
 temp3 = buf1[i];
 lcd_comdata(temp3, 1);
 i++;
 if(i==16)
 {
 lcd_comdata(0xc0, 0);
 }
 }
 return;
}









software)/********************************************************************************************************************************************************/


#include<LPC17xx.h>
#include<stdio.h>

 #define	Ref_Vtg		3.300
 #define	Full_Scale	0xFFF			//12 bit ADC
 
void lcd_init(void);
void lcd_comdata(int temp1, int type);
void write(int temp2, int type);
void delay_lcd(unsigned int r1);
void clear_ports(void);
void lcd_puts(unsigned char *buf1);

int main(void)
{
	unsigned long adc_temp;
	unsigned int i;
	float in_vtg;
	unsigned char vtg[7],dval[7];
	unsigned char Msg1[11] = {"ANLOG IP:"};
	unsigned char Msg2[12] = {"ADC O/P:"};
	
	 
    lcd_init();
    LPC_PINCON->PINSEL3 = 3<<30;	//P1.31 as AD0.5
	  LPC_SC->PCONP |= (1<<12);			//enable the peripheral ADC
	
	lcd_comdata(0x80, 0);
	delay_lcd(800);
	lcd_puts(&Msg1[0]);

	lcd_comdata(0xC0, 0);
	delay_lcd(800);
	lcd_puts(&Msg2[0]);

	while(1)
	{
		LPC_ADC->ADCR = (1<<5)|(1<<21)|(1<<24); 	//AD0.5, operational and start conversion	
		while(!(LPC_ADC->ADDR5 & 0x80000000));	//wait till 'done' bit is 1, indicates conversion complete                                                                                                                                                      
		adc_temp = LPC_ADC->ADDR5;
		adc_temp >>= 4;
		adc_temp &= 0x00000FFF;			//12 bit ADC
		in_vtg = ((float)adc_temp * Ref_Vtg)/(Full_Scale);	//calculating input analog voltage
		sprintf(vtg,"%3.2fV",in_vtg);	//convert the readings into string to display on LCD
		sprintf(dval,"%x",adc_temp);
		for(i=0;i<2000;i++);

		lcd_comdata(0x89, 0); //Firstline 9th charecter
		delay_lcd(800);
		lcd_puts(&vtg[0]);
                                   for(i=0;i<20000;i++);
		lcd_comdata(0xC8, 0);  //Secondline 8th character
		delay_lcd(800);
		lcd_puts(&dval[0]);

        for(i=0;i<20000;i++);
        for(i=0;i<7;i++)
        vtg[i] = dval[i] = 0x00;
        adc_temp = 0;
        in_vtg = 0;
	}
}



void lcd_init()
{
/*Ports initialized as GPIO */
 LPC_PINCON->PINSEL1 &= 0xFC003FFF; //P0.23 to P0.28
/*Setting the directions as output */
 LPC_GPIO0->FIODIR |= 0x0F<<23 | 1<<27 | 1<<28;
 
 clear_ports();
delay_lcd(3200);
lcd_comdata(0x33, 0); 
delay_lcd(30000); 
lcd_comdata(0x32, 0);
delay_lcd(30000);
lcd_comdata(0x28, 0); //function set
delay_lcd(30000);
lcd_comdata(0x0c, 0);//display on cursor off
delay_lcd(800);
lcd_comdata(0x06, 0); //entry mode set increment cursor right
delay_lcd(800);
lcd_comdata(0x01, 0); //display clear
delay_lcd(10000);
return;
}
void lcd_comdata(int temp1, int type)
{
int temp2 = temp1 & 0xf0; //move data (26-8+1) times : 26 - HN place, 4 - Bits
temp2 = temp2 << 19; //data lines from 23 to 26
write(temp2, type);
temp2 = temp1 & 0x0f; //26-4+1
temp2 = temp2 << 23; 
write(temp2, type);
delay_lcd(1000);
return;
}
void write(int temp2, int type) //write to command/data reg
{ 
clear_ports();
LPC_GPIO0->FIOPIN = temp2; // Assign the value to the data lines 
if(type==0)
LPC_GPIO0->FIOCLR = 1<<27; // clear bit RS for Command
else
LPC_GPIO0->FIOSET = 1<<27; // set bit RS for Data
LPC_GPIO0->FIOSET = 1<<28; // EN=1
delay_lcd(25);
LPC_GPIO0->FIOCLR = 1<<28; // EN =0
 return;
}
void delay_lcd(unsigned int r1)
{
 unsigned int r;
 for(r=0;r<r1;r++);
 return;
}
void clear_ports(void)
{
 /* Clearing the lines at power on */
LPC_GPIO0->FIOCLR = 0x0F<<23; //Clearing data lines
LPC_GPIO0->FIOCLR = 1<<27; //Clearing RS line
LPC_GPIO0->FIOCLR = 1<<28; //Clearing Enable line
 
 return;
}
void lcd_puts(unsigned char *buf1)
{
 unsigned int i=0;
unsigned int temp3;
 while(buf1[i]!='\0')
 {
 temp3 = buf1[i];
 lcd_comdata(temp3, 1);
 i++;
 if(i==16)
 {
 lcd_comdata(0xc0, 0);
 }
 }
 return;
}



