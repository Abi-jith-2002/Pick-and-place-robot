#include <Servo.h>

#define SERVO1_PIN 9
#define SERVO2_PIN 11
#define SERVO3_PIN 5
#define SERVO4_PIN 3
#define SERVO5_PIN 10

Servo servos[5];
int angles[5] = {90, 90, 90, 90, 90};
int currentServo = 0;

bool waitingForConfirmation = false;

void setup() {
  Serial.begin(9600);

  servos[0].attach(SERVO1_PIN);
  servos[1].attach(SERVO2_PIN);
  servos[2].attach(SERVO3_PIN);
  servos[3].attach(SERVO4_PIN);
  servos[4].attach(SERVO5_PIN);

  for (int i = 0; i < 5; i++) {
    servos[i].write(angles[i]);
  }

  Serial.println("Enter angle for Servo 1 (0-180):");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (waitingForConfirmation) {
      // User is confirming if the angle was okay
      if (input.equalsIgnoreCase("y")) {
        currentServo++;
        if (currentServo >= 5) currentServo = 0;
        waitingForConfirmation = false;
        Serial.print("Enter angle for Servo ");
        Serial.print(currentServo + 1);
        Serial.println(" (0-180):");
      } else if (input.equalsIgnoreCase("n")) {
        Serial.print("Re-enter angle for Servo ");
        Serial.print(currentServo + 1);
        Serial.println(" (0-180):");
        waitingForConfirmation = false;
      } else {
        Serial.println("Please enter 'y' or 'n'. Is the angle okay? (y/n)");
      }
    } else {
      int angle = input.toInt();
      if (angle >= 0 && angle <= 180) {
        angles[currentServo] = angle;
        servos[currentServo].write(angle);
        Serial.print("Servo ");
        Serial.print(currentServo + 1);
        Serial.print(" moved to ");
        Serial.println(angle);
        Serial.println("Is this okay? (y/n)");
        waitingForConfirmation = true;
      } else {
        Serial.println("Invalid angle! Enter a value between 0 and 180.");
        Serial.print("Re-enter angle for Servo ");
        Serial.print(currentServo + 1);
        Serial.println(":");
      }
    }
  }
}
