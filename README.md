# Obstacle Avoiding Robot using Ultrasonic Sensors and Arduino

This project implements an **autonomous robot car** that uses **ultrasonic distance sensing (HC-SR04)** and a **servo-mounted front sensor** to detect and avoid obstacles in its path.

Built using **Arduino**, **DC motors**, **ultrasonic sensors**, and a **servo motor**, the robot intelligently maneuvers by analyzing distance and depth data.

## Features

- Automatic forward movement when path is clear
- Stops when an obstacle is detected
- Scans left and right using a servo to find an alternate path
- Backs up and turns if stuck
- Dual ultrasonic sensors — one for front distance, one for depth (optional)

## Hardware Components

| Component            | Quantity |
|---------------------|----------|
| Arduino Uno         | 1        |
| HC-SR04 Ultrasonic Sensors | 2        |
| SG90 Servo Motor     | 1        |
| L298N or motor driver | 1        |
| DC Motors + Wheels  | 2        |
| Chassis             | 1        |
| Power Supply (Battery) | 1        |
| Jumper Wires        | ~10      |


## How It Works

- The **front HC-SR04 sensor** checks for obstacles in the robot's path.
- The **depth sensor** (side or downward-facing) can be used to detect cliffs, drops, or pits.
- A **servo motor** rotates the sensor to scan left/right.
- Based on the readings, the robot either:
  - Moves forward
  - Backs up and turns
  - Scans for alternative paths
