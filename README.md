# Password-based-Access-Control-System

## Description
This project implements a password-protected motor control system using the PIC18F4580 microcontroller. The system is designed to secure motor activation with a 4-digit password entered via a 4x4 keypad. A 16x2 LCD is used to guide the user through the password entry process, and LED indicators provide visual feedback for successful or failed attempts. If the password is entered incorrectly three times, the system locks out the user and requires them to wait before attempting again.

## Installations
Ensure you have the following tools installed:
- MPLAB X IDE: The integrated development environment used for writing and compiling the code for PIC microcontrollers
- Proteus Design Suite: A simulation software used to model and test the circuit design

## Setup
1. Create a new project in MPLAB and copy the code from main.c into the source file of the project.
2. Build the project to generate a `.hex` file, which is needed for simulation in Proteus.
3. According to the `Proteus Simluation.pdsprj`, create the schematic of the project and ensure the connections are correctly made.
4. Double-click on the PIC18F4580 in the schematic. In the Program File field, browse to the location where the MPLAB project saved the `.hex` file and select it.
5. After setting up all the connections, run the simulation in Proteus.