[materials]: https://i.imgur.com/d9pONmn.jpg "Materials"
[demo]: https://giphy.com/gifs/3ohjUPLlxs0M3eeMda/html5 "Demo"
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
| Arduino Uno R3 | Microcontroller handles operation of devices |
| LIDAR-Lite v3 | Lidar scanner |
| Stepping Motor | 12V 0.4A 200 steps |
| Digital RC Servo Motor | 5V ~500 mA |
| Adafruit Motor/Stepper/Servo Shield | Driver for stepper and servo motors |
| RGB LCD Shield Kit | Adafruit display shield with buttons |
| SD Card Shield | Saves output to SD card |
| Slip Ring | Prevents wires from twisting up |

## Assembly

## Software Installation

## Collecting Data

## Visualizing Data

## Closing Thoughts
