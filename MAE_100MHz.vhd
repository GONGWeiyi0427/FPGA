----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 2023/03/21 10:57:36
-- Design Name: 
-- Module Name: MAE_100Hz - Behavioral
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

entity MAE_100MHz is
    Port (
     -- Parametre Generale
     CLK_100MHz: in std_logic;
     RESET: in std_logic;
     -- Registre DCC
     DCC_BIT: in std_logic;
     COM_REG: out std_logic;
     -- TEMPO
     START_TEMPO: out std_logic;
     FIN_TEMPO: in std_logic;
     -- DCC_BIT_1
     GO_1: out std_logic;
     FIN_1: in std_logic;
     -- DCC_BIT _0
     GO_0: out std_logic;
     FIN_0: in std_logic
         
     );
end MAE_100MHz;

architecture Behavioral of MAE_100MHz is

signal last: std_logic;
signal cpt: INTEGER range 51 to 0;

--MAE
type etat is(S0,S1,S2,S3,S4,S5);
signal EP,EF: etat;

begin

    process(RESET,CLK_100MHz)
    begin
        if RESET= '0' then EP <= S0;
        elsif rising_edge(CLK_100MHz) then EP <= EF;
        end if;
    end process;


 process(EP,DCC_BIT,FIN_TEMPO,FIN_1,FIN_0)
    begin
        case (EP) is
        when S0 => EF <= S1;
        when S1 => EF <= S1; if DCC_BIT = '1' then EF <= S1; elsif DCC_BIT = '0' then EF <= S2; end if;
        when S2 => EF <= S2; if FIN_1 = '1' then EF <= S4; end if;
        when S3 => EF <= S3; if FIN_0 = '1' then EF <= S4; end if;
        when S4 => EF <= S4; if last = '1' then EF <= S5; elsif last = '0' then EF <= S1; end if;
        when S5 => EF <= S5; if FIN_TEMPO = '1' then EF <= S0; end if; 
        end case;
 end process;

 process(EP)
 begin
     case (EP) is
        when S0 => COM_REG <= '0';
        when S1 => COM_REG <= '1'; cpt <= cpt + 1;
        when S2 => GO_1 <= '1';
        when S3 => GO_0 <= '1';
        when S5 => START_TEMPO <= '1'; 
     end case;
 end process;
 
 
 --COMPTEUR POUR INDIQUER SI C'EST LE DERNIER SIGNAL POUR LE TRAME_DCC
last <= '1' when cpt = 51;

end Behavioral;
