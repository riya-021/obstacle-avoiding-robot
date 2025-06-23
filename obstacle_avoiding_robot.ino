#include <Servo.h>

Servo Myservo;

// Ultrasonic Sensor (Front) Pins
#define trigPin 9
#define echoPin 8

// Ultrasonic Sensor (Depth/Cliff Detection) Pins
#define depthTrigPin 11
#define depthEchoPin 12

// Motor Driver Pins
#define MLa 4  // Left Motor A
#define MLb 5  // Left Motor B
#define MRa 6  // Right Motor A
#define MRb 7  // Right Motor B

long duration, distance, depth;

void setup() {
  Serial.begin(9600);

  // Motor pins
  pinMode(MLa, OUTPUT);
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);

  // Ultrasonic sensor (front)
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Ultrasonic sensor (depth)
  pinMode(depthTrigPin, OUTPUT);
  pinMode(depthEchoPin, INPUT);

  // Attach servo to pin 10
  Myservo.attach(10);

  Serial.println("Obstacle Avoiding Robot Ready!");
}

void loop() {
  // --- Front Distance Measurement ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  // --- Depth Measurement ---
  digitalWrite(depthTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(depthTrigPin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(depthEchoPin, HIGH);
  depth = duration / 58.2;

  // Print sensor values
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Depth: ");
  Serial.print(depth);
  Serial.println(" cm");

  // --- Obstacle-Free Path ---
  if (distance > 15 && depth < 10) {
    Myservo.write(90);  // Face forward
    moveForward();
  }
  // --- Obstacle Detected ---
  else if (distance < 10 && distance > 0) {
    stopMotors();
    delay(100);

    // Scan with servo
    Myservo.write(0);   // Look left
    delay(500);
    Myservo.write(180); // Look right
    delay(500);
    Myservo.write(90);  // Return to center
    delay(500);

    // Move backward briefly
    moveBackward();
    delay(500);
    stopMotors();
    delay(100);

    // Turn left
    turnLeft();
    delay(500);
    stopMotors();
  }

  delay(100); // Small delay to stabilize loop
}

// --- Movement Functions ---

void moveForward() {
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
  Serial.println("Moving Forward");
}

void moveBackward() {
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);
  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
  Serial.println("Reversing");
}

void turnLeft() {
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
  Serial.println("Turning Left");
}

void stopMotors() {
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
  Serial.println("Stopped");
}
