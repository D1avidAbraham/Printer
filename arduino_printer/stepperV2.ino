// File: StepperBridge.ino

#include <AccelStepper.h>

// change these to your pins
constexpr uint8_t STEP_PIN_1 = 2, DIR_PIN_1 = 3;
constexpr uint8_t STEP_PIN_2 = 4, DIR_PIN_2 = 5;

// driver interface: step, dir
AccelStepper stepper1(AccelStepper::DRIVER, STEP_PIN_1, DIR_PIN_1);
AccelStepper stepper2(AccelStepper::DRIVER, STEP_PIN_2, DIR_PIN_2);

void setup() {
  Serial.begin(115200);
  // tune these to your motors/driver
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(500);
  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(500);
}

void loop() {
  // expect lines like "1:200\n" or "2:-100\n"
  stepper1.run();
  stepper2.run();
  if (Serial.available()) {
    
    String line = Serial.readStringUntil('\n');
    if (line.length() < 3 || line.indexOf(':') == -1) return;

    uint8_t id = line.substring(0,1).toInt();
    long steps = line.substring(line.indexOf(':')+1).toInt();

    AccelStepper &M = (id==1) ? stepper1 : stepper2;
    M.move(steps);
    // blocking run until move completes
    
  }
}