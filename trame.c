#include "xparameters.h"
#include "xgpio.h"
#include "my_trame.h"
#include "xil_io.h"



int main()
{
	XGpio led_sw,bouton;
	u64 trame;

	int pre_0 = 0b11111111111111111111111;	//Preambule de 23 bits
	int pre_1 = 0b11111111111111;			//Preambule de 14 bits

	int sw_state, bouton_state;

	int mask_sw_0 = 0b000000000000001;
	int mask_sw_1 = 0b000000000000010;
	int mask_sw_2 = 0b000000000000100;
	int mask_sw_3 = 0b000000000001000;
	int mask_sw_4 = 0b000000000010000;
	int mask_sw_5 = 0b000000000100000;
	int mask_sw_6 = 0b000000001000000;
	int mask_sw_7 = 0b000000010000000;
	int mask_sw_8 = 0b000000100000000;
	int mask_sw_9 = 0b000001000000000;
	int mask_sw_10 = 0b000010000000000;
	int mask_sw_11 = 0b000100000000000;
	int mask_sw_12 = 0b001000000000000;
	int mask_sw_13 = 0b010000000000000;
	int mask_sw_14 = 0b100000000000000;


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

	int adr = 0x00;
	int mode = 0;
	int cmd1 = 0b00000000;
	int cmd2 = 0b00000000;
	int cmd_04 = 0b00000000;
	int cmd_512 = 0b00000000;
	int cmd_1320 = 0b00000000;
	int cmd_s;
	int controler = 0b00000000;
	int step = 0;

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
		int sw_5 = sw_state & mask_sw_5;
		int sw_6 = sw_state & mask_sw_6;
		int sw_7 = sw_state & mask_sw_7;
		int sw_8 = sw_state & mask_sw_8;
		int sw_9 = sw_state & mask_sw_9;
		int sw_10 = sw_state & mask_sw_10;
		int sw_11 = sw_state & mask_sw_11;
		int sw_12 = sw_state & mask_sw_12;
		int sw_13 = sw_state & mask_sw_13;
		int sw_14 = sw_state & mask_sw_14;


		int bp_c = bouton_state & mask_bp_c;
		int bp_l = bouton_state & mask_bp_l;
		int bp_r = bouton_state & mask_bp_r;
		int bp_u = bouton_state & mask_bp_u;
		int bp_d = bouton_state & mask_bp_d;


		if(sw_0 == 0b000000000000001)		//Chose the address of the train
		{
			if(bp_l == 0b00100 && bp_l_pre == 0)
			{
				if(adr == 0x00)
				{
					adr = 0xFF;
				}
				else
				{
					adr --;
				}
			}
			if(bp_r == 0b01000 && bp_r_pre == 0)
			{
				if(adr == 0xFF)
				{
					adr = 0x00;
				}
				else
				{
					adr ++;
				}
			}
			bp_l_pre = bp_l;
			bp_r_pre = bp_r;

            XGpio_DiscreteWrite(&led_sw,2,adr);

		}



		else if(sw_1 == 0b000000000000010)	//Chose the speed of the train ahead
		{
			mode = 22;
			if(bp_l == 0b00100 && bp_l_pre == 0)
			{
				if(step == 0)
				{
					step = 28;
				}
				else
				{
					step =step - 1;
				}
			}
			else if(bp_r == 0b01000 && bp_r_pre == 0)
			{
				if(step == 28)
				{
					step = 0;
				}
				else
				{
					step = step + 1;
				}
			}
			else if(bp_u == 0b00010 && bp_u_pre == 0)
			{
				step = 28;
			}
			else if(bp_d == 0b10000 && bp_d_pre == 0)
			{
				step = 0;
			}

			if(step == 0) cmd1 = 0b01100000;
			else if(step == 1) cmd1 = 0b01100010;
			else if(step == 2) cmd1 = 0b01110010;
			else if(step == 3) cmd1 = 0b01100011;
			else if(step == 4) cmd1 = 0b01110011;
			else if(step == 5) cmd1 = 0b01100100;
			else if(step == 6) cmd1 = 0b01110100;
			else if(step == 7) cmd1 = 0b01100101;
			else if(step == 8) cmd1 = 0b01110101;
			else if(step == 9) cmd1 = 0b01100110;
			else if(step == 10) cmd1 = 0b01110110;
			else if(step == 11) cmd1 = 0b01100111;
			else if(step == 12) cmd1 = 0b01110111;
			else if(step == 13) cmd1 = 0b01101000;
			else if(step == 14) cmd1 = 0b01111000;
			else if(step == 15) cmd1 = 0b01101001;
			else if(step == 16) cmd1 = 0b01111001;
			else if(step == 17) cmd1 = 0b01101010;
			else if(step == 18) cmd1 = 0b01111010;
			else if(step == 19) cmd1 = 0b01101011;
			else if(step == 20) cmd1 = 0b01111011;
			else if(step == 21) cmd1 = 0b01101100;
			else if(step == 22) cmd1 = 0b01111100;
			else if(step == 23) cmd1 = 0b01101101;
			else if(step == 24) cmd1 = 0b01111101;
			else if(step == 25) cmd1 = 0b01101110;
			else if(step == 26) cmd1 = 0b01111110;
			else if(step == 27) cmd1 = 0b01101111;
			else if(step == 28) cmd1 = 0b01111111;

			cmd_s = cmd1;
			bp_l_pre = bp_l;
			bp_r_pre = bp_r;
			bp_u_pre = bp_u;
			bp_d_pre = bp_d;
            XGpio_DiscreteWrite(&led_sw,2,step);
		}


		else if(sw_2 == 0b000000000000100)	//Chose the speed of the train backward
		{
			mode = 22;
			if(bp_l == 0b00100 && bp_l_pre == 0)
			{
				if(step != 0)
				{
					step --;
				}
			}
			else if(bp_r == 0b01000 && bp_r_pre == 0)
			{
				if(step != 28)
				{
					step ++;
				}
			}
			else if(bp_u == 0b00010 && bp_u_pre == 0)
			{
				step = 28;
			}
			else if(bp_d == 0b10000 && bp_d_pre == 0)
			{
				step = 0;
			}

			if(step == 0) {cmd1 = 0b01100000;}
			else if(step == 1)  {cmd1 = 0b01000010;}
			else if(step == 2)  {cmd1 = 0b01010010;}
			else if(step == 3)  {cmd1 = 0b01000011;}
			else if(step == 4)  {cmd1 = 0b01010011;}
			else if(step == 5)  {cmd1 = 0b01000100;}
			else if(step == 6)  {cmd1 = 0b01010100;}
			else if(step == 7)  {cmd1 = 0b01000101;}
			else if(step == 8)  {cmd1 = 0b01010101;}
			else if(step == 9)  {cmd1 = 0b01000110;}
			else if(step == 10) {cmd1 = 0b01010110;}
			else if(step == 11) {cmd1 = 0b01000111;}
			else if(step == 12) {cmd1 = 0b01010111;}
			else if(step == 13) {cmd1 = 0b01001000;}
			else if(step == 14) {cmd1 = 0b01011000;}
			else if(step == 15) {cmd1 = 0b01001001;}
			else if(step == 16) {cmd1 = 0b01011001;}
			else if(step == 17) {cmd1 = 0b01001010;}
			else if(step == 18) {cmd1 = 0b01011010;}
			else if(step == 19) {cmd1 = 0b01001011;}
			else if(step == 20) {cmd1 = 0b01011011;}
			else if(step == 21) {cmd1 = 0b01001100;}
			else if(step == 22) {cmd1 = 0b01011100;}
			else if(step == 23) {cmd1 = 0b01001101;}
			else if(step == 24) {cmd1 = 0b01011101;}
			else if(step == 25) {cmd1 = 0b01001110;}
			else if(step == 26) {cmd1 = 0b01011110;}
			else if(step == 27) {cmd1 = 0b01001111;}
			else if(step == 28) {cmd1 = 0b01011111;}


			bp_l_pre = bp_l;
			bp_r_pre = bp_r;
			bp_u_pre = bp_u;
			bp_d_pre = bp_d;
            XGpio_DiscreteWrite(&led_sw,2,step);
		}

		else if(sw_3 == 0b000000000001000)	//Chose the activation of functions F0-F21
		{
			if(bp_l == 0b00100 && bp_l_pre == 0)
			{
				if(mode != 0)
				{
					mode --;
				}
			}
			else if(bp_r == 0b01000 && bp_r_pre == 0)
			{
				if(mode != 28)
				{
					mode ++;
				}
			}
			else if(bp_u == 0b00010 && bp_u_pre == 0)
			{
				if(mode < 11)
				{
					mode = mode + 10;
				}
			}
			else if(bp_d == 0b10000 && bp_d_pre == 0)
			{
				if(mode > 9)
				{
					mode = mode - 10;
				}
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

            active = 1;
			bp_l_pre = bp_l;
			bp_r_pre = bp_r;
			bp_u_pre = bp_u;
			bp_d_pre = bp_d;
            XGpio_DiscreteWrite(&led_sw,2,mode);
		}

		else if(sw_4 == 0b000000000010000) 	//Chose the dis-activation of the functions F0-21
		{
			if(bp_l == 0b00100 && bp_l_pre == 0)
			{
				if(mode != 0)
				{
					mode --;
				}
			}
			else if(bp_r == 0b01000 && bp_r_pre == 0)
			{
				if(mode != 28)
				{
					mode ++;
				}
			}
			else if(bp_u == 0b00010 && bp_u_pre == 0)
			{
				if(mode < 11)
				{
					mode = mode + 10;
				}
			}
			else if(bp_d == 0b10000 && bp_d_pre == 0)
			{
				if(mode > 9)
				{
					mode = mode - 10;
				}
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

            active = 0;

			bp_l_pre = bp_l;
			bp_r_pre = bp_r;
			bp_u_pre = bp_u;
			bp_d_pre = bp_d;
            XGpio_DiscreteWrite(&led_sw,2,mode);
		}



		if(bp_c == 0b00001 && bp_c_pre == 0)
		{
			if(mode >= 0 && mode <= 4)
			{
                if(active == 1)
                {
                    cmd_04 = cmd_04 | cmd1;
                }
                else
                {
                    cmd_04 = cmd_04 & cmd1;
                }

				controler = adr ^ cmd_04;
				trame = (pre_0 << 50) + (0 << 27) + (adr << 26) + (1 << 18) + (cmd_04 << 17) + (0 << 9) + (controler << 8) + 1;
			}
			else if(mode <= 12 && mode >= 5)
			{
                if(active == 1)
                {
                    cmd_512 = cmd_512 | cmd1;
                }
                else
                {
                    cmd_512 = cmd_512 & cmd1;
                }

				controler = adr ^ cmd_512;
				trame = (pre_0 << 50) + (0 << 27) + (adr << 26) + (1 << 18) + (cmd_512 << 17) + (0 << 9) + (controler << 8) + 1;
			}
			else if(mode <= 20 && mode >= 13)
			{
                if(active == 1)
                {
                    cmd_1320 = cmd_1320 | cmd2;
                }
                else
                {
                    cmd_1320 = cmd_1320 & cmd2;
                }

				controler = adr ^ cmd1 ^ cmd_1320;
				trame = (pre_1 << 50) + (0 << 36) + (adr << 35) + (0 << 27) + (cmd1 << 26) + (0 << 18) + (cmd_1320 << 17) + (0 << 9) + (controler << 8) + 1;
			}
            else if(mode == 22)
            {
                controler = adr ^ cmd_s;
                trame = (pre_0 << 50) + (0 << 27) + (adr << 26) + (1 << 18) + (cmd_s << 17) + (0 << 9) + (controler << 8) + 1;
            }

			bp_c_pre = bp_c;


		}


		MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG0_OFFSET,trame);  //Write the first 26 bits trame in the first register
		MY_TRAME_mWriteReg(XPAR_MY_TRAME_0_S00_AXI_BASEADDR,MY_TRAME_S00_AXI_SLV_REG1_OFFSET,trame>>26);  //Write the second 25 bits trame in the second register
	}
}
