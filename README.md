# feather-blinkelights
Blinkenlights display using an Adafruit Neopixel Featherwing and Feather module


The feather registers itself as i2c device 0x14.

On a Raspberry Pi4:
  > pip install psutil
  
  > python interface.py &

This will send the status of all 4 CPU cores to the Feather which will update it's display to show current activity.
If the CPU is idle, the Feather will begin displaying random data.
 
