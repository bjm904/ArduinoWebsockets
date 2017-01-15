# ArduinoWebsockets
*This is a personalized project and you probably wont be able to get it to work. Contact me if you are interested*

Arduino code for connecting to Socket.io server and changing pins over the internet. Currently it is set up to change 11 digital pins plus the debug pin. If you want to add more, keep in mind the line that parses the socket message because it deletes a defined number of characters in order to parse.

**Use the Socket.io server from my other project https://github.com/bjm904/Arduino-Online with this!**
##Requires:
- The exact versions of the included libraries, don't try to update
- Socket.io server using Socket.io version 0.9
- A wifi shield that uses the CC3000 chipset


*This was used to control christmas lights on a tree with various animations*
