----------------------------------------------------------------------------------
-- Company: UPMC
-- Engineer: Julien Denoulet
-- 
-- Create Date:   	Septembre 2016 
-- Module Name:    	Impulse_Count - Behavioral 
-- Project Name: 		TP1 - FPGA1
-- Target Devices: 	Nexys4 / Artix7

-- XDC File:			Impulse_Count.xdc					

-- Description: Compteur d'Impulsions - Version KO
--
--		Compteur d'Impulsions sur 4 bits
--			- Le Compteur s'Incrémente si on Appuie sur le Bouton Left
--			- Le Compteur se'Décrémente si on Appuie sur le Bouton Center
--			- Sup Passe ? 1 si le Compteur Dépasse 9
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity IMPULSE_COUNT is
    Port ( Reset : in  STD_LOGIC;								-- Reset Asynchrone
           Button_L : in  STD_LOGIC;							-- Bouton Left
           Button_C : in  STD_LOGIC;							-- Bouton Center
           clk : in STD_LOGIC;
           Count : out  STD_LOGIC_VECTOR (3 downto 0);	-- Compteur d'Impulsions
           Sup : out  STD_LOGIC);								-- Indicateur Valeur Seuil
end IMPULSE_COUNT;

architecture Behavioral of IMPULSE_COUNT is

signal cpt: std_logic_vector(3 downto 0);		-- Compteur d'Impulsions
signal q1,q2: std_logic;  -- Signaux pour enregister les valeurs pr¨¦cedents des boutons


begin
	count <= cpt;	-- Affichage en Sortie du Compteur
	
	


	-------------------------
	-- Gestion du Compteur --
	-------------------------
	process(reset,clk)

	begin
    
		-- Reset Asynchrone
		if reset='1' then cpt<="0000"; end if;
         
            -- Incrémentation Si on Appuie sur le Bouton Left
        if rising_edge(clk) then
            if((Button_L = '1') and (q1 = '0')) then  --si la valeur pr¨¦sente est 1 et la valeur pr¨¦cedente est 0,alors le bouton a ¨¦t¨¦ pouss¨¦
                q1 <= '1';                            --remplace la valeur pr¨¦c¨¦dente par la valeur pr¨¦sente
                cpt <= cpt + '1';                     --nous commencons le cpt
            elsif (Button_L = '0') then
                q1 <= '0';                            --nous faisons rien quand q1=0
            end if;
            
            if((Button_C = '1') and (q2 = '0')) then  --si la valeur pr¨¦sente est 1 et la valeur pr¨¦cedente est 0,alors le bouton a ¨¦t¨¦ pouss¨¦
                q2 <= '1';                            --le m¨ºme que l'avant
                cpt <= cpt - '1';
            elsif (Button_C = '0') then
                q2 <= '0';
            end if;
            
        end if;
            
		
	end process;

	-------------------------
	-- Gestion du Flag Sup --
	-------------------------
	process(Cpt)

	begin
		
		-- Mise ? 1 si CPT Dépasse 9. A 0 Sinon...
		if (cpt > 9) then 			
			Sup<='1'; 									
		else 							
			Sup<='0'; 
		end if;
	end process;

end Behavioral;

