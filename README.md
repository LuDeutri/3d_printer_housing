# 3d_printer_housing
This repo is to control diffrent functionalitys for an self-build housing of a 3d FDM printer based on klipper with an Raspberry Pi 4B and one STM32F103 bluepill board. An fire extinguisher system based on CO2 is included.

![printer_view](https://github.com/LuDeutri/3d_printer_housing/assets/56504337/b51a1fef-8035-451d-b42c-b65f21fda6cf)
![printing_nozzle](https://github.com/LuDeutri/3d_printer_housing/assets/56504337/521e05f5-b340-4939-a73a-2c0d5451e58d)

## Setup:
- Anycubic Cobra Plus
- Raspberry Pi 4B
- STM32F103 (Bluepill)
- 3 Button (Fire_butn, Led_btn, PrinterSply_btn)
- WS2811 RGB Leds
- MQ-2 Gas sensor
- electric controlled magnetic pneumatic valve
- 450ml Sodastream (CO2)
- OSOYOO DSI display 5 zoll
- 12V Beeper
- 1x DSI pi camera, 1x usb pi camera
- 1x be quiet pwm fan
- multiple MOSFET switches

## Controller:
The main part is running on the stm32, the pi mainly controls the printer together with the printer hardware (HC32F460).
The stm32 and the pi are stacked and communcicate to each other about a simple GPIO bit communcication. With that the RGB leds and printer supply can be controlled in the webinterface.

<img src="https://github.com/LuDeutri/3d_printer_housing/assets/56504337/8811c318-8b6d-4fd3-884b-74065f6b2175" width=400 height=400>  <img src="https://github.com/LuDeutri/3d_printer_housing/assets/56504337/11fcde93-7293-454f-b73f-eda6e998e272" width=400 height=400>
<img src="https://github.com/LuDeutri/3d_printer_housing/assets/56504337/031cb212-3798-4427-9629-acbafadf9874" width=400 height=400> <img src="https://github.com/LuDeutri/3d_printer_housing/assets/56504337/9b283681-30cc-4830-abf1-0b014e9d6540" width=400 height=400>

**Bluepill:**
- RGB Leds (PWM with DMA data signal)
- MQ-2 gas sensor data read out
- Fire extinguisher (electronic controlled pneumatic valve)
- Buttons state
- Printer supply (2 MOSFET switches: L and N)
- Beeper (used for fire alarm)

**Pi:**
- Printer control (Klipper, webinterface Mainsail)
- Display (klipperScreen)
- DSI, USB camera (crowsnest)
- Cooling fan (controlled by pid regulator)


## Fire extinguisher:
The MQ-2 sensor is used to detect a fire inside the casing. The extinguisher is based on a sodastream CO2 gas bottle and a electronic controlled pneumatic valve to extinguish the fire.
Beside the sensor, an button at the side of the case can be used to activate the fire extiguisher or to deactivate the alarm sequence. An beeper and red fading leds are used to indicate the alarm.

<img src="https://github.com/LuDeutri/3d_printer_housing/assets/56504337/c0c3d8df-2594-4686-ada3-b9922420f164" width=400 height=400>
<img src="https://github.com/LuDeutri/3d_printer_housing/assets/56504337/306debc8-372d-4306-9df9-7ea39422a4a8" width=400 height=400>

