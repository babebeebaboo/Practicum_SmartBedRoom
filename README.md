# Practicum_Project_SmartRoom

## Developers
  * Supakorn Wongsawang 
  * Rawit Panjaroen 
  
Department of Computer Engineering, Faculty of Engineering, Kasetsart University.

## File Description
  * /Python : all python file to use in this project
  * /Babe_Board/main.ino : MCU's file for Board ID 5910500147
  * /Check_Board : MCU's file for Board ID 591050xxxx
  * /HAP-NodeJS : all Siri Homekit file to use with Apple Devices.
  * index.html : web controlled page
  * schematic.pdf : schematic diagram
  
## Python Section

## Web Section
```sh
python3 web-server.py
chrome index.html
```

## Homekit Section

Make sure you have node and npm install in your computer 
```sh
cd 
sudo npm config set registry http://registry.npmjs.org/
sudo npm install -g node-gyp
npm install request
cd
cd HAP-NodeJS
npm rebuild
npm install 
```

##### Run
```sh
python3 web-server.py
cd HAP-NodeJS
node BridgedCore.js
```
### Home App
```
Go to 'Home' app in your iphone/ipad
add a new accessories
Select 'Node Bridge'
Tap 'Confirm'
And scan this code below
Tap Add all accessories
```
![alt text](https://github.com/babebeebaboo/Practicum_SmartBedRoom/blob/master/Homekit%20CODE.jpg)

## Hardware
 * ATmega168 microcontroller
 * Relay
 * RFID Reader
 * Switch
 * DHT11
 * Servo
