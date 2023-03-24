#include "xgpio.h"
#include "xparameters.h"




int main()
{
	XGpio led_sw;
	int led=0x0000;
	int cpt=0;
	int comp;
	int sw_state;
	int mask0=0b0001;
	int mask1=0b0010;
	int mask2=0b0100;
	int mask3=0b1000;  //Initialize four switch we need

	XGpio_Initialize(&led_sw,XPAR_LED_SWITCH_DEVICE_ID);

	XGpio_SetDataDirection(&led_sw,1,0xF);  //Set direction of switch input
	XGpio_SetDataDirection(&led_sw,2,0);  //Set direction of switch output


	while(1)
	{
		sw_state = XGpio_DiscreteRead(&led_sw,1);  //Read the value of switch
		int q0=sw_state & mask0;
		int q1=sw_state & mask1;
		int q2=sw_state & mask2;
		int q3=sw_state & mask3;  //Read four value of switch

			for(cpt=0;cpt<=15;cpt++)  //Make a loop for 16 leds direction right to left
			{
				led=led & (0x0000);  //Reset the led
				XGpio_DiscreteWrite(&led_sw,2, led);  //Write the value in the gpio led

				led=1<<cpt;  //Add one and shift to left
				XGpio_DiscreteWrite(&led_sw,2, led); //Write the value in the gpio led

				if(q0==0b0001)  //If the first switch is pulled
				{
					for(comp=0;comp<100000;comp++){}  //Set waitfor in a period
				}
				else if(q1==0b0010)  //If the second switch is pulled
				{
					for(comp=0;comp<250000;comp++){}  //Set waitfor in a period
				}
				else if(q2==0b0100)  //If the third switch is pulled
				{
					for(comp=0;comp<500000;comp++){}  //Set waitfor in a period
				}
				else if(q3==0b1000)  //If the forth switch is pulled
				{
					for(comp=0;comp<750000;comp++){}  //Set waitfor in a period
				}
			}


			for(cpt=15;cpt>=0;cpt--)
			{
				led=led & (0x0000);
				XGpio_DiscreteWrite(&led_sw,2, led);  //Write the value in the gpio led

				led=1<<cpt;
				XGpio_DiscreteWrite(&led_sw,2, led);

				if(q0==0b0001)  //If the first switch is pulled
				{
					for(comp=0;comp<100000;comp++){}  //Set waitfor in a period
				}
				else if(q1==0b0010)  //If the second switch is pulled
				{
					for(comp=0;comp<250000;comp++){}  //Set waitfor in a period
				}
				else if(q2==0b0100)  //If the third switch is pulled
				{
					for(comp=0;comp<500000;comp++){}  //Set waitfor in a period
				}
				else if(q3==0b1000)  //If the forth switch is pulled
				{
					for(comp=0;comp<750000;comp++){}  //Set waitfor in a period
				}
			}


	}




}
