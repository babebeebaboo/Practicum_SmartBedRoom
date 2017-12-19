# Practicum_Project_SmartRoom
##### By Supakorn Wongsawang, Rawit Panjaroen<br /><br />
Python folder is store all python file to use in this project.<br />
Babe_Board folder is store MCU's file for Board ID 5910500147.<br />
Check_Board folder is store MCU's file for Board ID 591050xxxx.<br />
HAP-NodeJS folder is store all the file to use Siri Homekit with Apple Devices.<br />
index.html is file to open a web controlled page.<br />
# Python Section

# Web Section
```sh
python3 web-server.py
chrome index.html
```

# Homekit Section

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
## Home App
```
Go to 'Home' app in your iphone/ipad
add a new accessories
Select 'Node Bridge'
Tap 'Confirm'
And scan this code below
Tap Add all accessories
```
![alt text](https://github.com/babebeebaboo/Practicum_SmartBedRoom/blob/master/Homekit%20CODE.jpg)
