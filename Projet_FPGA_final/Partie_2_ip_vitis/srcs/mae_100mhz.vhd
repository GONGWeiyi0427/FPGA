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
     fetched: in std_logic;
     fin_trame: in std_logic;
     COM_REG: out std_logic_vector(1 downto 0);
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

--MAE
type etat is(S0,S1,S2,S3,S4,S5);
signal EP,EF: etat;

begin

    process(RESET,CLK_100MHz)
    begin
        if RESET= '1' then EP <= S0;
        elsif rising_edge(CLK_100MHz) then EP <= EF;
        end if;
    end process;


 process(EP,DCC_BIT,FIN_TEMPO,FIN_1,FIN_0,fetched,fin_trame)
    begin
        case (EP) is
        when S0 => EF <= S0; if fetched = '1' then EF <= S1; end if;
        when S1 => EF <= S1; if DCC_BIT = '1' then EF <= S2; elsif DCC_BIT = '0' then EF <= S3; end if;
        when S2 => EF <= S2; if FIN_1 = '1' then EF <= S4; end if;
        when S3 => EF <= S3; if FIN_0 = '1' then EF <= S4; end if;
        when S4 => EF <= S4; if fin_trame = '1' then EF <= S5; else EF <= S1; end if;
        when S5 => EF <= S5; if FIN_TEMPO = '1' then EF <= S0; end if; 
        end case;
 end process;

 process(EP)
 begin
    
     case (EP) is
        when S0 => START_TEMPO <= '0'; COM_REG <= "01"; GO_1 <= '0'; GO_0 <= '0';
        when S1 => COM_REG <= "10"; GO_1 <= '0'; GO_0 <= '0'; START_TEMPO <= '0';
        when S2 => GO_1 <= '1'; GO_0 <= '0'; COM_REG <= "00"; START_TEMPO <= '0';
        when S3 => GO_0 <= '1'; GO_1 <= '0'; COM_REG <= "00"; START_TEMPO <= '0';
        when S4 => GO_1 <= '0'; GO_0 <= '0'; COM_REG <= "00"; START_TEMPO <= '0';
        when S5 => START_TEMPO <= '1'; COM_REG <= "00"; GO_1 <= '0'; GO_0 <= '0';
        --when others => NULL;
     end case;
 end process;
 
 



end Behavioral;