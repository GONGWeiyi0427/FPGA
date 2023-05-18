#include "xparameters.h"
#include "xgpio.h"
#include "my_trame.h"
#include "xil_io.h"




int main()
{
	XGpio led_sw,bouton;

	u64 trame = 0x1111111111111;
	unsigned int adr = 0x00;
	u64 pre_0 = 0b11111111111111111111111;	//Preambule de 23 bits
	u64 pre_1 = 0b11111111111111;			//Preambule de 14 bits

	int sw_state, bouton_state;

	int mask_sw_0 = 0b000000000000001;
	int mask_sw_1 = 0b000000000000010;
	int mask_sw_2 = 0b000000000000100;
	int mask_sw_3 = 0b000000000001000;
	int mask_sw_4 = 0b000000000010000;

	int mask_bp_c = 0b00001;
	int mask_bp_l = 0b00100;
	int mask_bp_r = 0b01000;
	int mask_bp_u = 0b00010;
	int mask_bp_d = 0b10000;

	int bp_r_pre = 0;
	int bp_l_pre = 0;
	int bp_u_pre = 0;
	int bp_d_pre = 0;
	int bp_c_pre = 0;


	int mode = 0;
	int cmd1 = 0b00000000;
	int cmd2 = 0b00000000;
	int cmd_04 = 0b00000000;
	int cmd_512 = 0b00000000;
	int cmd_1320 = 0b00000000;
	int cmd_sa;
	int cmd_sb;
	int controler = 0b00000000;
	int step_a = 0;
	int step_b = 0;

    int active = 0;

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
		int sw_1 = sw_state & mask_sw_1;
		int sw_2 = sw_state & mask_sw_2;
		int sw_3 = sw_state & mask_sw_3;
		int sw_4 = sw_state & mask_sw_4;

		int bp_c = bouton_state & mask_bp_c;
		int bp_l = bouton_state & mask_bp_l;
		int bp_r = bouton_state & mask_bp_r;
		int bp_u = bouton_state & mask_bp_u;
		int bp_d = bouton_state & mask_bp_d;

		if(sw_0 == 0b000000000000001)                                                                                   // sw0 to change the address
		{
			if(bp_l == 0b00100 && bp_l_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				adr = adr - 1;
				XGpio_DiscreteWrite(&led_sw,2,adr);                                                                  // write the adr in the led
			}
			if(bp_r == 0b01000 && bp_r_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				adr = adr + 1;
				XGpio_DiscreteWrite(&led_sw,2,adr);                                                                  // write the adr in the led
			}
		}   
		else if(sw_1 == 0b000000000000010)                                                                              // sw1 to change the speed run ahead
		{
			if(bp_l == 0b00100 && bp_l_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				step_a = step_a - 1;                                                                                    // speed slow down
				XGpio_DiscreteWrite(&led_sw,2,step_a);                                                                  // write the speed in the led
			}
			if(bp_r == 0b01000 && bp_r_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				step_a = step_a + 1;                                                                                    // speed up
				XGpio_DiscreteWrite(&led_sw,2,step_a);                                                                  // write the speed in the led
			}
			else if(bp_u == 0b00010 && bp_u_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				step_a = 28;                                                                                            // To the fastest
				XGpio_DiscreteWrite(&led_sw,2,step_a);                                                                  // write the speed in the led
			}
			else if(bp_d == 0b10000 && bp_d_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				step_a = 0;                                                                                             // To stop slowly
				XGpio_DiscreteWrite(&led_sw,2,step_a);                                                                  // write the speed in the led
			}
			if(step_a == 0) cmd_sa = 0b01100000;
			else if(step_a == 1) cmd_sa = 0b01100010;
			else if(step_a == 2) cmd_sa = 0b01110010;
			else if(step_a == 3) cmd_sa = 0b01100011;
			else if(step_a == 4) cmd_sa = 0b01110011;
			else if(step_a == 5) cmd_sa = 0b01100100;
			else if(step_a == 6) cmd_sa = 0b01110100;
			else if(step_a == 7) cmd_sa = 0b01100101;
			else if(step_a == 8) cmd_sa = 0b01110101;
			else if(step_a == 9) cmd_sa = 0b01100110;
			else if(step_a == 10) cmd_sa = 0b01110110;
			else if(step_a == 11) cmd_sa = 0b01100111;
			else if(step_a == 12) cmd_sa = 0b01110111;
			else if(step_a == 13) cmd_sa = 0b01101000;
			else if(step_a == 14) cmd_sa = 0b01111000;
			else if(step_a == 15) cmd_sa = 0b01101001;
			else if(step_a == 16) cmd_sa = 0b01111001;
			else if(step_a == 17) cmd_sa = 0b01101010;
			else if(step_a == 18) cmd_sa = 0b01111010;
			else if(step_a == 19) cmd_sa = 0b01101011;
			else if(step_a == 20) cmd_sa = 0b01111011;
			else if(step_a == 21) cmd_sa = 0b01101100;
			else if(step_a == 22) cmd_sa = 0b01111100;
			else if(step_a == 23) cmd_sa = 0b01101101;
			else if(step_a == 24) cmd_sa = 0b01111101;
			else if(step_a == 25) cmd_sa = 0b01101110;
			else if(step_a == 26) cmd_sa = 0b01111110;
			else if(step_a == 27) cmd_sa = 0b01101111;
			else if(step_a == 28) cmd_sa = 0b01111111;
			else if(step_a == 29) cmd_sa = 0b01110001;

			mode = 22;                                                                                                  // mode 22 as run ahead
		}
		else if(sw_2 == 0b000000000000100)                                                                              // sw2 to control the speed run backwards
		{
			if(bp_l == 0b00100 && bp_l_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				step_b = step_b - 1;
				XGpio_DiscreteWrite(&led_sw,2,step_b);                                                                  // write the speed in the led
			}
			if(bp_r == 0b01000 && bp_r_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				step_b = step_b + 1;
				XGpio_DiscreteWrite(&led_sw,2,step_b);                                                                  // write the speed in the led
			}
			else if(bp_u == 0b00010 && bp_u_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				step_b = 28;
				XGpio_DiscreteWrite(&led_sw,2,step_b);                                                                  // write the speed in the led
			}
			else if(bp_d == 0b10000 && bp_d_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				step_b = 0;
				XGpio_DiscreteWrite(&led_sw,2,step_b);                                                                  // write the speed in the led
			}
			if(step_b == 0) cmd_sb = 0b01000000;
			else if(step_b == 1) cmd_sb = 0b01000010;
			else if(step_b == 2) cmd_sb = 0b01010010;
			else if(step_b == 3) cmd_sb = 0b01000011;
			else if(step_b == 4) cmd_sb = 0b01010011;
			else if(step_b == 5) cmd_sb = 0b01000100;
			else if(step_b == 6) cmd_sb = 0b01010100;
			else if(step_b == 7) cmd_sb = 0b01000101;
			else if(step_b == 8) cmd_sb = 0b01010101;
			else if(step_b == 9) cmd_sb = 0b01000110;
			else if(step_b == 10) cmd_sb = 0b01010110;
			else if(step_b == 11) cmd_sb = 0b01000111;
			else if(step_b == 12) cmd_sb = 0b01010111;
			else if(step_b == 13) cmd_sb = 0b01001000;
			else if(step_b == 14) cmd_sb = 0b01011000;
			else if(step_b == 15) cmd_sb = 0b01001001;
			else if(step_b == 16) cmd_sb = 0b01011001;
			else if(step_b == 17) cmd_sb = 0b01001010;
			else if(step_b == 18) cmd_sb = 0b01011010;
			else if(step_b == 19) cmd_sb = 0b01001011;
			else if(step_b == 20) cmd_sb = 0b01011011;
			else if(step_b == 21) cmd_sb = 0b01001100;
			else if(step_b == 22) cmd_sb = 0b01011100;
			else if(step_b == 23) cmd_sb = 0b01001101;
			else if(step_b == 24) cmd_sb = 0b01011101;
			else if(step_b == 25) cmd_sb = 0b01001110;
			else if(step_b == 26) cmd_sb = 0b01011110;
			else if(step_b == 27) cmd_sb = 0b01001111;
			else if(step_b == 28) cmd_sb = 0b01011111;
			else if(step_b == 29) cmd_sb = 0b01010001;

			mode = 23;                                                                                              // run backwards as mode 23
		}
		else if(sw_3 == 0b000000000001000)
		{
			if(bp_l == 0b00100 && bp_l_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				if(mode != 0)
				{
					mode --;                                                                                        // mode - 1 
				}
				XGpio_DiscreteWrite(&led_sw,2,mode);                                                                  // write the mode in the led
			}
			else if(bp_r == 0b01000 && bp_r_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				if(mode != 20)
				{
					mode ++;                                                                                        // mode + 1
				}
				XGpio_DiscreteWrite(&led_sw,2,mode);                                                                  // write the mode in the led
			}
			else if(bp_u == 0b00010 && bp_u_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				if(mode < 11)
				{
					mode = mode + 10;
				}
				XGpio_DiscreteWrite(&led_sw,2,mode);                                                                  // write the mode in the led
			}
			else if(bp_d == 0b10000 && bp_d_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				if(mode > 9)
				{
					mode = mode - 10;
				}
				XGpio_DiscreteWrite(&led_sw,2,mode);                                                                  // write the mode in the led
			}

			if(mode == 0) {cmd1 = 0b10010000;}
			else if(mode == 1)  {cmd1 = 0b10000001;}
			else if(mode == 2)  {cmd1 = 0b10000010;}
			else if(mode == 3)  {cmd1 = 0b10000100;}
			else if(mode == 4)  {cmd1 = 0b10001000;}
			else if(mode == 5)  {cmd1 = 0b10010001;}
			else if(mode == 6)  {cmd1 = 0b10110010;}
			else if(mode == 7)  {cmd1 = 0b10110100;}
			else if(mode == 8)  {cmd1 = 0b10111000;}
			else if(mode == 9)  {cmd1 = 0b10100001;}
			else if(mode == 10) {cmd1 = 0b10100010;}
			else if(mode == 11) {cmd1 = 0b10100100;}
			else if(mode == 12) {cmd1 = 0b10101000;}
			else if(mode == 13) {cmd1 = 0b11011110; cmd2 = 0b00000001;}
			else if(mode == 14) {cmd1 = 0b11011110; cmd2 = 0b00000010;}
			else if(mode == 15) {cmd1 = 0b11011110; cmd2 = 0b00000100;}
			else if(mode == 16) {cmd1 = 0b11011110; cmd2 = 0b00001000;}
			else if(mode == 17) {cmd1 = 0b11011110; cmd2 = 0b00010000;}
			else if(mode == 18) {cmd1 = 0b11011110; cmd2 = 0b00100000;}
			else if(mode == 19) {cmd1 = 0b11011110; cmd2 = 0b01000000;}
			else if(mode == 20) {cmd1 = 0b11011110; cmd2 = 0b10000000;}

			active = 1;                                                                                                 // treat as the activation
		}
		else if(sw_4 == 0b000000000010000) 	//Chose the dis-activation of the functions F0-21
		{
			if(bp_l == 0b00100 && bp_l_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				if(mode != 0)
				{
					mode --;
				}
				XGpio_DiscreteWrite(&led_sw,2,mode);                                                                  // write the mode in the led
			}
			else if(bp_r == 0b01000 && bp_r_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				if(mode != 20)
				{
					mode ++;
				}
				XGpio_DiscreteWrite(&led_sw,2,mode);                                                                  // write the mode in the led
			}
			else if(bp_u == 0b00010 && bp_u_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				if(mode < 11)
				{
					mode = mode + 10;
				}
				XGpio_DiscreteWrite(&led_sw,2,mode);                                                                  // write the mode in the led
			}
			else if(bp_d == 0b10000 && bp_d_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
			{
				if(mode > 9)
				{
					mode = mode - 10;
				}
				XGpio_DiscreteWrite(&led_sw,2,mode);                                                                  // write the mode in the led
			}

			if(mode == 0) cmd1 = 0b10001111;
			else if(mode == 1)  cmd1 = 0b10011110;
			else if(mode == 2)  cmd1 = 0b10011101;
			else if(mode == 3)  cmd1 = 0b10011011;
			else if(mode == 4)  cmd1 = 0b10010111;
			else if(mode == 5)  cmd1 = 0b10111000;
			else if(mode == 6)  cmd1 = 0b10111101;
			else if(mode == 7)  cmd1 = 0b10111011;
			else if(mode == 8)  cmd1 = 0b10110111;
			else if(mode == 9)  cmd1 = 0b10101000;
			else if(mode == 10) cmd1 = 0b10101101;
			else if(mode == 11) cmd1 = 0b10101011;
			else if(mode == 12) cmd1 = 0b10100111;
			else if(mode == 13) {cmd1 = 0b11011110; cmd2 = 0b11111110;}
			else if(mode == 14) {cmd1 = 0b11011110; cmd2 = 0b11111101;}
			else if(mode == 15) {cmd1 = 0b11011110; cmd2 = 0b11111011;}
			else if(mode == 16) {cmd1 = 0b11011110; cmd2 = 0b11110111;}
			else if(mode == 17) {cmd1 = 0b11011110; cmd2 = 0b11101111;}
			else if(mode == 18) {cmd1 = 0b11011110; cmd2 = 0b11011111;}
			else if(mode == 19) {cmd1 = 0b11011110; cmd2 = 0b10111111;}
			else if(mode == 20) {cmd1 = 0b11011110; cmd2 = 0b01111111;}


		    active = 0;                                                         // In the mode dis-activation
		}



		if(bp_c == 0b00001 && bp_c_pre == 0)                                                                     // If the last time bouton is not pressed and now the bouton is pressed
		{
			if(mode == 22)                                                                                      // Run ahead
			{
				controler = cmd_sa ^ adr;                                                                     // Calculate the bits controlers
				trame = (pre_0 << 28) + (0 << 27) + (adr << 19) + (0 << 18) + (cmd_sa << 10) + (0 << 9) + (controler << 1) + 1;
				MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG0_OFFSET,trame);  //Write the first 26 bits trame in the first register
				MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG1_OFFSET,trame>>26);  //Write the second 25 bits trame in the second register
			}
			else if(mode == 23)                                                                                 // Run backwards
			{
				controler = cmd_sb ^ adr;                                                                     // Calculate the bits controlers
				trame = (pre_0 << 28) + (0 << 27) + (adr << 19) + (0 << 18) + (cmd_sb << 10) + (0 << 9) + (controler << 1) + 1;
				MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG0_OFFSET,trame);  //Write the first 26 bits trame in the first register
				MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG1_OFFSET,trame>>26);  //Write the second 25 bits trame in the second register
			}
			else if(mode >= 0 && mode <= 4)                                                                         // If in the fonction 0 to 4
			{
				if(active == 1)                                                                                     // If in the mode of activation
				{
					cmd_04 = cmd_04 | cmd1;                                                                         // Mask the bits for the fonctions 0 to 4
					controler = cmd_04 ^ adr;                                                                     // Calculate the bits controlers
					trame = (pre_0 << 28) + (0 << 27) + (adr << 19) + (0 << 18) + (cmd_04 << 10) + (0 << 9) + (controler << 1) + 1;
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG0_OFFSET,trame);  //Write the first 26 bits trame in the first register
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG1_OFFSET,trame>>26);  //Write the second 25 bits trame in the second register
				}
				else                                                                                                 // In mode dis-activation
				{
					cmd_04 = cmd_04 & cmd1;                                                                         // Mask the bits for the fonctions 0 to 4
					controler = cmd_04 ^ adr;                                                                     // Calculate the bits controlers
					trame = (pre_0 << 28) + (0 << 27) + (adr << 19) + (0 << 18) + (cmd_04 << 10) + (0 << 9) + (controler << 1) + 1;
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG0_OFFSET,trame);  //Write the first 26 bits trame in the first register
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG1_OFFSET,trame>>26);  //Write the second 25 bits trame in the second register
				}
			}
			else if(mode >= 5 && mode <= 12)                                                                        // If in the fonction 5 to 12
			{
				if(active == 1)                                                                                     // If in the mode of activation
				{
					cmd_512 = cmd_512 | cmd1;                                                                       // Mask the bits for the fonctions 5 to 12
					controler = cmd_512 ^ adr;                                                                     // Calculate the bits controlers
					trame = (pre_0 << 28) + (0 << 27) + (adr << 19) + (1 << 18) + (cmd_512 << 10) + (0 << 9) + (controler << 1) + 1;
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG0_OFFSET,trame);  //Write the first 26 bits trame in the first register
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG1_OFFSET,trame>>26);  //Write the second 25 bits trame in the second register
				}
				else                                                                                                 // In mode dis-activation
				{
					cmd_512 = cmd_512 & cmd1;                                                                       // Mask the bits for the fonctions 5 to 12
					controler = cmd_512 ^ adr;                                                                     // Calculate the bits controlers
					trame = (pre_0 << 28) + (0 << 27) + (adr << 19) + (1 << 18) + (cmd_512 << 10) + (0 << 9) + (controler << 1) + 1;
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG0_OFFSET,trame);  //Write the first 26 bits trame in the first register
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG1_OFFSET,trame>>26);  //Write the second 25 bits trame in the second register
				}
			}
			else if(mode >= 13 && mode <= 20)                                                                     // If in the fonction 13 to 20
			{
				u64 bit_0 = 0;
				if(active == 1)                                                                                     // If in mode activation
				{
					cmd_1320 = cmd_1320 | cmd2;                                                                     // Mask the bits for the fonctions 13 to 20
					controler = cmd_1320 ^ cmd1 ^ adr;                                                                     // Calculate the bits controlers
					trame = (pre_1 << 37) + (bit_0 << 36) + (adr << 28) + (0 << 27) + (cmd1 << 19) + (0 << 18) + (cmd_1320 << 10) + (0 << 9) + (controler << 1) + 1;
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG0_OFFSET,trame);  //Write the first 26 bits trame in the first register
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG1_OFFSET,trame>>26);  //Write the second 25 bits trame in the second register
				}
				else                                                                                                 // In mode dis-activation
				{
					cmd_1320 = cmd_1320 & cmd2;                                                                     // Mask the bits for the fonctions 13 to 20
					controler = cmd_1320 ^ cmd1 ^ adr;                                                                     // Calculate the bits controlers
					trame = (pre_1 << 37) + (bit_0 << 36) + (adr << 28) + (0 << 27) + (cmd1 << 19) + (0 << 18) + (cmd_1320 << 10) + (0 << 9) + (controler << 1) + 1;
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG0_OFFSET,trame);  //Write the first 26 bits trame in the first register
					MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG1_OFFSET,trame>>26);  //Write the second 25 bits trame in the second register
				}
			}


		}
		bp_l_pre = bp_l;
		bp_r_pre = bp_r;
		bp_c_pre = bp_c;
		bp_u_pre = bp_u;
		bp_d_pre = bp_d;

	}
}
