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

entity TEST_Reg_DCC is
--  Port ( );
end TEST_Reg_DCC;

architecture Behavioral of TEST_Reg_DCC is
    signal CLK_100MHz: std_logic:='0';
    signal COM_REG : std_logic:='0';
    signal RESET : std_logic:='0';
    signal TRAME_DCC : std_logic_vector(50 downto 0);   --inputs
    signal DCC_BIT :std_logic;      --outputs
    
       
begin
    simu : entity work.Reg_DCC port map(CLK_100MHz=>CLK_100MHz, 
                                          COM_REG=>COM_REG, 
                                          RESET=>RESET, 
                                          TRAME_DCC=>TRAME_DCC,
                                          DCC_BIT=>DCC_BIT);
                                          
CLK_100MHz <= not CLK_100MHz after 10 ns;
RESET <= '1' after 5 us;
COM_REG <= '1' after 6 us, '0' after 70 us, '1' after 75 us; 
TRAME_DCC <= "100101010101010101010101010101010101010101010101001" after 5 us;


end Behavioral;
