#define echoPin 5
#define trigPin 12

long duration;
int cm;

void setupDat() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

int getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    cm = duration / 58;
    return cm;
}