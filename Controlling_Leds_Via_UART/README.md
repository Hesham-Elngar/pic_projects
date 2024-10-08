

https://github.com/user-attachments/assets/5077317e-0911-4b74-be8f-abf971771871

# Controlling_Leds_Via_UART
##Overview
This project demonstrates UART communication between two PIC18F4620 microcontrollers, where one acts as a transmitter and the other as a receiver to control LEDs remotely. The transmitter sends specific characters ('a', 'b', or 'c'), which prompt the receiver to turn on or off LEDs and send a response message back to the transmitter.

##Hardware Requirements
2 x PIC18F4620 Microcontrollers
2 x LEDs (Green and Red)
UART communication setup between the microcontrollers (TX/RX connections)
Power Supply
Resistors as required

##Project Structure
The project consists of two primary components:

Transmitter MCU: This microcontroller sends character commands ('a', 'b', or 'c') to control the LEDs on the receiver MCU.
Receiver MCU: This microcontroller receives commands from the transmitter MCU, controls the LEDs accordingly, and sends a response back to the transmitter.
##Functionality
Transmitter MCU
Sends one of the following characters via UART:
'a': Command to turn on the green LED on the receiver MCU.
'b': Command to turn on the red LED on the receiver MCU.
'c': Command to turn off all LEDs on the receiver MCU.
Waits for a response from the receiver MCU, confirming the action taken.
##Receiver MCU
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
##Communication Flow
The transmitter sends one of the characters ('a', 'b', or 'c') to the receiver.
The receiver MCU executes the command and responds with a message to confirm the action.
The transmitter receives and displays (or logs) the response.
##Circuit Diagram
The following wiring is required:

Connect the TX pin of the transmitter MCU to the RX pin of the receiver MCU.
Connect the RX pin of the transmitter MCU to the TX pin of the receiver MCU.
Connect each LED to an output pin on the receiver MCU with appropriate resistors.
##Code Explanation
Transmitter Code: Handles UART initialization and sends characters based on user input or program logic. It then waits and receives responses from the receiver.
Receiver Code: Handles UART initialization, listens for incoming characters, controls the LEDs, and sends back response messages.
##Dependencies
MPLAB IDE with XC8 Compiler for PIC microcontroller development
UART library or custom UART routines for PIC18F4620
##How to Use
Upload the transmitter code to the first PIC18F4620 and the receiver code to the second PIC18F4620.
Power on both microcontrollers and establish UART communication between them.
The transmitter will send commands, and the receiver will control the LEDs and send back responses.
Monitor the output on both microcontrollers to verify successful communication and LED control.

