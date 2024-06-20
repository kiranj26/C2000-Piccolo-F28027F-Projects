/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the UART (Universal Asynchronous Receiver/Transmitter) module to send and receive data on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The UART is configured to communicate at a baud rate of 9600.
 *
 * The code initializes the system control and GPIO settings, configures the UART module, and sends/receives data.
 *
 * This example is intended to help users get started with basic UART operations on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;   // Enable pull-up on GPIO28 (SCIRXDA)
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;   // Enable pull-up on GPIO29 (SCITXDA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; // Asynchronous input GPIO28 (SCIRXDA)
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;  // Configure GPIO28 as SCIRXDA
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // Configure GPIO29 as SCITXDA
    EDIS;
}

void InitScia()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1; // Enable SCI-A clock
    SciaRegs.SCICCR.all = 0x0007;         // 1 stop bit, No loopback, No parity, 8 char bits, async mode, idle-line protocol
    SciaRegs.SCICTL1.all = 0x0003;        // Enable TX, RX, internal SCICLK
    SciaRegs.SCICTL2.all = 0x0003;        // Enable TX, RX interrupts
    SciaRegs.SCICTL1.all = 0x0023;        // Relinquish SCI from Reset
    SciaRegs.SCIHBAUD = 0x0001;           // Set baud rate to 9600
    SciaRegs.SCILBAUD = 0x00E7;
    EDIS;
}

void SciaTx(char *msg)
{
    int i;
    for(i = 0; msg[i] != '\0'; i++)
    {
        while(SciaRegs.SCIFFTX.bit.TXFFST != 0); // Wait until TX FIFO is empty
        SciaRegs.SCITXBUF = msg[i]; // Send character
    }
}

void main(void)
{
    char msg[] = "Hello, UART!";

    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO
    InitScia();    // Initialize the UART

    while(1)
    {
        SciaTx(msg); // Send message
        DELAY_US(1000000); // Delay for 1 second
    }
}
