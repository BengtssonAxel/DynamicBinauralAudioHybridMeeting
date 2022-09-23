import processing.net.*;
import processing.serial.*;

Client c;
Serial arduino;
int nl = 10;
String myString = null;
String myString2 = null;
String arduinoString = null;
float val;
int numbers []; 

void setup() {
  c = new Client(this, "192.168.0.7", 12345); 
  arduino = new Serial(this, "COM9", 115200);
}

void draw() {
  if (c.available()>0) {
    myString = c.readStringUntil(nl);
    
    if(myString != null){
      val = float(myString);
      
      println(myString);
      arduino.write(myString + "\n");
    }
  }
  if(arduino.available() > 0){ 
    myString2 = arduino.readStringUntil(nl);
    if(myString2 != null){
      println(myString2);
    }       
  }
}
