#include "Arduino.h"
#include "BTHC05.h"
#include "VarSpeedServo.h"

// servo objects for pan and tilt servo
VarSpeedServo panServo;
VarSpeedServo tiltServo;
BTHC05 bluetooth(12, 13); // RX, TX

// global variables
bool laserState = 0;
bool modeState = 0;
const int servoSpeed = 10;
const int timeAmount = 50;
const int minManualServoAdjustment = 10;
const int maxManualServoAdjustment = 40;
const int minimalRange = 10;

// minimum & maximum degree of rotation for pan servo 
int panServoMin = 0; 
int panServoMax = 140;

// minimum & maximum degree of rotation for tilt servo
int tiltServoMin = 0;
int tiltServoMax = 70;
int panServoPos = (panServoMin + panServoMax) / 2;
int tiltServoPos = (tiltServoMin + tiltServoMax) / 2;

// delay between each iteration of loop
int delayVal = 300; 

// setup function
void setup() {
  // begin serial communication with baud rate of 9600
  // for printing string input to Serial Monitor
  Serial.begin(9600);
  // while serial communication is active
  while (!Serial); 
  // begin software serial communication with baud rate of 9600
  // for reading string input from HC-05 Bluetooth Module 
  bluetooth.begin(9600); 
  // attach pan and tilt servo objects to pins 10 and 11
  panServo.attach(10);         
  tiltServo.attach(11);

  // write states to each of the pins, and set pin 2 to output
  pinMode(2, OUTPUT);
  digitalWrite(2, laserState);
  tiltServo.write(tiltServoPos, servoSpeed);
  panServo.write(panServoPos, servoSpeed);
}

// loop function
void loop() {
  String string = "";
  if (bluetooth.available()) {
    string = bluetooth.readStringUntil('\n');
    Serial.println(string);  // print input string to serial monitor
  }

  // determine if the Turn On/Turn Off button has been accessed in the Android app
  if (string == "Laser On") {
    laserState = !laserState; // change the laser state and write it to pin 2
    digitalWrite(2, laserState);
    Serial.print("Laser State: ");  // print laser state to serial monitor
    Serial.println(laserState);
  }

  else if (string == "Laser Off") {
    laserState = !laserState; // change the laser state and write it to pin 2
    digitalWrite(2, laserState);
    Serial.print("Laser State: ");  // print laser state to serial monitor
    Serial.println(laserState);
  }

  // determine if the Increase Speed button has been accessed in the Android app
  else if (string == "Increase Speed") {
    if (delayVal >= 50) {
      delayVal -= timeAmount; // decrease the delay amount by 50
      Serial.print("Delay: ");  // print delay value to serial monitor
      Serial.println(delayVal);
    }
  }

  // determine if the Decrease Speed button has been accessed in the Android app
  else if (string == "Decrease Speed") {
      delayVal += timeAmount; // increase the delay amount by 50
      Serial.print("Delay: ");  // print delay value to serial monitor
      Serial.println(delayVal);
  }
  
  // determine if the user has toggled the auto-pilot mode within the Android app
  else if (string == "Autoplay") {
    modeState = !modeState;  // keep the current mode state
    Serial.print("Mode State: "); // print mode state to serial monitor
    Serial.println(modeState);
  }
  
  // determine if the user has toggled the manual override mode within the Android app
  else if (string == "Manual") {
    modeState = !modeState; // change the mode state
    Serial.print("Mode State: "); // print mode state to serial monitor
    Serial.println(modeState);
  }

  // determine if the Increase Area button has been accessed in the Android app
  else if (string == "Increase Area") {
    panServoMin -= 5;
    panServoMax += 5;
    tiltServoMin -= 5;
    tiltServoMax += 5;

    panServoMin = constrain(panServoMin, 0, panServoMax); // adjust the min and max of each servo,
    panServoMax = constrain(panServoMax, panServoMin, 180); // then constrain it
    tiltServoMin = constrain(tiltServoMin, 0, tiltServoMax);
    tiltServoMax = constrain(tiltServoMax, tiltServoMin, 180);
    Serial.print("Area +: ");
    char buf[20];
    sprintf(buf, "%d,%d,%d,%d", panServoMin, panServoMax, tiltServoMin, tiltServoMax);
    Serial.println(buf);  // print buffer to serial monitor
  }

  // determine if the Decrease Area button has been accessed in the Android app
  else if (string == "Decrease Area") {
    if (panServoMax - panServoMin > minimalRange) { // adjust the panServo back down to a previous level
      panServoMin += 5;
      panServoMax -= 5;
    }
    
    if (tiltServoMax - tiltServoMin > minimalRange) { // adjust the tiltServo back down to a previous level
      tiltServoMin += 5;
      tiltServoMax -= 5;
    }
    Serial.print("Area -: ");
    char buf[20];
    sprintf(buf, "%d,%d,%d,%d", panServoMin, panServoMax, tiltServoMin, tiltServoMax);
    Serial.println(buf);  // print buffer to serial monitor
  }

  // the device is in Auto Pilot Mode
  if (modeState) {
    tiltServo.write(random(tiltServoMin, tiltServoMax), servoSpeed);
    panServo.write(random(panServoMin, panServoMax), servoSpeed);
    // waits until servos reaches destination
    tiltServo.wait();
    panServo.wait();
    delay(random(delayVal, delayVal * 5));
  }

  // the device is in Manual Override Mode
  else {
    // move the laser manually in random size steps from 5 - 20 deg upwards
    if (string == "Up") {
      tiltServoPos -= random(minManualServoAdjustment, maxManualServoAdjustment);
      tiltServoPos = constrain(tiltServoPos, tiltServoMin, tiltServoMax);
      tiltServo.write(tiltServoPos, servoSpeed);
      // waits until tilt servo reaches destination
      tiltServo.wait();
      Serial.println(tiltServoPos); // print position of tilt servo to serial monitor
    }

    // move the laser manually in random size steps from 5 - 20 deg downwards
    else if (string == "Down") {
      tiltServoPos += random(minManualServoAdjustment, maxManualServoAdjustment);
      tiltServoPos = constrain(tiltServoPos, tiltServoMin, tiltServoMax);
      tiltServo.write(tiltServoPos, servoSpeed);
      // waits until tilt servo reaches destination
      tiltServo.wait();
      Serial.println(tiltServoPos);  // print position of tilt servo to serial monitor
     
    }

    // move the laser manually in random size steps from 5 - 20 deg to the left
    else if (string == "Left") {
      panServoPos += random(minManualServoAdjustment, maxManualServoAdjustment);
      panServoPos = constrain(panServoPos, panServoMin, panServoMax);
      panServo.write(panServoPos, servoSpeed);
      // waits until pan servo reaches destination
      panServo.wait();  
      Serial.println(panServoPos); // print position of pan servo to serial monitor
    }

    // move the laser manually in random size steps from 5 - 20 deg to the right
    else if (string == "Right") {
      panServoPos -= random(minManualServoAdjustment, maxManualServoAdjustment);
      panServoPos = constrain(panServoPos, panServoMin, panServoMax);
      panServo.write(panServoPos, servoSpeed);
      // waits until pan servo reaches destination
      panServo.wait();
      Serial.println(panServoPos); // print position of pan servo to serial monitor
    }
  }
}
