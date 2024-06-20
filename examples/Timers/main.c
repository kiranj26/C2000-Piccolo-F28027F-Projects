/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use a timer interrupt on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The onboard LED connected to GPIO0 will be toggled in the timer interrupt service routine (ISR).
 *
 * The code initializes the system control and GPIO settings, configures Timer0 to generate periodic interrupts,
 * and sets up an interrupt service routine to handle the timer interrupts.
 *
 * This example is intended to help users get started with basic timer operations and interrupt handling on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

__interrupt void cpu_timer0_isr(void);

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all = 0;      // GPIO functionality
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; // GPIO0 as output
    EDIS;
}

void InitTimer0()
{
    EALLOW;
    CpuTimer0Regs.PRD.all = 0x1E8480; // Set period for 500 ms
    CpuTimer0Regs.TPR.all = 0;
    CpuTimer0Regs.TPRH.all = 0;
    CpuTimer0Regs.TCR.bit.TSS = 1;    // Stop the timer
    CpuTimer0Regs.TCR.bit.TRB = 1;    // Reload the timer
    CpuTimer0Regs.TCR.bit.TIE = 1;    // Enable timer interrupt
    CpuTimer0Regs.TCR.bit.TSS = 0;    // Start the timer
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
    PieVectTable.TINT0 = &cpu_timer0_isr; // Map ISR to the PIE vector table
    EDIS;

    IER |= M_INT1; // Enable CPU INT1
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; // Enable PIE group 1 interrupt 7

    InitTimer0(); // Initialize Timer0

    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    while(1) { }
}

__interrupt void cpu_timer0_isr(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1; // Toggle the LED
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge the interrupt
}
