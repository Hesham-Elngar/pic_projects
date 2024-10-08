

https://github.com/user-attachments/assets/5077317e-0911-4b74-be8f-abf971771871

# Controlling_Leds_Via_UART
##Overview
This project demonstrates UART communication between two PIC18F4620 microcontrollers, where one acts as a transmitter and the other as a receiver to control LEDs remotely. The transmitter sends specific characters ('a', 'b', or 'c'), which prompt the receiver to turn on or off LEDs and send a response message back to the transmitter.

## Hardware Requirements
2 x PIC18F4620 Microcontrollers
2 x LEDs (Green and Red)
UART communication setup between the microcontrollers (TX/RX connections)
Power Supply
Resistors as required

## Project Structure
The project consists of two primary components:

Transmitter MCU: This microcontroller sends character commands ('a', 'b', or 'c') to control the LEDs on the receiver MCU.
Receiver MCU: This microcontroller receives commands from the transmitter MCU, controls the LEDs accordingly, and sends a response back to the transmitter.
## Functionality
Transmitter MCU
Sends one of the following characters via UART:
'a': Command to turn on the green LED on the receiver MCU.
'b': Command to turn on the red LED on the receiver MCU.
'c': Command to turn off all LEDs on the receiver MCU.
Waits for a response from the receiver MCU, confirming the action taken.

## Receiver MCU
Listens for incoming characters via UART and performs actions based on the command received:
If 'a' is received:
Turns on the green LED.
Sends "Green LED ON" back to the transmitter.
If 'b' is received:
Turns on the red LED.
Sends "Red LED ON" back to the transmitter.
If 'c' is received:
Turns off both LEDs.
Sends "ALL LEDs OFF" back to the transmitter.

## Circuit Diagram
Connect the TX pin of the transmitter MCU to the RX pin of the receiver MCU.
Connect the RX pin of the transmitter MCU to the TX pin of the receiver MCU.
Connect each LED to an output pin on the receiver MCU with appropriate resistors.


