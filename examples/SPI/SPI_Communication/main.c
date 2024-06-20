/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: Apr 1, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the SPI (Serial Peripheral Interface) module to communicate with an external SPI device on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The SPI is configured to communicate at a standard speed.
 *
 * The code initializes the system control and GPIO settings, configures the SPI module, and handles data transmission and reception.
 *
 * This example is intended to help users get started with using SPI for data communication on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0; // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0; // Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0; // Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0; // Enable pull-up on GPIO19 (SPISTEA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynchronous input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynchronous input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynchronous input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynchronous input GPIO19 (SPISTEA)
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;  // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;  // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;  // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;  // Configure GPIO19 as SPISTEA
    EDIS;
}

void InitSpi()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1; // Enable SPI-A clock
    SpiaRegs.SPICCR.all = 0x0047; // 8-bit character, Loop-back mode, Enable SPI
    SpiaRegs.SPICTL.all = 0x0006; // Master mode, Enable transmission
    SpiaRegs.SPIBRR = 0x007F; // Baud rate
    SpiaRegs.SPICCR.bit.SPISWRESET = 1; // Release SPI from reset
    SpiaRegs.SPIPRI.bit.FREE = 1; // Free run, continue SPI operation
    EDIS;
}

void SpiTransmit(Uint16 data)
{
    while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG); // Wait if buffer is full
    SpiaRegs.SPITXBUF = data; // Transmit data
}

void main(void)
{
    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO
    InitSpi();     // Initialize the SPI

    while(1)
    {
        SpiTransmit(0xA5); // Send data to SPI slave
        DELAY_US(1000000); // Delay for 1 second
    }
}
