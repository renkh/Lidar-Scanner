[materials]: https://i.imgur.com/d9pONmn.jpg "Materials"
[demo]: https://imgur.com/pdBPAoY.png "Demo"
[assembly]: https://imgur.com/Wku4ZV2.jpg "Assembly"
# Lidar Scanner

Lidar scanner is a device capable of scanning small to medium sized rooms and spaces using Lidar. The Lidar sensor illuminates a small target in a scene and measures the distance by calculating the laser return times and wavelengths. The device then calculates the angle of the target in relation to its position and saves an xyz coordinate to an SD card. By knowing the precise xyz coordinates, it is possible to make digital 3D representations of the scenery by using software capable of reading xyz coordinates. Main motivation of this project is to create an affordable 3D scanning Lidar sensor by using readily available parts and microcontrollers at a fraction of the price of comparable commercial 3D scanners.

## Scanning Instructions

  The device is operated by Arduino Uno R3 based microcontroller. When the device starts up, it waits for user input using rudimentary user interface. The menu has 3 options for scanning speed. M1 for regular scanning speed, M2 for a quicker scanning, and M3 for very fast scanning. Once the mode has been selected, the device begins scanning. It rotates the Lidar sensor to the top, spinning it around 360 degrees. Every time the scanner makes a rotation, predefined by the selected mode, lidar sensor moves down a degree. As the scan progresses, the lidar sensor keeps moving down producing azimuthal projection. At the end of the scan, the device stops spinning and produces a success message on the display at which point the user can remove the SD card to gather data, or restart the scan from the beginning.

## Demo

![demo]

## How it works

  The device consists of a Lidar sensor, a stepper motor, servo motor, Arduino Uno R3 based microcontroller, Adafruit motor shield V2, SD card shield, Adafruit RBG 16x2 LCD display shield, slip ring, and electrolytic diode. Servo motor is connected to the Lidar sensor and rotates the sensor down on the x axis. The position of the servo motor is kept track by the Arduino and corresponds to the x coordinate in the scan file. The servo and Lidar unit is rotated by the stepper motor along the y axis. Slip ring helps keep the wires from tangling up on each other. The position of the stepper motor is kept track by Arduino and corresponds to the y coordinate in the scan file. At each step of the stepper motor, Lidar sensor measures the distance of a point in the scene. The distance measurement corresponds to the z coordinate in the scan file. The device continuously spins, collecting xyz coordinates that are saved to an SD card for later viewing.


## Materials

![materials]

