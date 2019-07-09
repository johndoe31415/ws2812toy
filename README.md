# ws2812toy
Simple example of an ATmega88p with a 18.432 MHz external crystal (important
for timing!) that connects to an LED ring with 16 WS2812 RGB LEDs on pin PB0.
Shows some rainbow stripes and thingies.

Note that LEDs are not run at full brightness because power consumption
otherwise would exceed 1A. In current configuration, 500mA are sufficient.

# License
GNU GPL-3.
