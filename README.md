# Autonomous Navigation with RPLidar and GPIO Control

This Arduino script demonstrates autonomous navigation utilizing the RPLidar sensor for obstacle detection and GPIO control to maneuver a robotic system based on the detected obstacles.

## Overview

The script utilizes an RPLidar sensor to detect obstacles in its vicinity and controls GPIO pins based on the detected scenario to enable autonomous navigation.

## Code Description

### Libraries Used
- **RPLidar**: The code employs the `RPLidar.h` library to interact with the RPLidar sensor.

### Pin Definitions
- Defines GPIO pin connections for different scenarios:
  - `no_obj`: GPIO pin number for no obstacles scenario.
  - `obj_c`, `obj_l`, `obj_r`: GPIO pin numbers for specific obstacle detection scenarios (center, left, right).

### Setup and Initialization
- The script initializes the RPLidar sensor, serial communication, and GPIO pins.
- Serial communication is established to facilitate debugging messages (`Serial.begin()`).

### Loop Execution
- The loop continuously runs and processes data from the RPLidar sensor.
- It iterates through the lidar data points to detect obstacles in different angles and distances.
- The script interprets lidar data to determine the presence and location of obstacles.
- Based on the obstacle scenarios detected by lidar and the GPIO input statuses, it controls the GPIO outputs to navigate the robot:
  - Forward movement ('f'), backward movement ('b'), left turn ('l'), and right turn ('r').
- If no obstacles are detected in specific directions, appropriate GPIO pins are set to control the robot's movement accordingly.

### Autonomous Navigation Logic
- The script implements logic to interpret lidar data and GPIO inputs to navigate autonomously.
- Different combinations of lidar readings and GPIO inputs trigger specific movement commands for the robot to avoid obstacles.

### Usage
- The script can be uploaded to an Arduino board equipped with the required hardware components (RPLidar sensor and GPIO connections).
- Ensure proper connections and power supply for the RPLidar sensor and GPIO pins.

### Note
- Ensure the correct GPIO pin connections and their respective functionalities as per your hardware setup.
- Adjustments to distance thresholds and obstacle detection angles may be necessary based on the physical configuration and operational requirements.
