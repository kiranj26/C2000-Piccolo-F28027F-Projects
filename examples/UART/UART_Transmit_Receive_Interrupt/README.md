# UART Transmit and Receive Using Interrupts Example

This example demonstrates how to use the UART (Universal Asynchronous Receiver/Transmitter) module to send and receive data using interrupts on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).

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
    - Enter a project name, e.g., `UART_Transmit_Receive_Interrupt`.
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
    - Click the `Run` button to start the program. The UART will send and receive data using interrupts.

### Code Explanation

#### InitGpio
This function initializes the GPIO settings. GPIO28 is configured as SCIRXDA and GPIO29 as SCITXDA.

#### InitScia
This function configures the UART module to communicate at a baud rate of 9600.

#### main
The main function initializes the system control, GPIO, and UART, initializes the PIE control registers and vector table, maps the UART RX and TX ISRs, and enables the necessary interrupts. It then enters an infinite loop.

#### scia_rx_isr
The interrupt service routine reads the received character from the UART, echoes it back, and acknowledges the interrupt.

#### scia_tx_isr
The interrupt service routine sends the next character from the transmit buffer and acknowledges the interrupt.

### Additional Resources
- [C2000 Piccolo F28027F Datasheet](https://www.ti.com/lit/ds/symlink/tms320f28027.pdf)
- [C2000 Piccolo Technical Reference Manual](https://www.ti.com/lit/ug/spruh18g/spruh18g.pdf)
- [Code Composer Studio](https://www.ti.com/tool/CCSTUDIO)
- [C2000Ware](https://www.ti.com/tool/C2000WARE)
- [TI E2E Community](https://e2e.ti.com/)
- [C2000 Academy](https://dev.ti.com/tirex/explore/node?node=ACVoMPn4X0iwIj0-VfT0HQ__FUz-xrs__LATEST)
- [C2000 Getting Started Guide](https://www.ti.com/lit/an/spracg5/spracg5.pdf)
- [C2000 Real-Time Control MCUs Forum](https://e2e.ti.com/support/microcontrollers/c2000/f/171)
- [TI Training on C2000](https://training.ti.com/c2000-real-time-mcus)
- [C2000 Workshop](https://software-dl.ti.com/trainingTTO/trainingTTO_public_sw/C2000%20Piccolo%20One-Day%20Workshop.pdf)
- [Embedded Advantage - C2000 Resources](https://www.embeddedadvantage.com/c2000)
- [C2000 Piccolo One-Day Workshop Material](https://software-dl.ti.com/trainingTTO/trainingTTO_public_sw/C2000%20Piccolo%20One-Day%20Workshop.zip)
- [Application Notes for C2000](https://www.ti.com/microcontrollers-mcus-processors/microcontrollers/c2000-real-time-control-mcus/products.html#p2794=F28027&view=appnotes)
- [F2802x Microcontroller Workshop](http://processors.wiki.ti.com/images/c/c7/F2802x_Microcontroller_Workshop.pdf)
- [C2000 Real-Time Control MCU Online Training](https://training.ti.com/c2000-real-time-mcus?context=1137707-1137705)
- [C2000 GitHub Repository](https://github.com/TexasInstruments/c2000ware)
- [C2000 Microcontroller Application Videos](https://www.youtube.com/playlist?list=PLISmVLHAZbTOgUeZb-0dd1ecM4p0T5r-b)
- [C2000 System Framework](https://www.ti.com/tool/C2000-SYSFW)

## Contributing
Contributions are welcome! If you have a project or example you'd like to share, please fork the repository, create a new branch, and submit a pull request. Make sure to follow the coding standards and include a detailed description of your project.

## License
This repository is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

---

Happy coding!

**Kiran Jojare**  
*Embedded Software / Firmware Engineer*  
kijo7257@colorado.edu
