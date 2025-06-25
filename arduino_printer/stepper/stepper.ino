#include <AccelStepper.h>

// change to your pins & driver type
#define STEP_PIN 2
#define DIR_PIN 3
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// we'll accumulate serial chars here
String inputString = "";
bool newCommand = false;

void setup() {
  Serial.begin(115200);
  // give us a little extra headroom
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);
  inputString.reserve(16);

  Serial.println("Ready. Enter speed (–1000…1000) and newline:");
}

void loop() {
  // if we've received a full line, parse it
  if (newCommand) {
    int speed = inputString.toInt(); 
    Serial.print("Setting speed = ");
    Serial.println(speed);
    stepper.setSpeed(speed);
    // clear for the next command
    inputString = "";
    newCommand = false;
  }

  // this must run every loop to keep the motor moving
  stepper.runSpeed();
}

// This handler is called by the core whenever serial data arrives
// (with recent Arduino IDEs - older use serialEvent() differently)
void serialEvent() {
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n') {
      newCommand = true;
    } else if (isDigit(c) || c=='-' ) {
      inputString += c;
    }
    // ignore other chars
  }
}
