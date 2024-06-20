/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the I2C (Inter-Integrated Circuit) module to communicate with an external I2C device as a slave
 * on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F). The I2C is configured to communicate at a standard speed of 100 kHz.
 *
 * The code initializes the system control and GPIO settings, configures the I2C module as a slave, and communicates with an I2C master device.
 *
 * This example is intended to help users get started with basic I2C slave operations on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

#define I2C_SLAVE_ADDRESS 0x50 // Slave device address

__interrupt void i2c_isr(void);

void InitI2C()
{
    EALLOW;
    I2caRegs.I2CSAR = I2C_SLAVE_ADDRESS; // Set the slave address
    I2caRegs.I2CPSC.all = 9; // Prescaler - need 7-12 Mhz on module clk (assuming 60 MHz SYSCLKOUT)
    I2caRegs.I2CCLKL = 10;   // NOTE: must be non zero
    I2caRegs.I2CCLKH = 5;    // NOTE: must be non zero
    I2caRegs.I2CIER.all = 0x24; // Enable SCD & ARDY interrupts

    I2caRegs.I2CMDR.all = 0x0020; // Take I2C out of reset
    I2caRegs.I2CMDR.all = 0x0020; // Release stop condition
    EDIS;
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

    InitPieCtrl(); // Initialize the PIE control registers
    InitPieVectTable(); // Initialize the PIE vector table

    EALLOW;
    PieVectTable.I2CINT1A = &i2c_isr; // Map ISR to the PIE vector table
    EDIS;

    IER |= M_INT8; // Enable CPU INT8
    PieCtrlRegs.PIEIER8.bit.INTx1 = 1; // Enable PIE Group 8 interrupt 1

    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    while(1)
    {
        // Wait for I2C communication
    }
}

__interrupt void i2c_isr(void)
{
    if (I2caRegs.I2CISRC.bit.INTCODE == 0x6) // Receive data
    {
        Uint16 receivedData = I2caRegs.I2CDRR;
        // Process received data
    }
    else if (I2caRegs.I2CISRC.bit.INTCODE == 0x8) // Transmit data
    {
        I2caRegs.I2CDXR = 0xA5; // Send data
    }

    I2caRegs.I2CSTR.bit.SCD = 1; // Clear stop condition detected
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP8; // Acknowledge interrupt
}
