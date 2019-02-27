# Raspberry-Server  ---  RFCOMM
basic example of communication between smartphone and raspberry PI - using RFCOMM 

Bluetooth Server example – Comunication using RFCOMM

This program enables communication with the raspberry pi device using the logical layer of RFCOMM software available in the linux environment.

I hope this example helps save fellow developers from the long hours of reading and researching, it took me until I was able to put together a 
reasonably robust solution.

# Overview


To compile the program in raspberry it will be necessary:

sudo apt-get install libbluetooth-dev

# Steps to run:


* make smartphone bluetooth discoverable

* execute following commands in raspberry: 

* sudo bluetoothctl

* [bluetooth]# power on
* [bluetooth]# agent on
* [bluetooth]# discoverable on
* [bluetooth]# pairable on
* [bluetooth]# scan on

* [bluetooth]# pair <smartphone>  ex: pair  94:65:2D:C6:8F:68
* [bluetooth]# trust <smartphone> ex: trust 94:65:2D:C6:8F:68
* [bluetooth]# quit
 
* ./RfcommServer.exe

* goto smartphone and install: 

 ex: Advanced Bluetooth Terminal

 connect with raspberry
 send any content

* in the console of raspberry:
* check if it is receiving
* type any content and enter
* 
* look phone for response

Note: Default BT configuration is permissive. See  https://github.com/mongoose-os-libs/bt-common#security  for a better idea. 

