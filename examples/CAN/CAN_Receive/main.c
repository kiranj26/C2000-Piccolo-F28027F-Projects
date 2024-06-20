/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the CAN (Controller Area Network) module to receive messages on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The CAN module is configured to communicate at a baud rate of 500 kbps.
 *
 * The code initializes the system control and GPIO settings, configures the CAN module, and receives CAN messages.
 *
 * This example is intended to help users get started with basic CAN receive operations on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0; // Enable pull-up on GPIO30 (CANRXA)
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0; // Enable pull-up on GPIO31 (CANTXA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = 3; // Asynchronous input GPIO30 (CANRXA)
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;  // Configure GPIO30 as CANRXA
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;  // Configure GPIO31 as CANTXA
    EDIS;
}

void InitCan()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ECANENCLK = 1; // Enable CAN clock
    EDIS;

    InitECana(); // Initialize eCAN module

    EALLOW;
    ECanaRegs.CANME.all = 0; // Disable all mailboxes
    ECanaRegs.CANMD.all = 0x00000000; // Set all mailboxes to receive
    ECanaRegs.CANMC.bit.CCR = 1; // Enable configuration change
    while(ECanaRegs.CANES.bit.CCE != 1); // Wait for configuration change enable

    ECanaRegs.CANBTC.all = 0x00023F00; // Set baud rate to 500 kbps
    ECanaRegs.CANMC.bit.CCR = 0; // Disable configuration change
    while(ECanaRegs.CANES.bit.CCE != 0); // Wait for configuration change disable

    ECanaRegs.CANME.all = 0xFFFFFFFF; // Enable all mailboxes
    EDIS;
}

Uint32 CanReceive(Uint16 mailbox)
{
    while((ECanaRegs.CANRMP.all & (1 << mailbox)) == 0); // Wait for message
    Uint32 data = ECanaMboxes.MBOX0.MDL.all; // Read data
    ECanaRegs.CANRMP.all = (1 << mailbox); // Clear RMP bit
    return data;
}

void main(void)
{
    Uint32 receivedData;

    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO
    InitCan();     // Initialize the CAN

    while(1)
    {
        receivedData = CanReceive(0); // Receive CAN message
        // Process received data (e.g., toggle an LED, store in memory, etc.)
    }
}
