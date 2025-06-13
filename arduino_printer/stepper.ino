#include <AccelStepper.h>

#define STEP_PIN 2
#define DIR_PIN 3

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
    Serial.begin(115200);
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
}

void loop() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        int speed = command.toInt();
        stepper.setSpeed(speed);
        stepper.runSpeed();
    }
}
