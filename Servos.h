#include <Servo.h>

Servo myservo1;
Servo myservo2;

int hiServoState = 0;
int twoHandState = 0;
unsigned long hiServoPreviousMillis = 0;
unsigned long twoHandPreviousMillis = 0;

void setupServos() {
    myservo1.attach(4);
    myservo2.attach(2);
}

void hiServo() {
    unsigned long currentMillis = millis();
    switch (hiServoState) {
        case 0:
            myservo1.write(270);
            hiServoState++;
            hiServoPreviousMillis = currentMillis;
            break;
        case 1:
            if (currentMillis - hiServoPreviousMillis >= 1000) {
                myservo1.write(180);
                hiServoState++;
                hiServoPreviousMillis = currentMillis;
            }
            break;
        case 2:
            if (currentMillis - hiServoPreviousMillis >= 1000) {
                myservo1.write(360);
                hiServoState++;
                hiServoPreviousMillis = currentMillis;
            }
            break;
        case 3:
            if (currentMillis - hiServoPreviousMillis >= 1000) {
                myservo1.write(180);
                hiServoState = 0; 
                hiServoPreviousMillis = currentMillis;
            }
            break;
    }
}

void twoHand() {
    unsigned long currentMillis = millis();

    switch (twoHandState) {
        case 0:
            myservo1.write(90);
            myservo2.write(0);
            twoHandState++;
            twoHandPreviousMillis = currentMillis;
            break;
        case 1:
            if (currentMillis - twoHandPreviousMillis >= 1000) {
                myservo1.write(0);
                myservo2.write(90);
                twoHandState++;
                twoHandPreviousMillis = currentMillis;
            }
            break;
        case 2:
            if (currentMillis - twoHandPreviousMillis >= 1000) {
                myservo1.write(90);
                myservo2.write(0);
                twoHandState++;
                twoHandPreviousMillis = currentMillis;
            }
            break;
        case 3:
            if (currentMillis - twoHandPreviousMillis >= 1000) {
                myservo1.write(0);
                myservo2.write(90);
                twoHandState = 0; 
                twoHandPreviousMillis = currentMillis;
            }
            break;
    }
}