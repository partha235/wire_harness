# Wire Harness
This repo contains code for wire harness system.

## Abstract 

This project presents a smart wire harness diagnostic system using an Arduino Nano for comprehensive cable testing and analysis. The system verifies signal integrity by transmitting a PWM waveform through the harness and measuring pulse width accuracy at the receiving end. It evaluates electrical continuity and calculates wire resistance using precision voltage measurement techniques. Current flow up to 10A is monitored using the ACS712 to assess load behavior and detect abnormal conditions. Temperature rise under load is measured to analyze thermal performance and conductor stability. The integrated approach enables real-time detection of open circuits, short circuits, high resistance faults, and overheating, making it suitable for automotive and industrial harness validation applications.



### Hardware

Arduino Nano
ACS712 (30amp)
N-channel MOSFET 
DS18B20 temperature sensor 
10kΩ resistors
10W resistor
Flyback diode
Automotive fuse (10A–15A)
Oled display
Push buttons
Buzzer
Status LEDs
5V DC power supply
Test connectors
Heat sink for MOSFET