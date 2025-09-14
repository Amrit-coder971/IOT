#include <Servo.h>
// Define pins for the ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Define servo motor pin
const int servoPin = 6;

// Create a Servo object
Servo myServo;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    myServo.attach(servoPin);
    myServo.write(0); // Ensure the lid is closed initially
    Serial.begin(9600);
}

void loop() {
    long duration;
    long distance;
    
    // Send ultrasonic pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Measure the echo pulse duration
    duration = pulseIn(echoPin, HIGH);
    
    // Convert to distance in cm
    distance = duration * 0.034 / 2;
    
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // Check if the object is within the trigger range (e.g., 20 cm)
    if (distance > 0 && distance <= 10) {
        myServo.write(90); // Open the lida
        delay(3000);       // Keep it open for 3 seconds
        myServo.write(0);  // Close the lid
    }
    
    delay(3000); // Small delay before the next measurement
}