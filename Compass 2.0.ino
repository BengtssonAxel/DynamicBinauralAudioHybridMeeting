//Code for the compass
//Written By Axel Bengtsson
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Math.h>

Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

float pi = 3.14159;
float oldHeading = 0;
float moveTo;
int maxValue = 2048;

void setup() {
  Serial.begin(115200);
  if(!mag.begin()){
    while(1);
  }
}

void loop() {
  CompassReading();
  delay(200);
}

void CompassReading(){
  sensors_event_t event;                                                        //Get a new sensor event.
  mag.getEvent(&event);
  float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / pi;       //Calculate the angle of the vector x, y.
  if(heading < 0){                                                              //Set the readings to be within 0-360 degrees.
    heading = 360 + heading;
  }
  if( heading != 0){                                                            //Throw away values that equal 0.
    heading = round(heading);
    if(BigChange(heading)){                                                     //If the sensor value have moved more than X amount continue.
      moveTo = map(heading, 0, 360, 0, maxValue);                               //Convert compass value to min 0 max 2048 and set the old heading.
      Serial.println(moveTo);                                                   //Sending the compass readings to the stepper motor
    }
  }
}

//Method that checks if the sensor have moved more that X degrees.
bool BigChange(float heading){
  if(oldHeading == 0){                                                          //If this is the first iteration the skip to run this method once.
    oldHeading = heading;
    return false;
  }
  int change = heading - oldHeading;                                           
  if(change == 0){                                                              //If it is not the first iteration calculate if the change is bigger than X.
    oldHeading = heading;
    return false;
  }else if(change < 5 && change > -5){
    oldHeading = heading;
    return false;
  }else{
    oldHeading = heading;
    return true;
  }
}