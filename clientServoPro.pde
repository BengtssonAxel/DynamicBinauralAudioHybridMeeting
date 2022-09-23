import processing.net.*;
import processing.serial.*;

Client c;
int val;
Serial arduino;

void setup() {
  // Connect to the server’s IP address and port­
  c = new Client(this, "192.168.0.7", 12345); // Replace with your server’s IP and port
  arduino = new Serial(this, "COM9", 115200);
}

void draw() {
  if (c.available()>0) {
    val = c.read();
    val = int(map(val, 0, 360, 180, 0));
    arduino.write(val);
    print(val);
    println("");
  }
}
