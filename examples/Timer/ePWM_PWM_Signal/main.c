/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the ePWM (Enhanced Pulse Width Modulator) module to generate a PWM signal on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The PWM signal is generated on GPIO0 (EPWM1A).
 *
 * The code initializes the system control and GPIO settings, configures the ePWM module to generate a PWM signal with a specific frequency and duty cycle.
 *
 * This example is intended to help users get started with basic PWM signal generation using the ePWM module on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1; // Configure GPIO0 as EPWM1A
    EDIS;
}

void InitEPwm1()
{
    EPwm1Regs.TBPRD = 1500;                // Set period for 20 kHz
    EPwm1Regs.TBPHS.all = 0;               // Set phase to 0
    EPwm1Regs.TBCTR = 0;                   // Clear counter
    EPwm1Regs.CMPA.half.CMPA = 750;        // Set compare A value for 50% duty cycle

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Up-count mode
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;    // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;

    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;      // Set PWM1A on event A, up count
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_CLEAR;    // Clear PWM1A on zero count
}

void main(void)
{
    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO
    InitEPwm1();   // Initialize EPWM1

    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    while(1) { }
}
