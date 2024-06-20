/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to blink an LED on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The onboard LED is connected to GPIO0 and will be toggled in an infinite loop with a delay.
 *
 * The code initializes the system control and GPIO settings. Specifically, it configures GPIO0 as an output pin.
 * In the main function, the system control is initialized, CPU interrupts are disabled, and the GPIO is set up.
 * The program then enters an infinite loop where the LED is toggled on and off with a delay of 500 milliseconds.
 *
 * This example is intended to help users get started with basic GPIO operations on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all = 0;      // GPIO functionality
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; // GPIO0 as output
    EDIS;
}

void main(void)
{
    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO

    while(1)
    {
        GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1; // Toggle the LED
        DELAY_US(500000); // Delay for a while
    }
}
