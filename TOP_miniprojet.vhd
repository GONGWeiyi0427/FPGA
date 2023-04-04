----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 2023/03/28 12:27:34
-- Design Name: 
-- Module Name: TOP_miniprojet - Behavioral
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

entity TOP_miniprojet is 
    Port (
    interrupteurs: in std_logic_vector(7 downto 0);
    clk100MHz: in std_logic;
    reset: in std_logic;
    sortie_dcc: out std_logic
     );
end TOP_miniprojet;

architecture Behavioral of TOP_miniprojet is

begin


end Behavioral;
