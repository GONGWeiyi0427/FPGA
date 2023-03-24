#include "xil_io.h"
#include "my_led.h"
#include "xgpio.h"
#include "xparameters.h"

int main()
{
	XGpio sw;  //Switch should read in mode gpio
	u32 data;  //unsigned vector of 32 bits


	XGpio_Initialize(&sw,XPAR_GPIO_0_DEVICE_ID);  //Initialize the gpio switch

	XGpio_SetDataDirection(&sw,1,0xF);  //Set direction switch input

	while(1)
	{
		data=XGpio_DiscreteRead(&sw,1);  //Read the value from gpio

		MY_LED_mWriteReg(XPAR_MY_LED_0_S00_AXI_BASEADDR,MY_LED_S00_AXI_SLV_REG0_OFFSET,data);  //Write the first two bits in the first register
		MY_LED_mWriteReg(XPAR_MY_LED_0_S00_AXI_BASEADDR,MY_LED_S00_AXI_SLV_REG1_OFFSET,data>>2);  //Write the second two bits in the second register
		//The value written in the register will read by the ip and directly control the leds

	}

	return 0;
}
