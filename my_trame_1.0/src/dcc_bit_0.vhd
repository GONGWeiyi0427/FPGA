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

entity DCC_BIT_0 is
    Port (
        CLK_100MHz: in std_logic;
        CLK_1MHz: in std_logic;
        RESET: in std_logic;
        GO_0: in std_logic;
        FIN_0: out std_logic;
        DCC_0: out std_logic
     );
end DCC_BIT_0;

architecture Behavioral of DCC_BIT_0 is

--Compteur de 100us
signal enable: std_logic;
signal cpt: std_logic_vector(7 downto 0):="00000000"; 
signal cpt_reset: std_logic;

type etat is(INIT,N_BAS,N_HAUT);
signal EP,EF: etat;

begin

    process(RESET,CLK_100MHz)
    begin
        if RESET= '1' then EP <= INIT;
        elsif rising_edge(CLK_100MHz) then EP <= EF;
        end if;
    end process;

    process(EP,GO_0,cpt)
    begin
        case (EP) is
        when INIT => if GO_0 = '1' then EF <= N_BAS; else  EF <= INIT; end if;
        when N_BAS =>  if cpt = "01100100" then EF <= N_HAUT; else EF <= N_BAS; end if;
        when N_HAUT => if cpt = "11001000" then EF <= INIT; else  EF <= N_HAUT; end if;
        end case;
    end process;
    
    process(EP)
    begin
        case (EP) is
            when INIT => DCC_0 <= '0'; cpt_reset <= '1'; enable <= '0';
            when N_BAS => DCC_0 <= '0'; enable <= '1'; cpt_reset <= '0';
            when N_HAUT => DCC_0 <= '1'; enable <= '1'; cpt_reset <= '0';
         end case;
     end process;
     
     --Compteur
     process(CLK_1MHz,RESET,cpt_reset)
     begin
        if (cpt_reset or RESET ) = '1' then cpt <= "00000000"; 
        elsif rising_edge(CLK_1MHz) then 
            if enable = '1' then
                cpt <= cpt + '1';
            else
                cpt <= cpt;
            end if;
        end if;
     end process;
    
    FIN_0 <= '1' when cpt = "11001000" else '0';

end Behavioral;