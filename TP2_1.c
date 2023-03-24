//Writen by: Weiyi GONG, Zhuyu WEN
#include "xgpio.h"
#include "xparameters.h"




int main()
{
	XGpio led_sw,bouton;  //Initialize two values GPIO of led and botton
	int led=0x0000;
	int cpt;
	int comp=0x0000;
	int sw_state;
	int bouton_state;
	int mask0=0b0001;  //Mask to read first bit of gpio
	int mask1=0b0010;  //Mask to read second bit of gpio
	int maskbc=0b010;  //Mask to read second bit of gpio
	int maskbl=0b100;  //Mask to read third bit of gpio
	int maskbr=0b001;  //Mask to read first bit of gpio

	int bpc_dernier=0b000;

	XGpio_Initialize(&led_sw,XPAR_LED_SWITCH_DEVICE_ID);  //Initialize the led_sw gpio
	XGpio_Initialize(&bouton,XPAR_BOUTONS_DEVICE_ID);  //Initialize the button gpio

	XGpio_SetDataDirection(&led_sw,1,0xF);  //Set direction of gpio switch input
	XGpio_SetDataDirection(&led_sw,2,0);  //Set dirction of gpio led output
	XGpio_SetDataDirection(&bouton,1,0xF);  //Set dirction of gpio button input



	while(1){
		sw_state = XGpio_DiscreteRead(&led_sw,1);  //Read value of gpio switches
		bouton_state = XGpio_DiscreteRead(&bouton,1);  //Read value of gpio button
		int q0=sw_state & mask0;  //Read the first bit
		int q1=sw_state & mask1;  //Read the second bit
		int qbc=bouton_state & maskbc;  //Read the value of button center
		int qbl=bouton_state & maskbl;  //Read the value of button left
		int qbr=bouton_state & maskbr;  //Read the value of button right

		if(q0==0b0001)//If switch0=1
		{
			led=led|(0xFF00); //Turn the 8 first leds on the left on
			XGpio_DiscreteWrite(&led_sw,2, led );  //Write the value in the gpio led
			for(cpt=0;cpt<450000;cpt++){}  //Wait for
			led=led&(0x00FF);  //Turn off the led we turned on for blink
			XGpio_DiscreteWrite(&led_sw,2, led);  //Write the value in the gpio led
			for(cpt=0;cpt<450000;cpt++){}  //Wait for
		}

/*
		else if(q0!=0b0001)//If switch0=0
		{
			led=led&(0x00FF);
			XGpio_DiscreteWrite(&led_sw,2,led);
		}
*/


		if(q1==0b0010)//If switch1=1
		{
			if(qbc==0b010)  //If the button center is pressed
			{
				if(bpc_dernier==0b000)  //The last value of button is 0, so the button is pressed in this moment
				{
					comp++; //Add one to the counter
					if(comp==0x0010){comp=0x0000;}// Reset the counter if the value passed 8
				}

			}
			led=led&(0xFFF0);  //We reset the 4 led on the right side
			led=led|comp;  //Write the value of counter in the led
			XGpio_DiscreteWrite(&led_sw,2,led);  //Write the value in the gpio led
			bpc_dernier=qbc;  //Replace the last value of button by the value present

			if(qbl==0b100)  //If the button left is pressed
			{
				led=led|(0x00F0);  //We turn on the led middle
				XGpio_DiscreteWrite(&led_sw,2,led);  //Write the value in gpio led
			}
			if(qbr==0b001)  //If the button right is pressed
			{
				led=led&(0xFF0F);  //We turn off the led middle
				XGpio_DiscreteWrite(&led_sw,2,led);  //Write the value in gpio led
			}

		}
		else if(q1==0x0000)  //If the first switch is pulled
		{
			led=led&(0xFF00);  //Turn off all the led
			XGpio_DiscreteWrite(&led_sw,2,led);  //Write the value in the gpio led
		}


	}




}
