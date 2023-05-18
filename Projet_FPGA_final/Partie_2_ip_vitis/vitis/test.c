#include "xparameters.h"
#include "xgpio.h"
#include "my_trame.h"
#include "xil_io.h"

int main()
{
	XGpio led_sw,bouton;

	int sw_state, bouton_state;

	int mask_sw_0 = 0b000000000000001;



	int mask_bp_l = 0b00100;
	int mask_bp_r = 0b01000;
	int bpl_pre = 0;
	int bpr_pre = 0;




	int adr = 0x0000;

	XGpio_Initialize(&led_sw,XPAR_LED_SWITCH_DEVICE_ID);  //Initialize the gpio switch
	XGpio_Initialize(&bouton,XPAR_BOUTON_DEVICE_ID);  //Initialize the button gpio
	XGpio_SetDataDirection(&led_sw,1,0x7FFF);  //Set direction switch input
	XGpio_SetDataDirection(&led_sw,2,0);  //Set direction led output
	XGpio_SetDataDirection(&bouton,1,0x1F);  //Set direction of gpio button input


	while(1)
		{
			sw_state = XGpio_DiscreteRead(&led_sw,1);  		//Read value of gpio switches
			bouton_state = XGpio_DiscreteRead(&bouton,1);  	//Read value of gpio buttons

			int sw_0 = sw_state & mask_sw_0;


			int bp_l = bouton_state & mask_bp_l;
			int bp_r = bouton_state & mask_bp_r;



			if(sw_0 == 0b000000000000001)
			{
				if(bp_l == 0b00100 && bpl_pre == 0)
				{
					if(adr == 0)
					{
						adr = 0xFFFF;
					}
					else
					{
						adr = adr - 1;
					}
				}
				else if(bp_r == 0b01000 && bpr_pre == 0)
				{
					if(adr == 0xFFFF)
					{
						adr = 0;
					}
					else
					{
						adr = adr + 1;
					}
				}
				bpl_pre = bp_l;
				bpr_pre = bp_r;
	            XGpio_DiscreteWrite(&led_sw,2,adr);

			}



		}


}
