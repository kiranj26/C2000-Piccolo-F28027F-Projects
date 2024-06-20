# C2000 Piccolo F28027F Projects

Welcome to the C2000 Piccolo F28027F Projects repository! This repository is dedicated to exploring and leveraging the capabilities of the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F). Here, you'll find a collection of projects, examples, and resources that will help you get the most out of this powerful microcontroller. This repository will be my playground to try my hands on this hardware.

## Table of Contents
- [Introduction](#introduction)
- [Getting Started](#getting-started)
- [Projects](#projects)
  - [Blinking LED](#blinking-led)
  - [PWM Generation](#pwm-generation)
  - [ADC and Sensor Integration](#adc-and-sensor-integration)
  - [Motor Control](#motor-control)
  - [Digital Signal Processing](#digital-signal-processing)
- [Resources](#resources)
- [Contributing](#contributing)
- [License](#license)

## Introduction
The C2000 Piccolo F28027F microcontroller is a high-performance platform designed for real-time control applications. This repository aims to provide a comprehensive set of examples and projects that demonstrate the diverse capabilities of this microcontroller, from basic input/output operations to complex control systems.

## Getting Started
To get started with the projects in this repository, you'll need the following tools and software:
- **Code Composer Studio (CCS)**: The recommended integrated development environment (IDE) for developing applications on the C2000 series.
- **C2000Ware**: A comprehensive software package that includes libraries, drivers, examples, and documentation for C2000 microcontrollers.

### Installation Steps
1. Download and install [Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO).
2. Download and install [C2000Ware](https://www.ti.com/tool/C2000WARE).

## Projects

### Blinking LED
This is the classic "Hello World" project for microcontrollers. It demonstrates how to configure GPIO pins and create a simple LED blinking pattern.
- **File**: `examples/blinking_led/main.c`
- **Description**: This example configures a GPIO pin as an output and toggles the LED in a loop.

### PWM Generation
This project demonstrates how to generate Pulse Width Modulation (PWM) signals using the PWM modules on the F28027F.
- **File**: `examples/pwm_generation/main.c`
- **Description**: This example configures the PWM modules to generate a PWM signal with a specific duty cycle and frequency.

### ADC and Sensor Integration
Learn how to interface sensors using the Analog-to-Digital Converter (ADC) on the F28027F.
- **File**: `examples/adc_sensor_integration/main.c`
- **Description**: This example configures the ADC to read analog values from a connected sensor and process the data.

### Motor Control
Utilize the specialized motor control capabilities of the F28027F for controlling various types of motors.
- **File**: `examples/motor_control/main.c`
- **Description**: This project demonstrates controlling a DC motor using PWM signals and feedback from an encoder.

### Digital Signal Processing
Implement and test digital signal processing (DSP) algorithms on the F28027F.
- **File**: `examples/dsp_algorithms/main.c`
- **Description**: This project showcases the DSP capabilities of the F28027F by implementing a simple filtering algorithm.

## Resources
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
