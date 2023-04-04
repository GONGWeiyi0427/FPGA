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
use ieee.std_logic_unsigned.all;

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
     --FETCH: in std_logic;
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
signal cpt: INTEGER range 0 to 51;

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
        when S1 => EF <= S1; if DCC_BIT = '1' then EF <= S2; elsif DCC_BIT = '0' then EF <= S3; end if;
        when S2 => EF <= S2; if FIN_1 = '1' then EF <= S4; end if;
        when S3 => EF <= S3; if FIN_0 = '1' then EF <= S4; end if;
        when S4 => EF <= S4; if cpt > 50 then EF <= S5; elsif cpt <= 50 then EF <= S1; end if;
        when S5 => EF <= S5; if FIN_TEMPO = '1' then EF <= S0; end if; 
        end case;
 end process;

 process(EP)
 begin
    
     case (EP) is
        when S0 => START_TEMPO <= '0'; COM_REG <= '0'; cpt <= 0; GO_1 <= '0'; GO_0 <= '0';
        when S1 => COM_REG <= '1'; cpt <= cpt + 1; GO_1 <= '0'; GO_0 <= '0'; START_TEMPO <= '0';
        when S2 => GO_1 <= '1'; GO_0 <= '0'; COM_REG <= 'U'; START_TEMPO <= '0'; cpt <= cpt;
        when S3 => GO_0 <= '1'; GO_1 <= '0'; COM_REG <= 'U'; START_TEMPO <= '0'; cpt <= cpt;
        when S4 => GO_1 <= '0'; GO_0 <= '0'; COM_REG <= 'U'; START_TEMPO <= '0'; cpt <= cpt;
        when S5 => START_TEMPO <= '1'; COM_REG <= 'U'; GO_1 <= '0'; GO_0 <= '0'; cpt <= cpt;
        --when others => NULL;
     end case;
 end process;
 
 
 --COMPTEUR POUR INDIQUER SI C'EST LE DERNIER SIGNAL POUR LE TRAME_DCC
last <= '1' when cpt = 51;

end Behavioral;