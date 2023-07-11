# 3d_printer_housing
This repo is to control diffrent functionalitys for an self-build housing of a 3d FDM printer.

Setup:
- Anycubic Cobra Plus
- Raspberry Pi 3A+
- STM32F103 (Bluepill)
- 3 Button
- WS2811 RGB Leds
- MQ-2 Gas sensor
- electric controlled magnetic pneumatic valve
- 450ml Sodastream (CO2)


The printer is controlled by the Raspberry Pi with klipper firmware. To include diffrent led shows depending on printing status, there are multiple simple gpio inputs coming from the pi to the stm32. 

The MQ-2 sensor is used to detect a fire inside the casing. An CO2 fire extinguisher is euqiped (selfbuild), based on a sodastream CO2 gas bottle to extinguish the fire. 

Overall the stm32 controls:
- RGB LEDs
- MQ2 data read out
- electric pneumatic valve (fire extinguisher)
- beeper
- printer pwr sply
