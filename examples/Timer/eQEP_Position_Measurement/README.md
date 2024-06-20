# eQEP Position Measurement Example

This example demonstrates how to use the eQEP (Enhanced Quadrature Encoder Pulse) module to measure the position of a quadrature encoder on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).

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

### Quadrature Encoder Connections
- **eQEP1A**: Connect the A signal of the quadrature encoder to GPIO20.
- **eQEP1B**: Connect the B signal of the quadrature encoder to GPIO21.

## Software Details

### Prerequisites
- **Code Composer Studio (CCS)**: Download and install from [here](https://www.ti.com/tool/CCSTUDIO).
- **C2000Ware**: Download and install from [here](https://www.ti.com/tool/C2000WARE).

### Instructions

1. **Open Code Composer Studio (CCS)**.
2. **Create a New Project**:
    - Select `File -> New -> CCS Project`.
    - Enter a project name, e.g., `eQEP_Position_Measurement`.
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
    - Click the `Run` button to start the program. The eQEP module will start capturing the quadrature encoder signals and calculating the position.

### Code Explanation

#### InitGpio
This function initializes the GPIO settings. GPIO20 and GPIO21 are configured as eQEP1A and eQEP1B, respectively.

#### InitEQep1
This function configures the eQEP1 module to capture the quadrature encoder signals and measure the position.

#### main
The main function initializes the system control and GPIO, configures the PIE control registers and vector table, initializes the eQEP module, and then enters an infinite loop where the position of the encoder can be read from `EQep1Regs.QPOSCNT`.

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
- [C2000 Workshop](https://software-dl.ti.com/trainingTTO/trainingTTO_public_sw/C2000%20Piccolo%20One-D
