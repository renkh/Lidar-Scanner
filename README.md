# Lidar Scanner

Lidar scanner is a device capable of scanning small to medium sized rooms and spaces using Lidar. The Lidar sensor illuminates a small target in a scene and measures the distance by calculating the laser return times and wavelengths. The device then calculates the angle of the target in relation to its position and saves an xyz coordinate to an SD card. By knowing the precise xyz coordinates, it is possible to make digital 3D representations of the scenery by using software capable of reading xyz coordinates. Main motivation of this project is to create an affordable 3D scanning Lidar sensor by using readily available parts and microcontrollers at a fraction of the price of comparable commercial 3D scanners.

## Workings

The device is operated by Arduino Uno R3 based microcontroller. When the device starts up, it waits for user input using rudimentary user interface. The menu has 3 options for scanning speed. M1 for regular scanning speed, M2 for a quicker scanning, and M3 for very fast scanning. Once the mode has been selected, the device begins scanning. It rotates the Lidar sensor to the top, spinning it around 360 degrees. Every time the scanner makes a rotation, predefined by the selected mode, lidar sensor moves down a degree. As the scan progresses, the lidar sensor keeps moving down producing azimuthal projection. At the end of the scan, the device stops spinning and produces a success message on the display at which point the user can remove the SD card to gather data, or restart the scan from the beginning. 

## Demo

## Materials

## Assembly
