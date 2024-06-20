/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the PWM (Pulse Width Modulation) module to generate a PWM signal on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The PWM module is configured to generate a PWM signal with a specified frequency and duty cycle.
 *
 * The code initializes the system control and GPIO settings, configures the PWM module, and generates the PWM signal.
 *
 * This example is intended to help users get started with basic PWM generation on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;   // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;  // Configure GPIO0 as EPWM1A
    EDIS;
}

void InitPwm()
{
    EALLOW;
    SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1; // Enable ePWM1 clock
    EDIS;

    EPwm1Regs.TBPRD = 1500;           // Set period for ePWM1
    EPwm1Regs.TBPHS.half.TBPHS = 0;   // Set phase register to 0
    EPwm1Regs.TBCTL.bit.CTRMODE = 0;  // Up-count mode
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET; // Set PWM1A on CMPA up
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR; // Clear PWM1A on CMPA down
    EPwm1Regs.CMPA.half.CMPA = 750;   // Set compare A value
}

void main(void)
{
    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO
    InitPwm();     // Initialize the PWM

    while(1)
    {
        // PWM signal generation in an infinite loop
    }
}
