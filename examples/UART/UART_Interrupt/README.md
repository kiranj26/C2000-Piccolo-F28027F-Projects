# UART Interrupt Example

This example demonstrates how to use the UART (Universal Asynchronous Receiver/Transmitter) module with interrupts on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).

## Hardware Details

### Microcontroller: TMS320F28027F

The TMS320F28027F is a high-performance microcontroller designed for real-time control applications. It features:
- **CPU**: 32-bit CPU with a clock speed of up to 60 MHz.
- **Memory**: 64 KB of Flash memory, 8 KB of RAM.
- **Peripherals**: Includes PWM modules, ADCs, enhanced capture modules, and more.
- **Package**: Available in a 38-pin TSSOP package.

### LaunchPad Features
- **Onboard LEDs**: The kit includes onboard LEDs connected to GPIO pins for easy debugging and status indication.
- **Push Buttons**: Two push buttons connected to GPIO pins for user input.
- **Debugger**: Integrated XDS100v2 JTAG debug probe.
- **Connectors**: Multiple headers for easy access to GPIO and peripheral signals.

### UART Connections
- **SCIRXDA**: GPIO28
- **SCITXDA**: GPIO29

## Software Details

### Prerequisites
- **Code Composer Studio (CCS)**: Download and install from [here](https://www.ti.com/tool/CCSTUDIO).
- **C2000Ware**: Download and install from [here](https://www.ti.com/tool/C2000WARE).

### Instructions

1. **Open Code Composer Studio (CCS)**.
2. **Create a New Project**:
    - Select `File -> New -> CCS Project`.
    - Enter a project name, e.g., `UART_Interrupt`.
    - Select `TMS320F28027F` as the target device.
    - Select `Empty Project` and click `Finish`.
3. **Add Source File**:
    - Right-click on the project and select `New -> Source File`.
    - Name the file `main.c` and copy the content from the `main.c` provided in this folder.
4. **Build and Load the Project**:
    - Click the `Build` button to compile the project.
    - Connect your C2000 Piccolo LaunchPad to your computer.
    - Click the `Debug` button to load the program onto the microcontroller.
5. **Run the Program**:
    - Click the `Run` button to start the program. The UART will handle communication using interrupts.

### Code Explanation

#### InitGpio
This function initializes the GPIO settings. GPIO28 is configured as SCIRXDA and GPIO29 as SCITXDA.

#### InitScia
This function configures the UART module to communicate at a baud rate of 9600 and sets up the interrupt handling for both transmission and reception.

#### main
The main function initializes the system control, GPIO, and UART, initializes the PIE control registers and vector table, maps the UART RX and TX ISRs, and enables the necessary interrupts. It then enters an infinite loop waiting for interrupt-driven communication.

