----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 2023/04/04 09:29:24
-- Design Name: 
-- Module Name: test_top - Behavioral
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

entity test_top is
--  Port ( );
end test_top;

architecture Behavioral of test_top is

signal interrupteurs: std_logic_vector(7 downto 0);
signal clk100MHz: std_logic := '0';
signal reset: std_logic := '1';
signal sortie_dcc: std_logic;

begin

    simu : entity work.TOP_miniprojet port map
    (
    interrupteurs => interrupteurs,
    clk100MHz => clk100MHz,
    reset => reset,
    sortie_dcc => sortie_dcc
    );

    reset <= '0' after 5 us;
    clk100MHz <= not clk100MHz after 5 ns;
--    interrupteurs(7) <= '1' after 10 us;
--    interrupteurs(6) <= '1' after 20 us;
--    interrupteurs(5) <= '1' after 30 us;
--    interrupteurs(4) <= '1' after 40 us;
--    interrupteurs(3) <= '1' after 50 us;
--    interrupteurs(2) <= '1' after 60 us;
--    interrupteurs(1) <= '1' after 70 us;
--    interrupteurs(0) <= '1' after 80 us;
    interrupteurs <= "00000010";

end Behavioral;
