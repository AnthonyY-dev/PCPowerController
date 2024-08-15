# PCController

## Overview

**PCController** is an Arduino-based project designed to control your PC's power state using a keypad, an LCD display, and a relay module. The system allows users to turn their PC on or off by entering a predefined PIN code. The project is straightforward and doesn't require any resistors, making it a simple yet effective solution for PC control.

## Features

- **Keypad Input**: Enter a custom PIN code to control your PC's power state.
- **LCD Display**: Provides visual feedback and guides the user through the process.
- **Relay Control**: Directly connected to the PC's power pins, the relay toggles the power state based on the entered PIN.

## Components

- Arduino board (e.g., Arduino Uno, Arduino Leonardo)
- 4x4 Matrix Keypad
- I2C LCD Display (20x4)
- Relay Module
- Jumper wires
- USB Cable for Arduino

## Circuit Diagram

- **Keypad**: Connected to digital pins 2-9 on the Arduino.
- **LCD Display**: Connected via I2C, using pins A4 (SDA) and A5 (SCL).
- **Relay Module**: Connected to digital pin 10, controlling the power state of the PC.
- **LED Indicators**: Optional RGB LED connected to pins 11, 12, and 13 to indicate system status.

## Installation

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/AnthonyY-dev/PCPowerController.git
    ```

2. **Upload the Code**:
    - Open the `PCController.ino` file in the Arduino IDE.
    - Update the PIN variable, to a pin of your choosing. By default, the pin is **1234**.
    - Connect your Arduino to your PC.
    - Select the correct board and port from the "Tools" menu.
    - Upload the code to your Arduino.

3. **Wiring**:
    - Connect the keypad, LCD, and relay module as described in the circuit diagram section.
    - Ensure that the relay is properly connected to your PC's power pins.

4. **Power On**:
    - After wiring and uploading the code, power on your Arduino.
    - The LCD will prompt you to enter the PIN. The default PIN is `1234`.
    - Enter the PIN using the keypad and press `*` to submit and turn off your PC, or `#` to turn on your PC.
    - If the PIN is correct, the relay will toggle, turning your PC on or off.

## Usage

- **Enter PIN**: Use the keypad to enter the predefined PIN.
- **Control PC Power**: Upon entering the correct PIN, the relay module will either turn the PC on or off.
- **Change PIN**: To modify the default PIN, update the `correctPin` variable in the code and re-upload it to the Arduino.

## Customization

- **Change the PIN**: Modify the `correctPin` variable in the code to set a new PIN.
- **Adjust the LCD Messages**: You can customize the messages displayed on the LCD by editing the `setup()` and `loop()` functions in the code.
- **Add a case**: You can 3D Print a case, using the provided `PC Power Controller.stl` file.

## Youtube

- Here is a youtube video displaying my project: https://youtu.be/HdTAr4uzxLw

## License

This project is open-source and licensed under the MIT License.
