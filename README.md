# DynamicBinauralAudioHybridMeeting
A head tracking contraption for controlling a set of binaural microphones in a hybrid meeting and enabling dynamic binaural audio.

This project was part of my thesis done for my bachelor’s degree in Interaction Design at Malmö University spring of 2022.
My goal with this project was to take a step toward minimizing the difference in the unfair attendance between the physically present attendees and the remote attendees. One of many solutions for doing this was to allow the remote participants to receive a higher perceived sense of presence in the physical meeting room by allowing them to be present in the auditory space. To do this I used binaural microphones paired with head tracking and a motorized platform for the microphones to sit on. The remote attendees' head movement would therefore allow them to navigate in the auditory space of the physical meeting room. 


![ArduinoCompass](https://user-images.githubusercontent.com/25184812/191968344-25fae194-e9a2-474b-819e-a7579936118e.png)
The image seen above is the wiring schematic of the head tracking assembly placed on the head of the remote participant. It consists of an Arduino micro to which the compass sensor is connected.


![ArduinoStepper](https://user-images.githubusercontent.com/25184812/191968414-d84003e6-ef73-4a16-930b-2656ded58c95.png)
The image seen above is the wiring schematic of the platform for the microphones. It consists of an Arduino Uno on which a stepper motor is connected. 

The two Arduinos are each connected to two separate computers running a server and a client. It is via the server the two Arduino boards can communicate.
