/*
====================================================
 Smart Automatic Trash Bin using Arduino
// Developed by Yassine Anouar
====================================================
*/

#include <Servo.h>

/* =======================
   Pin Configuration
======================= */
const int TRIG_PIN  = 9;
const int ECHO_PIN  = 10;
const int SERVO_PIN = 6;

/* =======================
   Object Creation
======================= */
Servo lidServo;

/* =======================
   System Settings
======================= */
const int OPEN_DISTANCE = 20;   // Distance in cm
const int OPEN_ANGLE    = 90;   // Servo open angle
const int CLOSED_ANGLE  = 0;    // Servo closed angle

const int OPEN_DELAY = 3000;    // Lid stays open لمدة 3 ثواني

/* =======================
   Variables
======================= */
long duration;
int distance;

/* ====================================================
   Function: setup()
==================================================== */
void setup()
{
    // Serial Monitor
    Serial.begin(9600);

    // Sensor Pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Servo Setup
    lidServo.attach(SERVO_PIN);

    // Start with closed lid
    lidServo.write(CLOSED_ANGLE);

    Serial.println("Smart Trash Bin Started...");
}

/* ====================================================
   Function: loop()
==================================================== */
void loop()
{
    distance = measureDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Check if object is near
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

/* ====================================================
   Function: measureDistance()
   Description:
   Measures distance using HC-SR04 sensor
==================================================== */
int measureDistance()
{
    // Clear trigger pin
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    // Send ultrasonic pulse
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read echo time
    duration = pulseIn(ECHO_PIN, HIGH);

    // Convert to distance (cm)
    int calculatedDistance = duration * 0.034 / 2;

    return calculatedDistance;
}

/* ====================================================
   Function: openLid()
==================================================== */
void openLid()
{
    Serial.println("Opening Lid...");

    lidServo.write(OPEN_ANGLE);

    delay(OPEN_DELAY);
}

/* ====================================================
   Function: closeLid()
==================================================== */
void closeLid()
{
    lidServo.write(CLOSED_ANGLE);
}
