----------------------------------------------------------------------------------
-- Company: 
-- Engineer: GONG Weiyi, WEN Zhuyu
-- 
-- Create Date: 2023/03/21 11:15:11
-- Design Name: 
-- Module Name: DCC_BIT_1 - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity DCC_BIT_1 is
    Port (
        CLK_100MHz: in std_logic;
        CLK_1MHz: in std_logic;
        RESET: in std_logic;
        GO_1: in std_logic;
        FIN_1: out std_logic;
        DCC_1: out std_logic
     );
end DCC_BIT_1;

architecture Behavioral of DCC_BIT_1 is

--Compteur de 100us
signal start: std_logic;
signal cpt: std_logic_vector(7 downto 0):="00000000"; 
signal done_bas,done_haut: std_logic;

type etat is(INIT,N_BAS,N_HAUT);
signal EP,EF: etat;

begin

    process(RESET,CLK_100MHz)
    begin
        if RESET= '0' then EP <= EF;
        elsif rising_edge(CLK_100MHz) then EP <= EF;
        end if;
    end process;

    process(EP,GO_1,done_bas,done_haut)
    begin
        case (EP) is
        when INIT => EF <= INIT; if GO_1 = '1' then EF <= N_BAS; end if;
        when N_BAS => EF <= N_BAS; if done_bas = '1' then EF <= N_HAUT; end if;
        when N_HAUT => EF <= N_HAUT; if done_haut = '1' then EF <= INIT; end if;
        end case;
    end process;
    
    process(EP)
    begin
        case (EP) is
            when INIT => FIN_1 <= '0'; start <= '0';
            when N_BAS => FIN_1 <= '0'; DCC_1 <= '0'; start <= '1';
            when N_HAUT => FIN_1 <= '0'; DCC_1 <= '1'; start <= '1';
         end case;
     end process;
     
     --Compteur
     process(CLK_1MHz,start,cpt)
     begin
        if start = '0' then cpt <= "00000000"; 
        elsif start = '1' and rising_edge(CLK_1MHz) then cpt <= cpt + '1';
        end if;
        if cpt = "01100100" then done_bas <= '1';
        elsif cpt = "11001000" then done_haut <= '1';
        end if;
     end process;
     
     



end Behavioral;