/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the I2C (Inter-Integrated Circuit) module to communicate with an external I2C device as a master
 * on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F). The I2C is configured to communicate at a standard speed of 100 kHz.
 *
 * The code initializes the system control and GPIO settings, configures the I2C module, and communicates with an I2C slave device.
 *
 * This example is intended to help users get started with basic I2C master operations on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

#define I2C_SLAVE_ADDRESS 0x50 // Slave device address

void InitI2C()
{
    I2caRegs.I2CSAR = I2C_SLAVE_ADDRESS; // Set the slave address
    I2caRegs.I2CPSC.all = 9; // Prescaler - need 7-12 Mhz on module clk (assuming 60 MHz SYSCLKOUT)
    I2caRegs.I2CCLKL = 10;   // NOTE: must be non zero
    I2caRegs.I2CCLKH = 5;    // NOTE: must be non zero
    I2caRegs.I2CIER.all = 0x24; // Enable SCD & ARDY interrupts

    I2caRegs.I2CMDR.all = 0x0020; // Take I2C out of reset
    I2caRegs.I2CMDR.all = 0x0020; // Release stop condition
}

void I2CWriteData(Uint16 data)
{
    while (I2caRegs.I2CMDR.bit.STP == 1); // Wait until the STP bit is cleared
    I2caRegs.I2CMDR.all = 0x6E20; // Generate START condition, transmit mode
    I2caRegs.I2CDXR = data; // Send data
    while (I2caRegs.I2CMDR.bit.STP == 1); // Wait until the STP bit is cleared
}

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO32 = 0; // Enable pull-up on GPIO32 (SDAA)
    GpioCtrlRegs.GPAPUD.bit.GPIO33 = 0; // Enable pull-up on GPIO33 (SCLA)
    GpioCtrlRegs.GPAMUX1.bit.GPIO32 = 1; // Configure GPIO32 as SDAA
    GpioCtrlRegs.GPAMUX1.bit.GPIO33 = 1; // Configure GPIO33 as SCLA
    EDIS;
}

void main(void)
{
    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO
    InitI2C();     // Initialize the I2C

    while(1)
    {
        I2CWriteData(0xA5); // Send data to I2C slave
        DELAY_US(1000000); // Delay for 1 second
    }
}
