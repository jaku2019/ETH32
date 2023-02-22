# Supla powered ETH32 light coontroller
Thanks to the amazing help of @elmaya @radzik_r @klew and othher forum.supla.org users I managed to create ETH32 light controller.
![alt text](https://github.com/jaku2019/ETH32/blob/main/photos/readme_photo.png?raw=true)
## Main characteristics
- 17 230V inputs (in the photo sample: 16x230V 1x12V) [PC814]
- 18 230V 5A inputs [HF46F/12V]
- TEST button that turns on all the relays (you can change that function in the code)
- LAN8721
- 2xMCP23017 (there is a possibility to channge its addresses with DIN switches)
- easy-access pins: 3,3V, 5V, GND, IO12, IO15, IO35, IO36, IO39, IO0, RX, TX
- easy access to I2C pins
- MCP9808 temperature sensor (there is a possibility to channge its address with DIN switch)
- RTC clock DS3231
- FRAM memory MB85RC256V (there is a possibility to channge its address with DIN switch)

## Info
Instead of soldering the buck converter elements to the PCB, you can insert a ready module LM2596 (it is necessary to set its output voltage to 5V)

ESP is connected with IO by MCP23017. One of this modules was placed on a card that is a bit loose. You shouldn't play with it when ETH32 is on, as it could make the relays stop working. Repositioning it to 90 degrees should solve the problem.

The PCB is designed to fit perfectly to the Kradex ZD1012 enclosure fr DIN rail.
## The code
In the software example relays no. 101-116 have assigned inputs with relative numbers. 

Input no. 117 turns on all the relays. 
Single click = turn on all,
Double click = turn off all. 

Everything is preperad to work with moonostable buttons. 

There is no thermometer, FRAM memory nor RTC support yet.
## Smart home control
You need to set your Supla accunt mail and server address in the coode (relative fields are placed in the bottom of the code).

You can integrate Supla with e.g. Home Assistant via MQTT. The setup is pretty easy and reliable. https://en-forum.supla.org/viewtopic.php?t=10419
