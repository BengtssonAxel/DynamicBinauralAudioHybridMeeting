//Code for the stepper
//Written By Axel Bengtsson
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
#define BUTTON_PIN_1 5
#define BUTTON_PIN_2 6
#define LED 13

int stepNumber = 0;
int moveTo = 0;
int stepperPos = 0;
int maxValue = 2048;
int nl = 10;
bool set = false;
bool setStepperPos = false;

const byte numChars = 32;
char receivedChars[numChars];
bool newData = false;
int dataNumber = 0;

void setup() {
  Serial.begin(115200);

  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  while (!set) {
    //Set the code for external buttons.
    if (digitalRead(BUTTON_PIN_1) == HIGH) {
      OneStep(true);
    }
    if (digitalRead(BUTTON_PIN_2) == HIGH) {
      OneStep(false);
    }
    if (digitalRead(BUTTON_PIN_1) == HIGH && digitalRead(BUTTON_PIN_2) == HIGH) {
      set = true;
      digitalWrite(LED, HIGH);
    }
  }

  recvWithEndMarker();
  showNewNumber();
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  if (Serial.available() > 0) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';  // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewNumber() {
  if (newData == true) {
    dataNumber = 0; 
    dataNumber = atoi(receivedChars);        
    newData = false;
    if (dataNumber > 0) {
      moveTo = dataNumber;
      StepperMotion();
    }
  }
}

//Method that calculates the stepper movement.
void StepperMotion() {
  //Set the statring position for the steppermotor equal to the first compass reading.
  if (!setStepperPos) {
    stepperPos = moveTo;
    setStepperPos = true;
  }

  int result = (maxValue - stepperPos + moveTo);

  if (result > maxValue) {
    result = result - maxValue;
  }
  if (result < maxValue / 2) {
    while (result != 0) {
      OneStep(true);
      delay(2);
      result--;
      stepperPos++;
      if (result <= 0) {
        result = 0;
      }
    }
  } else {
    result = maxValue - result;
    while (result != 0) {
      OneStep(false);
      delay(2);
      result--;
      stepperPos--;
      if (result <= 0) {
        result = 0;
      }
    }
  }
}

//Method that controls the stepper motor
void OneStep(bool dir) {
  //Move the stepper clockwise
  if (dir) {
    switch (stepNumber) {
      case 0:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
    }
  }

  //Move the stepper counter clockwise
  else {
    switch (stepNumber) {
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
    }
  }
  delay(2);
  stepNumber++;
  if (stepNumber > 3) {
    stepNumber = 0;
  }
}