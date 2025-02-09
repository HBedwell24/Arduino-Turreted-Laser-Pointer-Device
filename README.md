# Arduino Turreted Laser Pointer Device
A device forged to supply the niche of keeping household pets occupied in an autonomous nature through the culmination of various hardware components (Adafruit Mini Pan-Tilt Kit, a sensor shield, a 6V/2A power supply, a laser diode, a HC-05 Bluetooth module, and an Arduino UNO Rev 3), as well as an Android application external to the configuration (which performed the role of sending signals to the Arduino through Serial communication, which could then be represented accordingly in the Arduino’s C/C++ codebase). 

## Table of Contents
- [Materials Checklist](#materials-checklist)
- [Device Construction](#device-construction)
- [Configuring the Device](#configuring-the-device)

## Materials Checklist
- [x] Arduino UNO REV3 (x1)
- [x] RobotGeek Sensor Shield V2 (x1)
- [x] Adafruit Mini Pan-Tilt Kit (x1)
- [x] 5mW 650nm Laser Diode (x1)
- [x] HC-05 Bluetooth Transmission Module (x1)
- [x] Full Sized Breadboard (x1)
- [x] 6V Power Supply (x1)
- [x] Red Female/Male Jumper Wires (x2)
- [x] Black Female/Male Jumper Wires (x2)
- [x] Blue Female/Male Jumper Wires (x2)
- [x] Green Female/Male Jumper Wires (x1)
- [x] 1K Ohm ¼ Watt PTH resistor (x1)
- [x] 2.2K Ohm ¼ Watt Carbon Film Resistor (x1)

## Device Construction
The RobotGeek Sensor Shield is compatible with any Arduino board, so the Sensor Shield male header pins should fit perfectly with the female header pins of the Arduino UNO REV3, just make sure that the male header pins aren’t bent when exerting force down on the Sensor Shield to attach it to the Arduino board. Conveniently, the Sensor Shield converts the Arduino’s Digital IO pins into 3-pin adapters, so that it is easier to add servos and other sensors to the project. 

Under the group of pins labeled Voltage In (VIN), attach one servo to DIO-10 and the other to DIO-11. This is so that the servos draw power from the 6V Power Supply, rather than from the Arduino’s built-in 5V regulator which would limit the servo’s range of rotation. It is important to make sure that the orange wire on each servo corresponds to the Signal (S) pin, the red wire to the Voltage (V) pin, and the brown wire to the Ground (G) pin; otherwise, the current will likely burn out the servos. Now, take the female end of the blue jumper wire and attach it to the Signal (S) pin of DIO-12 (this will be your RX pin by which you receive serial data from the HC-05). Repeat the same for the female end of the green jumper wire on the Signal (S) pin of DIO-13 (this will be your TX pin by which you transmit serial data to the HC-05). When attaching the 5mW laser diode to the sensor shield, the diode will feature two wires: a red wire for power and a black wire for ground. Unfortunately, both wires lack header pins to mount directly to the sensor shield, so this is where two of the remaining red and black female/male jumper wires (one of each) will come into play. 

Cut each of the female/male jumper wires in half, making sure to use the halves with the female header pins; the other halves of the wires may be disposed of. Strip the insulation off the end of the wire halves and also off the diode wires. Using a twist-on wire connector, bind the exposed end of the red wire halve to the exposed end of the red diode wire. Repeat this step with another twist-on-wire connector, this time for the set of black wires. Now, simply attach the female end of the red wire to the Signal (S) pin and the female end of the black wire to the Ground (G) pin of DIO-2. Lastly, to finish off with the connections to the Sensor Shield, take the female end of the remaining red jumper wire and attach it to the 5V pin and attach the female end of the remaining black jumper wire to the GND pin. The configuration of the Sensor Shield should look identical to the image provided below.

![Wiring Diagram](images/wiring-schematics.jpg?raw=true "RobotGeek Sensor Shield Wiring Schematics")

The next step is to attach the male ends of the jumper wires to the breadboard. You will need the breadboard, the HC-05 Bluetooth Module, the 1K Ohm ¼ Watt resistor, and the 2.2K Ohm ¼ Watt resistor specified in the parts list for general assembly. The HC-05 Bluetooth Module has six pins designated for State, RX, TX, GND, VCC, and EN. For this project, only RX, TX, GND, and VCC will be used. The Bluetooth Module has an operating voltage of 5V, but only the VCC and GND pins feature breakout boards to limit the voltage down to 3.3V. Therefore, the 1K and 2K resistor will be used to create a voltage divider (as illustrated in below), to limit the input voltage down to 3.3V for the RX and TX pins so that the Bluetooth Module is not burnt in the process of connecting it to a power source.

![Voltage Divider](images/voltage-divider.jpg?raw=true "Voltage Divider for HC-05")

Start by placing the pins of the HC-05 Bluetooth Module into the edge of the breadboard, parallel to the positive and negative power rails. When connecting the male ends of the jumper wires to the breadboard, make sure to connect the green jumper wire (TX) to RX, the blue jumper wire (RX) to TX, the black jumper wire (GND) to GND, and the red jumper wire (5V) to VCC. An illustration of these connections is provided below. If everything is done correctly, a blinking red LED will indicate that the HC-05 Bluetooth Module is powered up and ready to be paired with a client device.

![Breadboard](images/breadboard.jpg?raw=true "Breadboard Resistor, Jumper Wire, and Bluetooth Module Placement")

## Configuring the Device
To see the device in action, simply open up a window in Arduino IDE, and place the Arduino code from the 'src' folder into the project solution. Make sure that the correct microcontroller and port are selected under the tools menu, and then proceed to verify/upload sketch.ino. To properly utilize the full potential of the  HC-05 Bluetooth Module within this project, one should also download the .apk file for the Android application from the root of the repo. 

Once this has been accomplished, step-by-step instructions to move the .apk file from a computer to an Android device of choice can be found here, at AndroidBit: 

https://www.androidpit.com/android-for-beginners-what-is-an-apk-file
