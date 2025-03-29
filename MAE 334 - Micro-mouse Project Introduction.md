---
id: MAE334_MMPI
created_date: 2025-03-25
updated_date: 2025-03-25
type: note
---

#  Project Introduction
- **🏷️Tags** :  #03-2025 #MAE334
## Project Goals:
- Create a micro-mouse style robot with a onboard neural network for determining position and mapping the maze environment.

## Project Overview
- Create a Micro-mouse robot.
- Develop a Neural Network that operates within the Clock and Memory constraints of the ESP-S3 Chip.
- Develop a training environment for the neural network with a random maze generator.

## Project  Path:
1. Design a chassis for supporting the ESP-S3 breakout board.
	1. Requirements
	   - Sensor mounts.
	   - Motor control circuity and mounts.
2. Develop a framework for Neural Network deployment on ESP-S3 hardware.
	1. Requirements:
	   - Operate in real time. (Clock limitation: 240 MHz)
	   - Work within 240 kB of RAM.
3. Train the Neural Network with generated maze designs and deploy on ESP-S3 hardware.
	1. Requirements:
	   - Develop a map generation algorithm.
	   - Develop a training environment simulating the micro-mouse sensors and motor control system.
	   - Deploy the trained parameters to the control system of the robot.

