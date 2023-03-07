library IEEE;
use IEEE.std_logic_1164.ALL;

entity my_led is
port(
    sw_state: in std_logic_vector(3 downto 0);
    leds: out std_logic_vector(15 downto 0)
);
end my_led;

architecture Behavioral of my_led is
begin
leds(3 downto 0)<="1111" when sw_state(0)='1' else "0000";
leds(7 downto 4)<="1111" when sw_state(1)='1' else "0000";
leds(11 downto 8)<="1111" when sw_state(2)='1' else "0000";
leds(15 downto 12)<="1111" when sw_state(3)='1' else "0000";


end Behavioral;