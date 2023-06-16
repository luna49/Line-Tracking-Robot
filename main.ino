#include <Adafruit_MotorShield.h>
#include <hp_BH1750.h>

#define MOTOR_A_TERMINAL 1
#define MOTOR_B_TERMINAL 2
#define MOTOR_C_TERMINAL 3
#define MOTOR_D_TERMINAL 4

#define IR_PIN_1 A0
#define IR_PIN_2 A1

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *MOTOR_A = AFMS.getMotor(MOTOR_A_TERMINAL);
Adafruit_DCMotor *MOTOR_B = AFMS.getMotor(MOTOR_B_TERMINAL);
Adafruit_DCMotor *MOTOR_C = AFMS.getMotor(MOTOR_C_TERMINAL);
Adafruit_DCMotor *MOTOR_D = AFMS.getMotor(MOTOR_D_TERMINAL);

hp_BH1750 lightSensor;
int light = 0;

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();

  // Serial.begin(9600);

  lightSensor.begin(BH1750_TO_GROUND);

  pinMode(IR_PIN_1, INPUT);
  pinMode(IR_PIN_2, INPUT);

  MOTOR_A->setSpeed(0);
  MOTOR_A->run(RELEASE);

  MOTOR_B->setSpeed(0);
  MOTOR_B->run(RELEASE);

  MOTOR_C->setSpeed(0);
  MOTOR_C->run(RELEASE);

  MOTOR_D->setSpeed(0);
  MOTOR_D->run(RELEASE);
}

void loop() {
  lightSensor.start();
  
   // Read the value from the IR sensor
  int SEN_1 = digitalRead(IR_PIN_1);
  int SEN_2 = digitalRead(IR_PIN_2);

  // Read the value from the light sensor
  int lux = lightSensor.getLux();
  // Serial.println(lux);

  if (lux > 1500) {
    light = 1;
  }

  if (SEN_1 == 0 && SEN_2 == 0 && light == 1) {
    moveForward();
  }

  else if (SEN_1 == 0 && SEN_2 == 1 && light == 1) {
    //Serial.println("Black detected");
    rotateMotorsClockwise();
  }
  else if (SEN_1 == 1 && SEN_2 == 0 && light == 1) {
    //Serial.println("White detected!");
    rotateMotorsCounterClockwise();
  }
  else if (SEN_1 == 1 && SEN_2 == 1 && light == 1) {
    stop();
  }

}

void moveForward(){
  MOTOR_A->setSpeed(220);
  MOTOR_A->run(BACKWARD);

  MOTOR_B->setSpeed(220);
  MOTOR_B->run(BACKWARD);

  MOTOR_C->setSpeed(220);
  MOTOR_C->run(BACKWARD);

  MOTOR_D->setSpeed(220);
  MOTOR_D->run(BACKWARD);

}

void stop() {
  MOTOR_A->setSpeed(0);
  MOTOR_B->setSpeed(0);
  MOTOR_C->setSpeed(0);
  MOTOR_D->setSpeed(0);
  MOTOR_A->run(FORWARD);
  MOTOR_B->run(FORWARD);
  MOTOR_C->run(FORWARD);
  MOTOR_D->run(FORWARD);
}

void rotateMotorsClockwise() {
  MOTOR_A->setSpeed(10);
  MOTOR_D->setSpeed(130);
  MOTOR_A->run(FORWARD);
  MOTOR_D->run(FORWARD);

  MOTOR_B->setSpeed(100);
  MOTOR_C->setSpeed(180);
  MOTOR_B->run(BACKWARD);
  MOTOR_C->run(BACKWARD);
}

void rotateMotorsCounterClockwise() {
  MOTOR_B->setSpeed(10);
  MOTOR_C->setSpeed(130);
  MOTOR_B->run(FORWARD);
  MOTOR_C->run(FORWARD);

  MOTOR_A->setSpeed(100);
  MOTOR_D->setSpeed(180);
  MOTOR_A->run(BACKWARD);
  MOTOR_D->run(BACKWARD);
}
//   if (light == 1) {
//     if (SEN_1 == 0 && SEN_2 == 0) {
//       moveMotors(-220);
//     } else if (SEN_1 == 0 && SEN_2 == 1) {
//       rotateMotors(10, 130, -100, -180);
//     } else if (SEN_1 == 1 && SEN_2 == 0) {
//       rotateMotors(-10, -130, 100, 180);
//     } else if (SEN_1 == 1 && SEN_2 == 1) {
//       stop();
//     }
//   }
// }

// void moveMotors(int speed) {
//   MOTOR_A->setSpeed(speed);
//   MOTOR_B->setSpeed(speed);
//   MOTOR_C->setSpeed(speed);
//   MOTOR_D->setSpeed(speed);

//   MOTOR_A->run(BACKWARD);
//   MOTOR_B->run(BACKWARD);
//   MOTOR_C->run(BACKWARD);
//   MOTOR_D->run(BACKWARD);
// }

// void stop() {
//   moveMotors(0);
//   MOTOR_A->run(FORWARD);
//   MOTOR_B->run(FORWARD);
//   MOTOR_C->run(FORWARD);
//   MOTOR_D->run(FORWARD);
// }

// void rotateMotors(int speedA, int speedD, int speedB, int speedC) {
//   MOTOR_A->setSpeed(speedA);
//   MOTOR_D->setSpeed(speedD);
//   MOTOR_A->run(FORWARD);
//   MOTOR_D->run(FORWARD);

//   MOTOR_B->setSpeed(speedB);
//   MOTOR_C->setSpeed(speedC);
//   MOTOR_B->run(FORWARD);
//   MOTOR_C->run(FORWARD);
// }
