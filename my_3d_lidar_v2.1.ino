/******************************************************************************
 * Title          : my_3d_lidar_v2.1.ino
 * Author         : Renat Khalikov
 * Created on     : December 19, 2017
 * Description    : Creates a xyz coordinate file saved to an SD card. File
 *                  contains x coordinate based on the height of the servo
 *                  motor, y coordinate based on the angle made by the stepper
 *                  motor, and z coordinate based on the distance measured by
 *                  the Lidar sensor. Project is based off Youtube video,
 *                  channel TechsOnTube, https://tinyurl.com/ycta3o5k
 * Purpose        : implementation for 3D scanning a small room using Arduino
 *                  Uno based microcontroller and readily available hardware
 *                  devices.
 * Usage          : Arduino IDE
 * Build with     : Arduino IDE
 */

/**
 * Hardware:
 * LiDAR Lite v3: 5 Vdc, 135 mA, I2C default 7-bit address 0x62
 *   Pins used: 5 Vdc (+), I2C SCL, I2C SDA, Ground (-).
 *
 * NEMA 17 Stepper Motor: 12 Vdc, 400 mA, 2 phase motor at 200 steps
 *   Pins used: Connected to Adafruit Motor Shield V2 motor port M3 and M4
 *
 * Continuous Servo Motor: 5 Vdc, 500 mA – 900 mA continuous rotation
 *   Pins used: Connected to Adafruit Motor Shield V2 Servo port, pin D5
 *
 *
 * Arduino and Shields:
 * Elgoo UNO R3 (ATmega328): 5 Vdc
 *
 * Stackable SD Card shield V3: 3.3V/5Vdc, 100 mA.
 * Pins used: SPI bus - MOSI - pin 11,
 *                      MISO - pin 12,
 *                      CLK - pin 13,
 *                      CS - pin 4.
 *
 * Adafruit Motor Shield V2: 5 Vdc (default), I2C default 7-bit address 0x60
 * Pins used: Ground (-), I2C SCL, I2C SDA, Pin D5 for servo.
 *
 * Adaruit RGB LCD 16x2 Shield: 5 Vdc, ~300 mA, I2C default 7-bit address 0x20
 * Pins used: 5 Vdc (+), I2C SCL, I2C SDA, Ground (-).
 */
#include <SoftwareServo.h>
#include <LIDARLite.h>

// stepper motor shield required libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// display libraries
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

// sd card shield libraries
#include <SPI.h>
#include <SD.h>

LIDARLite myLidarLite;
SoftwareServo servo;
File myFile;
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

volatile int stepCount = 0;
volatile int roundCount = 0;

// default position of servo
int height = 18;
// default scan speed
int scan_speed = 20;

void setup() {
  delay(5000);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    lcd.setBacklight(RED);
    lcd.clear();
    lcd.setCursor(0, 0);
    Serial.println("initialization failed!");
    lcd.println("initialization failed!");
    while (1);
  }
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // display user interface
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Mode");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  uint8_t buttons = -1;
  while(1){
    buttons = lcd.readButtons();
    if (buttons) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Selected: ");
      if (buttons & BUTTON_RIGHT) {
        lcd.print("m2");
        lcd.setCursor(0, 1);
        lcd.print("Speed: ");
        lcd.print(scan_speed);
        scan_speed = 1600;
        break;
      }
      if (buttons & BUTTON_LEFT) {
        lcd.print("m3");
        lcd.setCursor(0, 1);
        lcd.print("Speed: ");
        lcd.print(scan_speed);
        scan_speed = 20;
        break;
      }
      if (buttons & BUTTON_DOWN) {
        lcd.print("m1");
        lcd.setCursor(0, 1);
        lcd.print("Speed: ");
        lcd.print(scan_speed);
        scan_speed = 3200;
        break;
      }
    }
  }

  // 0: Default mode, balanced performance.
  // If true, I2C frequency is set to 400kHz.
  myLidarLite.begin(0, true);
  // 0: Default mode, balanced performance.
  myLidarLite.configure(0);

  // attach servo to pin 5
  servo.attach(5);
  servo.write(height);

  // stepper motor shield
  AFMS.begin();  // create with the default frequency 1.6KHz
  myMotor->setSpeed(10);  // 10 rpm
  Serial.println("initialization done.");
}

void loop() {
  // biasCorrection: Default true. Take aquisition with receiver bias
  // correction. If set to false measurements will be faster. Receiver bias
  // correction must be performed periodically. (e.g. 1 out of every 100
  // readings).
  receive(true);
  for(int i = 0; i < 99; i++){
    receive(false);
  }
}

void receive(bool bias)
{
  // move motor one step forward
  MoveOneStep();

  float angle = ((float)stepCount / 3200.0f) * 360.0f;
  if(myFile) {
    myFile.print(108 - height);
    myFile.print(",");
    myFile.print(angle);
    myFile.print(",");
    myFile.println(myLidarLite.distance(bias)); // returns distance
    Serial.print(108 - height);
    Serial.print(",");
    Serial.print(angle);
    Serial.print(",");
    Serial.println(myLidarLite.distance(bias)); // returns distance
  }

  // after 2 rotations of stepper motor,
  // adjust the height of servo to start another scanline
  if(roundCount >= 2){
    height++;
    // done scanning, reset servo positon
    // output to lcd screen
    if(height >= 140){
      height = 18;
      servo.write(height);
      myFile.close();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Done!");
      lcd.setBacklight(GREEN);
      while(1);
    }
    servo.write(height);
    roundCount = 0;
  }
  servo.refresh();
}

void MoveOneStep()
{
  // "Double" means 2 coils are activated at once (for higher torque)
  myMotor->step(1, FORWARD, DOUBLE);

  // keep track of how many steps stepper motor took
  // if stepper made a full rotation, increment the number of times
  // stepper motor made a rotation
  stepCount++;
  if(stepCount >= scan_speed){
    stepCount = 0;
    roundCount++;
  }
}
