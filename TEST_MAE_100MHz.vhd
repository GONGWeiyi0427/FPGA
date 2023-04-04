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

entity TEST_MAE_100MHz is
--  Port ( );
end TEST_MAE_100MHz;

architecture Behavioral of TEST_MAE_100MHz is
    signal CLK_100MHz: std_logic:='0';
    signal RESET : std_logic:='0';
    signal FIN_1: std_logic;
    signal FIN_0: std_logic;
    signal FIN_TEMPO: std_logic;
    signal DCC_BIT: std_logic;   --inputs
    signal COM_REG ,START_TEMPO,GO_1,GO_0 :std_logic;      --outputs
    
       
begin
    simu : entity work.MAE_100MHz port map(CLK_100MHz=>CLK_100MHz,         
                                          RESET=>RESET, 
                                          GO_0=>GO_0,
                                          GO_1=>GO_1,
                                          FIN_0=>FIN_0,
                                          FIN_1=>FIN_1,
                                          DCC_BIT=>DCC_BIT,
                                          FIN_TEMPO=>FIN_TEMPO,
                                          COM_REG=>COM_REG,
                                          START_TEMPO=>START_TEMPO);
                                          

CLK_100MHz <= not CLK_100MHz after 10 ns;
RESET<='1' after 5 us;
FIN_1<='1' after 10us;
FIN_0<='1' after 15us;
FIN_TEMPO<='1' after 200us;
DCC_BIT<='1' after 6us;


end Behavioral;
