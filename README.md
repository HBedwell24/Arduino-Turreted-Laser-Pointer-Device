Arduino Turreted Laser Pointer Device
=========================================================================
A device forged to supply the niche of keeping household pets occupied in an autonomous nature through the culmination of various hardware components (Adafruit Mini Pan-Tilt Kit, a sensor shield, a 6V/2A power supply, a laser diode, a HC-05 Bluetooth module, and an Arduino UNO Rev 3), as well as an Android application external to the configuration (which performed the role of sending signals to the Arduino through Serial communication, which could then be represented accordingly in the Arduino’s C/C++ codebase). 

Materials Checklist
------------------------------------------------------------------------
For the general assembly of the remote-controlled catapult device, the electronics parts will consist of an Arduino UNO REV3, a RobotGeek Sensor Shield (V2), an Adafruit Mini Pan-Tilt Kit (assembled or unassembled, it is really up to personal preference), a 5mW 650nm laser diode (also from Adafruit), an HC-05 Bluetooth Transmission Module, a Full Sized Breadboard, a 6V Power Supply, six Female/Male Jumper Wires of colors red (2x), black (2x), blue (1x), and green (1x) (any length jumper wires will suffice), a 1K Ohm ¼ Watt PTH resistor, and a 2.2K Ohm ¼ Watt Carbon Film Resistor. The RobotGeek Sensor Shield is compatible with any Arduino board, so the Sensor Shield male header pins should fit perfectly with the female header pins of the Arduino UNO REV3, just make sure that the male header pins aren’t bent when exerting force down on the Sensor Shield to attach it to the Arduino board. Conveniently, the Sensor Shield converts the Arduino’s Digital IO pins into 3-pin adapters, so that it is easier to add servos and other sensors to the project. 

Device Construction
------------------------------------------------------------------------
Under the group of pins labeled Voltage In (VIN), attach one servo to DIO-10 and the other to DIO-11. This is so that the servos draw power from the 6V Power Supply, rather than from the Arduino’s built-in 5V regulator which would limit the servo’s range of rotation. It is important to make sure that the orange wire on each servo corresponds to the Signal (S) pin, the red wire to the Voltage (V) pin, and the brown wire to the Ground (G) pin; otherwise, the current will likely burn out the servos. Now, take the female end of the blue jumper wire and attach it to the Signal (S) pin of DIO-12 (this will be your RX pin by which you receive serial data from the HC-05). Repeat the same for the female end of the green jumper wire on the Signal (S) pin of DIO-13 (this will be your TX pin by which you transmit serial data to the HC-05). When attaching the 5mW laser diode to the sensor shield, the diode will feature two wires: a red wire for power and a black wire for ground. Unfortunately, both wires lack header pins to mount directly to the sensor shield, so this is where two of the remaining red and black female/male jumper wires (one of each) will come into play. Cut each of the female/male jumper wires in half, making sure to use the halves with the female header pins; the other halves of the wires may be disposed of. Strip the insulation off the end of the wire halves and also off the diode wires. Using a twist-on wire connector, bind the exposed end of the red wire halve to the exposed end of the red diode wire. Repeat this step with another twist-on-wire connector, this time for the set of black wires. Now, simply attach the female end of the red wire to the Signal (S) pin and the female end of the black wire to the Ground (G) pin of DIO-2. Lastly, to finish off with the connections to the Sensor Shield, take the female end of the remaining red jumper wire and attach it to the 5V pin and attach the female end of the remaining black jumper wire to the GND pin. The configuration of the Sensor Shield should look identical to the image provided below.

![Wiring Diagram](images/wiring-diagram.jpg?raw=true "RobotGeek Sensor Shield Wiring Schematics")

The next step is to attach the male ends of the jumper wires to the breadboard. You will need the breadboard, the HC-05 Bluetooth Module, the 1K Ohm ¼ Watt resistor, and the 2.2K Ohm ¼ Watt resistor specified in the parts list for general assembly. The HC-05 Bluetooth Module has six pins designated for State, RX, TX, GND, VCC, and EN. For this project, only RX, TX, GND, and VCC will be used. The Bluetooth Module has an operating voltage of 5V, but only the VCC and GND pins feature breakout boards to limit the voltage down to 3.3V. Therefore, the 1K and 2K resistor will be used to create a voltage divider (as illustrated in below), to limit the input voltage down to 3.3V for the RX and TX pins so that the Bluetooth Module is not burnt in the process of connecting it to a power source.

[image2]




Arduino Source Code
------------------------------------------------------------------------
Navigating to the 'src' folder found above, one can find the source code for needed Arduino libraries as well as the Arduino program itself. 

Android APK
-------------------------------------------------------------------------
In addition, the .apk has been provided within the root folder for the purpose of downloading the Android application to a local device of the user's choice.
