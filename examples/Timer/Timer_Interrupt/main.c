/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: Jan 25, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the Timer module with interrupts on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The timer is configured to generate an interrupt at a regular interval.
 *
 * The code initializes the system control and GPIO settings, configures the Timer module, and handles the timer interrupt.
 *
 * This example is intended to help users get started with using timers and interrupts on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

__interrupt void cpu_timer0_isr(void);

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; // GPIO0 as GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;  // GPIO0 as output
    EDIS;
}

void InitTimer()
{
    EALLOW;
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 60, 1000000); // Configure CPU-Timer 0 to interrupt every 1 second
    PieVectTable.TINT0 = &cpu_timer0_isr;    // Map ISR to the PIE vector table
    EDIS;

    IER |= M_INT1; // Enable CPU INT1
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; // Enable PIE Group 1 interrupt 7 (TINT0)

    CpuTimer0Regs.TCR.all = 0x4000; // Start CPU-Timer 0
}

void main(void)
{
    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO
    InitTimer();   // Initialize the Timer

    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    while(1)
    {
        // Wait for timer interrupt
    }
}

__interrupt void cpu_timer0_isr(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1; // Toggle GPIO0

    CpuTimer0Regs.TCR.bit.TIF = 1; // Clear Timer interrupt flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge interrupt
}