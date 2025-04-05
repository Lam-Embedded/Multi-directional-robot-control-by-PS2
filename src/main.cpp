#include <Arduino.h>
#include "Emakefun_MotorDriver.h"
#include "PS2X_lib.h"

#define PS2_DAT     12
#define PS2_CMD     11
#define PS2_SEL     10
#define PS2_CLK     13

#define speaker A0

#define pressures   false
#define rumble      false

PS2X ps2x;
Emakefun_MotorDriver mMotor = Emakefun_MotorDriver(0x60);
Emakefun_DCMotor *DCMotor_1 = mMotor.getMotor(1);
Emakefun_DCMotor *DCMotor_2 = mMotor.getMotor(2);
Emakefun_DCMotor *DCMotor_3 = mMotor.getMotor(3);
Emakefun_DCMotor *DCMotor_4 = mMotor.getMotor(4);

int speed_val = 100;

void setMotorSpeed(Emakefun_DCMotor* motor, int speed, int direction) {
    motor->setSpeed(speed);
    motor->run(direction);
}

void moveForward() {
    setMotorSpeed(DCMotor_1, speed_val, FORWARD);
    setMotorSpeed(DCMotor_2, speed_val, FORWARD);
    setMotorSpeed(DCMotor_3, speed_val, FORWARD);
    setMotorSpeed(DCMotor_4, speed_val, FORWARD);
}

void moveBackward() {
    setMotorSpeed(DCMotor_1, speed_val, BACKWARD);
    setMotorSpeed(DCMotor_2, speed_val, BACKWARD);
    setMotorSpeed(DCMotor_3, speed_val, BACKWARD);
    setMotorSpeed(DCMotor_4, speed_val, BACKWARD);
}

void strafeLeft() {
    setMotorSpeed(DCMotor_1, speed_val, BACKWARD);
    setMotorSpeed(DCMotor_2, speed_val, FORWARD);
    setMotorSpeed(DCMotor_3, speed_val, FORWARD);
    setMotorSpeed(DCMotor_4, speed_val, BACKWARD);
}

void strafeRight() {
    setMotorSpeed(DCMotor_1, speed_val, FORWARD);
    setMotorSpeed(DCMotor_2, speed_val, BACKWARD);
    setMotorSpeed(DCMotor_3, speed_val, BACKWARD);
    setMotorSpeed(DCMotor_4, speed_val, FORWARD);
}

void rotateLeft() {
    setMotorSpeed(DCMotor_1, speed_val, FORWARD);
    setMotorSpeed(DCMotor_2, speed_val, BACKWARD);
    setMotorSpeed(DCMotor_3, speed_val, FORWARD);
    setMotorSpeed(DCMotor_4, speed_val, BACKWARD);
}

void rotateRight() {
    setMotorSpeed(DCMotor_1, speed_val, BACKWARD);
    setMotorSpeed(DCMotor_2, speed_val, FORWARD);
    setMotorSpeed(DCMotor_3, speed_val, BACKWARD);
    setMotorSpeed(DCMotor_4, speed_val, FORWARD);
}

void stopMotors() {
    DCMotor_1->run(BRAKE);
    DCMotor_2->run(BRAKE);
    DCMotor_3->run(BRAKE);
    DCMotor_4->run(BRAKE);
}

void diagonalFrontRight() {
    setMotorSpeed(DCMotor_1, speed_val, FORWARD);
    DCMotor_2->run(BRAKE);
    DCMotor_3->run(BRAKE);
    setMotorSpeed(DCMotor_4, speed_val, FORWARD);
}

void diagonalBackLeft() {
    setMotorSpeed(DCMotor_1, speed_val, BACKWARD);
    DCMotor_2->run(BRAKE);
    DCMotor_3->run(BRAKE);
    setMotorSpeed(DCMotor_4, speed_val, BACKWARD);
}

void diagonalFrontLeft() {
    setMotorSpeed(DCMotor_2, speed_val, FORWARD);
    DCMotor_1->run(BRAKE);
    DCMotor_4->run(BRAKE);
    setMotorSpeed(DCMotor_3, speed_val, FORWARD);
}

void diagonalBackRight() {
    setMotorSpeed(DCMotor_2, speed_val, BACKWARD);
    DCMotor_1->run(BRAKE);
    DCMotor_4->run(BRAKE);
    setMotorSpeed(DCMotor_3, speed_val, BACKWARD);
}

void setup() {
    Serial.begin(9600);
    mMotor.begin(50);
    ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    pinMode(speaker, OUTPUT);
    tone(speaker,131);
    delay(200);
    noTone(speaker);
}

void loop() {
    ps2x.read_gamepad(false, 0);
    if (ps2x.ButtonDataByte()) {
        if (ps2x.Button(PSB_PAD_UP)) {
            Serial.println("PS2X PSB_PAD_UP:");
            moveForward();
        }
        if (ps2x.Button(PSB_PAD_DOWN)) {
            Serial.println("PS2X PSB_PAD_DOWN:");
            moveBackward();
        }
        if (ps2x.Button(PSB_PAD_LEFT)) {
            Serial.println("PS2X PSB_PAD_LEFT:");
            strafeLeft();
        }
        if (ps2x.Button(PSB_PAD_RIGHT)) {
            Serial.println("PS2X PSB_PAD_RIGHT:");
            strafeRight();
        }
        if (ps2x.ButtonPressed(PSB_CIRCLE)) {
            Serial.println("PS2X PSB_CIRCLE:");
            rotateLeft();
        }
        if (ps2x.ButtonPressed(PSB_CROSS)) {
            Serial.println("PS2X PSB_CROSS:");
            stopMotors();
        }
        if (ps2x.ButtonPressed(PSB_SQUARE)) {
            Serial.println("PS2X PSB_SQUARE:");
            rotateRight();
        }
        if (ps2x.ButtonPressed(PSB_TRIANGLE)) {
            Serial.println("PS2X PSB_TRIANGLE:");
            diagonalFrontRight();
        }
    } else {
        stopMotors();
    }
}

