----------------------------------------------------------------------------------
-- Company: UPMC
-- Engineer: Weiyi GONG/Zhuyu WEN
-- 
-- Create Date: 2023/02/04 14:48:00
-- Design Name: 
-- Module Name: test - Behavioral
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

entity test is
   Port (SW0,SW1,SW2: in std_logic;
         LED: out std_logic_vector(2 downto 0));
end test;

architecture Behavioral of test is

begin
    LED(0) <= SW0;
    LED(1) <= SW1;
    LED(2) <= SW0 and SW1 and SW2;

end Behavioral;
