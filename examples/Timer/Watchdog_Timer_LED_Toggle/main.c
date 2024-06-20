/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the Watchdog Timer (WDT) to toggle an LED on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The onboard LED connected to GPIO0 will be toggled in the watchdog interrupt service routine (ISR).
 *
 * The code initializes the system control and GPIO settings, configures the Watchdog Timer to generate periodic interrupts,
 * and sets up an interrupt service routine to handle the watchdog interrupts.
 *
 * This example is intended to help users get started with basic watchdog timer operations and interrupt handling on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

__interrupt void watchdog_isr(void);

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all = 0;      // GPIO functionality
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; // GPIO0 as output
    EDIS;
}

void InitWatchdog()
{
    EALLOW;
    SysCtrlRegs.WDCR = 0x28; // Disable watchdog, set pre-scaler to 1
    SysCtrlRegs.WDCR = 0x68; // Enable watchdog, set pre-scaler to 1
    EDIS;
}

void main(void)
{
    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO
    InitPieCtrl(); // Initialize the PIE control registers
    InitPieVectTable(); // Initialize the PIE vector table

    EALLOW;
    PieVectTable.WD = &watchdog_isr; // Map ISR to the PIE vector table
    EDIS;

    IER |= M_INT1; // Enable CPU INT1
    PieCtrlRegs.PIEIER1.bit.INTx8 = 1; // Enable PIE group 1 interrupt 8

    InitWatchdog(); // Initialize the Watchdog Timer

    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    while(1)
    {
        SysCtrlRegs.WDKEY = 0x55; // Service the watchdog
        SysCtrlRegs.WDKEY = 0xAA; // Service the watchdog
        DELAY_US(1000000); // 1 second delay
    }
}

__interrupt void watchdog_isr(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1; // Toggle the LED
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge the interrupt
}