| Device | Description |
| --- | --- |
| [Arduino Uno R3 based microprocessor](https://www.amazon.com/Elegoo-Board-ATmega328P-ATMEGA16U2-Arduino/dp/B01EWOE0UU/ref=sr_1_3?ie=UTF8&qid=1514046216&sr=8-3&keywords=elegoo+uno+r3) | Microcontroller handles operation of devices |
| [LIDAR-Lite v3](https://www.amazon.com/Garmin-LYSB01MG3Z3PE-CMPTRACCS-LIDAR-Lite-v3/dp/B01MG3Z3PE/ref=sr_1_cc_1?s=aps&ie=UTF8&qid=1514046260&sr=1-1-catcorr&keywords=LIDAR-Lite+v3) | Lidar scanner |
| [Stepping Motor](https://www.amazon.com/Stepping-Motor-26Ncm-36-8oz-Printer/dp/B00PNEQ9T4/ref=sr_1_1?s=industrial&ie=UTF8&qid=1514046348&sr=1-1&keywords=Stepping+Motor+Nema+17+Stepping+Motor+26Ncm%2836.8oz.in%29+12V+0.4A+3D+Printer+CNC) | 12V 0.4A 200 steps |
| [Digital RC Servo Motor](https://www.amazon.com/gp/product/B014KONJZY/ref=oh_aui_detailpage_o05_s01?ie=UTF8&psc=1) | 5V ~500 mA |
| [Adafruit Motor/Stepper/Servo Shield](https://www.amazon.com/Adafruit-Motor-Stepper-Shield-Arduino/dp/B00PUTH3B0/ref=sr_1_2?s=electronics&ie=UTF8&qid=1514046456&sr=1-2&keywords=Adafruit+Motor%2FStepper%2FServo+Shield) | Driver for stepper and servo motors |
| [Adafruit RGB LCD Shield Kit](https://www.amazon.com/Shield-16x2-Character-Negative-Display-Uses/dp/B00JFJJDGY/ref=sr_1_1?s=electronics&ie=UTF8&qid=1514046515&sr=1-1&keywords=Adafruit+RGB+LCD+Shield+Kit) | Adafruit display shield with buttons |
| [SD Card Shield](https://www.amazon.com/HiLetgo-Stackable-Card-Arduino-Shield/dp/B006LRR0IQ/ref=sr_1_1?s=electronics&ie=UTF8&qid=1514046538&sr=1-1&keywords=SD+Card+Shield) | Saves output to SD card |
| [Slip Ring](https://www.amazon.com/gp/product/B01L8U2VOI/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1) | Prevents wires from twisting up |

## Assembly

![assembly]

Soldering is required for some parts. Assembly is straight forward. First assemble the shields if they came in kits.

### Adafruit Motor Shield Assembly
The Adafruit motor shield came partially assembled, I switched out the standard header pins for [stackable headers](https://www.amazon.com/Arduino-Stackable-Header-Kit-R3/dp/B00PCCWEJG/ref=sr_1_4?ie=UTF8&qid=1514046868&sr=8-4&keywords=arduino+stackable+header+kit), stackable headers allow you to stack shields. For soldering instructions, visit [Adafruit Motor Shield V2](https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/install-headers#installing-with-stacking-headers) **Install Headers & Terminals** page **Installing with Stacking Headers** subsection.

External power is needed to drive the servo motor. Cut trace along the bottom of the shield where it says **For opt. servo pwr supply cut trace**. You can do it with a knife, make sure the gold contact line is completely severed.
![cut trace](https://cdn-learn.adafruit.com/assets/assets/000/039/115/medium800/learn_arduino_P2080096_2kb.jpg)

Then solder wires to the **opt servo** holes located at the top of the shield. The red wire goes to the hole closest to **Reset** button. Be sure to get this step right, you can risk damage to the servo motor. Connect the wires to a DC power jack, this power jack will be connected to a **5 Vdc** power supply, which will provide enough power to drive the servo. Do not use anything higher than 5 Vdc.

## Software Installation

Code to run this device is provided in the repository. Download and install [Arduino IDE](https://www.arduino.cc/en/Main/Software). IDE is needed to compile and upload the code to Arduino Uno. The code requires some libraries to run. Libraries that are not included with Arduino IDE need to be download and put into the library folder of arduino. The location of arduino library is in `/Documents/Arduino/libraries`

Libraries needed:

[Adafruit Motor Shield Library](https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/install-software)

[Adafruit RGB LCD Shield Library](https://learn.adafruit.com/rgb-lcd-shield/using-the-rgb-lcd-shield)

[Lidar Lite Library](https://github.com/garmin/LIDARLite_v3_Arduino_Library)


## Collecting Data

You can collect data in 2 ways, either with an SD card or through Arduino IDE serial output monitor. SD card saves the output to TEXT.txt file in the following format:
`x_coord,y_coord,z_coord`
where the xyz coordinates are the coordinates of a point in a scene. Alternatively you can output the data directly to a computer through USB connection using Arduino IDE. On startup, click on the right-most button on the toolbar in the Arduino IDE. This will open serial monitor window where the output will appear. Be sure to set the baud rate to 9600 if its not set already. At the end of the run you can save the output to a text file for further viewing.

## Visualizing Data

Visualizing data can be done with many point cloud software programs.

## Closing Thoughts
