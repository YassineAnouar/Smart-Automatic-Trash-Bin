// Smart Automatic Trash Bin
// Developed by Yassine Anouar


#include <Servo.h>

const int TRIG_PIN  = 9;
const int ECHO_PIN  = 10;
const int SERVO_PIN = 6;

Servo lidServo;

const int OPEN_DISTANCE = 20;   
const int OPEN_ANGLE    = 90;  
const int CLOSED_ANGLE  = 0;    
const int OPEN_DELAY = 3000;   

long duration;
int distance;


void setup()
{
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
 
    lidServo.attach(SERVO_PIN);
    lidServo.write(CLOSED_ANGLE);
    Serial.println("Smart Trash Bin Started...");
}


void loop()
{
    distance = measureDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    if (distance > 0 && distance <= OPEN_DISTANCE)
    {
        openLid();
    }
    else
    {
        closeLid();
    }

    delay(200);
}


int measureDistance()
{
    
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    int calculatedDistance = duration * 0.034 / 2;
    return calculatedDistance;
}


void openLid()
{
    Serial.println("Opening Lid...");
    lidServo.write(OPEN_ANGLE);
    delay(OPEN_DELAY);
}


void closeLid()
{
    lidServo.write(CLOSED_ANGLE);
}
