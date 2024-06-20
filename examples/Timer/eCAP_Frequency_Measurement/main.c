/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the eCAP (Enhanced Capture) module to measure the frequency of an external signal on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The external signal is connected to GPIO24 (eCAP1).
 *
 * The code initializes the system control and GPIO settings, configures the eCAP module to capture the signal,
 * and calculates the frequency of the external signal.
 *
 * This example is intended to help users get started with basic eCAP operations and frequency measurement on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

__interrupt void ecap1_isr(void);

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // Enable pull-up on GPIO24
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0; // Synch to SYSCLKOUT GPIO24
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;  // Configure GPIO24 as eCAP1
    EDIS;
}

void InitECap1()
{
    EALLOW;
    SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1; // Enable eCAP1 clock
    EDIS;

    ECap1Regs.ECEINT.all = 0x0000;      // Disable all capture interrupts
    ECap1Regs.ECCLR.all = 0xFFFF;       // Clear all CAP interrupt flags
    ECap1Regs.ECCTL1.bit.CAPLDEN = 0;   // Disable CAP1-CAP4 register loads
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1; // Stop the counter

    ECap1Regs.ECCTL2.bit.CONT_ONESHT = 0; // Continuous mode
    ECap1Regs.ECCTL2.bit.STOP_WRAP = 3;   // Stop at 4 events
    ECap1Regs.ECCTL1.bit.CAP1POL = 1;     // Falling edge
    ECap1Regs.ECCTL1.bit.CTRRST1 = 1;     // Reset counter on CAP1
    ECap1Regs.ECCTL1.bit.CAP2POL = 0;     // Rising edge
    ECap1Regs.ECCTL1.bit.CTRRST2 = 1;     // Reset counter on CAP2
    ECap1Regs.ECCTL1.bit.CAP3POL = 1;     // Falling edge
    ECap1Regs.ECCTL1.bit.CTRRST3 = 1;     // Reset counter on CAP3
    ECap1Regs.ECCTL1.bit.CAP4POL = 0;     // Rising edge
    ECap1Regs.ECCTL1.bit.CTRRST4 = 1;     // Reset counter on CAP4
    ECap1Regs.ECCTL2.bit.SYNCI_EN = 0;    // Disable sync-in
    ECap1Regs.ECCTL2.bit.SYNCO_SEL = 0;   // Sync-out disabled
    ECap1Regs.ECCTL1.bit.CAPLDEN = 1;     // Enable CAP1-CAP4 register loads
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;   // Start counter
    ECap1Regs.ECEINT.bit.CEVT4 = 1;       // 4 events = interrupt

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;    // Enable the PIE block
    PieVectTable.ECAP1_INT = &ecap1_isr;  // Set eCAP1 ISR
    PieCtrlRegs.PIEIER4.bit.INTx1 = 1;    // Enable PIE Group 4, INT 1
    IER |= M_INT4;                        // Enable CPU INT4
    EINT;                                 // Enable Global interrupt INTM
    ERTM;                                 // Enable Global realtime interrupt DBGM
}

void main(void)
{
    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO
    InitPieCtrl(); // Initialize the PIE control registers
    InitPieVectTable(); // Initialize the PIE vector table

    InitECap1();   // Initialize eCAP1

    while(1) { }
}

__interrupt void ecap1_isr(void)
{
    Uint32 period;
    period = ECap1Regs.CAP2 - ECap1Regs.CAP1; // Calculate the period of the signal
    // Calculate frequency based on period
    float frequency = 1 / ((period * 1e-9) / 60); // Assuming 60 MHz SYSCLKOUT

    ECap1Regs.ECCLR.all = 0xFFFF; // Clear all CAP interrupt flags
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4; // Acknowledge the interrupt
}
