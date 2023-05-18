----------------------------------------------------------------------------------
-- Company: 
-- Engineer: GONG Weiyi, WEN Zhuyu
-- 
-- Create Date: 2023/03/21 12:16:49
-- Design Name: 
-- Module Name: REG_DCC - Behavioral
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
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity REG_DCC is
    Port (
        --Parametre general
        CLK_100MHz: in std_logic;
        RESET: in std_logic;
        
        COM_REG: in std_logic_vector(1 downto 0); --01 read, 10 send 1 bit
        TRAME_DCC: in std_logic_vector(50 downto 0);
        
        fetched: out std_logic;
        fin_trame: out std_logic;
        DCC_BIT: out std_logic
     );
end REG_DCC;

architecture Behavioral of REG_DCC is

signal cpt: INTEGER range 0 to 51;
signal trame: std_logic_vector(51 downto 0);

begin

process(CLK_100MHz,RESET)
--variable trame_tempo: std_logic;
begin
    if RESET = '1' then cpt <= 1; trame <= (others => '1'); DCC_BIT <= '1';
    elsif rising_edge(CLK_100MHz) then
        if COM_REG = "10" and cpt <= 51 and cpt >= 1 then 
            DCC_BIT <= trame(51-cpt); 
            cpt <= cpt + 1;
            if cpt = 51 then
                fin_trame <= '1';
            else 
                fin_trame <= '0';
            end if;
        elsif COM_REG = "01" then 
            trame <= Trame_DCC & '1'; 
            if trame = Trame_DCC & '1' then
                fetched <= '1';
            else 
                fetched <= '0';
            end if;
            cpt <= 1;
        else
            cpt <= cpt;
        end if;
     end if;
    
    --DCC_BIT <= trame_tempo;
end process;

    --fetched <= '1' when trame = TRAME_DCC else '0';

end Behavioral;
