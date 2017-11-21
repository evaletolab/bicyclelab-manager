# Simple Wireless bicycle controller
This project depends on battery and charger from [evaletolab/bicyclelab-charger](../../../bicyclelab-charger)

All that stuff are plugged and tested here!
![live testing](http://ucarecdn.com/42edabe7-46ce-4520-a1de-0e63eb6efe72/-/scale_crop/800x700/center/)

## Wireless switch (ON/OFF)
![wireless switch](http://ucarecdn.com/3769ae40-b797-4a02-8fcf-6ca95b9bdaef/-/resize/800x600/)
* the on/off switch is coupled with the integrated signal from the XYZ accelerometer.


## Features
1. Control electric bicycle plugged with the battery [evaletolab/bicyclelab-charger](../../../bicyclelab-charger),
2. 16kb flash,
3. Sensors for battery current and battery voltage,
3. 3 axis accelerometer available (automatic force detection to control motor power),
3. RFM12b for IO
4. controll external ESC with PWM or voltage
2. full protections: Short circuit / Overload / Over voltage 
7. small size, only ~23x48x4mm

![The PCB board](https://raw.github.com/evaletolab/bicyclelab-manager/master/docs/pcb.png "controller v0.0")



**THIS IS ALPHA SOFTWARE/HARDWARE AND SHOULD BE TREATED ACCORDINGLY.**
**IT IS FUN TO GET RUNNING, BUT EXPECT THINGS TO BE BROKEN.**
 
## License
GPL3

Copyright (c) 2012 Olivier Evalet (http://evaletolab.ch/)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the “Software”), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
