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
use IEEE.std_logic_unsigned;

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
    RESET: in std_logic;
    sortie_dcc: out std_logic
     );
end TOP_miniprojet;

architecture Behavioral of TOP_miniprojet is
   signal Clk :  STD_LOGIC;		-- Horloge 100 MHz
   signal Clk1M:  STD_LOGIC;		-- Horloge 1 MHz
   signal Start_Tempo:  STD_LOGIC;		-- Commande de D?marrage de la Temporisation
   signal Fin_Tempo:  STD_LOGIC;		-- Drapeau de Fin de la Temporisation
   signal GO_0:  std_logic;
   signal FIN_0:  std_logic;
   signal DCC_0:  std_logic;
   signal GO_1:  std_logic;
   signal FIN_1:  std_logic;
   signal DCC_1:  std_logic;
   signal DCC_BIT:  std_logic;
   signal COM_REG:  std_logic_vector(1 downto 0);
   signal TRAME_DCC:  std_logic_vector(50 downto 0);
   signal Clk_In:  STD_LOGIC;		-- Horloge 100 MHz de la carte Nexys
   signal Clk_Out:  STD_LOGIC;
   signal fetched: std_logic;
   signal fin_trame: std_logic;

begin
diviseur_horloge: entity work.CLK_DIV port map
(
     Reset=>RESET,
     Clk_In=>clk100MHz,
     Clk_Out=>Clk1M
 );

compteur_tempo: entity work.COMPTEUR_TEMPO port map
(
     Clk=>clk100MHz, -- Horloge 100 MHz
     Reset=>RESET,				-- Reset Asynchrone
     Clk1M =>Clk1M,				-- Horloge 1 MHz
     Start_Tempo=>Start_Tempo,		-- Commande de D?marrage de la Temporisation
     Fin_Tempo=>Fin_Tempo	
);

dcc_bit_0 : entity work.DCC_BIT_0 port map
(
     CLK_100MHz=>clk100MHz,
     CLK_1MHz=>Clk1M,
     RESET=>RESET,
     GO_0=>GO_0,
     FIN_0=>FIN_0,
     DCC_0=>DCC_0
);

dcc_bit_1 : entity work.DCC_BIT_1 port map
(    
     CLK_100MHz=>clk100MHz,
     CLK_1MHz=>Clk1M,
     RESET=>RESET,
     GO_1=>GO_1,
     FIN_1=>FIN_1,
     DCC_1=>DCC_1
);

mae :  entity work.MAE_100MHz port map
(
     CLK_100MHz=>clk100MHz,
     RESET=>RESET,
     DCC_BIT=>DCC_BIT,
     fetched=>fetched,
     fin_trame=>fin_trame,
     COM_REG=>COM_REG,
     START_TEMPO=>Start_Tempo,
     FIN_TEMPO=>Fin_Tempo,
     GO_1=>GO_1,
     FIN_1=>FIN_1,
     GO_0=>GO_0,
     FIN_0=>FIN_0
);

reg_dcc :entity work.Reg_DCC port map
(
     CLK_100MHz=>clk100MHz,
     RESET=>RESET,
     COM_REG=>COM_REG,
     TRAME_DCC=>TRAME_DCC,
     fetched=>fetched,
     fin_trame=>fin_trame,
     DCC_BIT=>DCC_BIT
);

trame_gen: entity work.DCC_FRAME_GENERATOR port map
(
    Interrupteur => interrupteurs,
    Trame_DCC => TRAME_DCC
);

sortie_dcc <= DCC_1 xor DCC_0;

end Behavioral;