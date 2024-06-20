/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: Jan 25, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use Timer1 to generate a periodic interrupt on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The onboard LED connected to GPIO0 will be toggled in the Timer1 interrupt service routine (ISR).
 *
 * The code initializes the system control and GPIO settings, configures Timer1 to generate periodic interrupts,
 * and sets up an interrupt service routine to handle the timer interrupts.
 *
 * This example is intended to help users get started with basic Timer1 operations and interrupt handling on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

__interrupt void cpu_timer1_isr(void);

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all = 0;      // GPIO functionality
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; // GPIO0 as output
    EDIS;
}

void InitCpuTimer1()
{
    EALLOW;
    CpuTimer1Regs.PRD.all = 0x1E8480; // Set period for 500 ms
    CpuTimer1Regs.TPR.all = 0;
    CpuTimer1Regs.TPRH.all = 0;
    CpuTimer1Regs.TCR.bit.TSS = 1;    // Stop the timer
    CpuTimer1Regs.TCR.bit.TRB = 1;    // Reload the timer
    CpuTimer1Regs.TCR.bit.TIE = 1;    // Enable timer interrupt
    CpuTimer1Regs.TCR.bit.TSS = 0;    // Start the timer
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
    PieVectTable.XINT13 = &cpu_timer1_isr; // Map ISR to the PIE vector table
    EDIS;

    IER |= M_INT13; // Enable CPU INT13
    InitCpuTimer1(); // Initialize Timer1

    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    while(1) { }
}

__interrupt void cpu_timer1_isr(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1; // Toggle the LED
    CpuTimer1Regs.TCR.bit.TIF = 1;        // Clear the interrupt flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP13; // Acknowledge the interrupt
}
