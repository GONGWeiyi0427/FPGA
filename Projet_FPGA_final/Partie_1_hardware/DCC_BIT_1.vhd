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
        CLK_100MHz: in std_logic;                                           --CLK to generate fsm
        CLK_1MHz: in std_logic;                                             --CLK to generate the counter
        RESET: in std_logic;
        GO_1: in std_logic;                                                 --bit of active
        FIN_1: out std_logic;                                               --bit of end
        DCC_1: out std_logic                                                --output wave
     );
end DCC_BIT_1;

architecture Behavioral of DCC_BIT_1 is

--Compteur de 100us
signal start: std_logic;
signal cpt: std_logic_vector(6 downto 0):="0000000"; 
signal done_bas,done_haut: std_logic;

type etat is(INIT,N_BAS,N_HAUT);
signal EP,EF: etat;

begin

    process(RESET,CLK_100MHz)
    begin
        if RESET= '0' then EP <= INIT;
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
            when INIT => DCC_1 <= '0';start <= '0';
            when N_BAS => DCC_1 <= '0'; start <= '1';
            when N_HAUT => DCC_1 <= '1'; start <= '1';
         end case;
     end process;
     
     --Compteur
     process(CLK_1MHz,start,cpt)
     begin
        if start = '0' then cpt <= "0000000"; done_bas <= '0'; done_haut <= '0'; FIN_1 <= '0';
        elsif start = '1' and rising_edge(CLK_1MHz) then cpt <= cpt + '1';
        end if;
        if cpt = "0011101" then done_bas <= '1';                                                    -- If the counter counts to 58, then it's the end of the state
        elsif cpt = "111010" then done_haut <= '1'; FIN_1 <= '1';                                   -- If the counter counts to 116, then it's the end of the state, and it's all the end
        end if;
     end process;
     
     



end Behavioral;
