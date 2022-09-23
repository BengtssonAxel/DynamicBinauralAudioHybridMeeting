import processing.serial.*;
import processing.net.*;

Server s;
Client c;
Serial arduino;
int nl = 10;
String myString = null;


void setup() {
  // Open the port that the board is connected to and use the same speed (9600 bps)
  arduino = new Serial(this, "/dev/cu.usbmodem14101", 115200);
  s = new Server(this, 12345);
}

void draw() {
  if(arduino.available() > 0){ 
    myString = arduino.readStringUntil(nl);
    if(myString != null){
      println(myString);
      s.write(myString); 
    }       
  }
}
