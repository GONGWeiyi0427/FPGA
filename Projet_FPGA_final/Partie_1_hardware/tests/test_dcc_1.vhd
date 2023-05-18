----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 2023/03/21 12:09:50
-- Design Name: 
-- Module Name: TEST_DCC_BIT_1 - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity TEST_DCC_BIT_1 is
--  Port ( );
end TEST_DCC_BIT_1;

architecture Behavioral of TEST_DCC_BIT_1 is
    signal CLK_100MHz: std_logic:='0';
    signal CLK_1MHz : std_logic:='0';
    signal RESET : std_logic:='1';
    signal GO_1: std_logic;   --inputs
    signal FIN_1 ,DCC_1 :std_logic;      --outputs
    
       
begin
    simu : entity work.DCC_BIT_1 port map(CLK_100MHz=>CLK_100MHz, 
                                          CLK_1MHz=>CLK_1MHz, 
                                          RESET=>RESET, 
                                          GO_1=>GO_1,
                                          FIN_1=>FIN_1,
                                          DCC_1=>DCC_1);
                                          
CLK_1MHz <= not CLK_1MHz after 0.5 us;
CLK_100MHz <= not CLK_100MHz after 5 ns;
RESET<= '0' after 5 us;
GO_1<='1' after 5 us, '0' after 25 us, '1' after 500 us, '0' after 520 us;


end Behavioral;