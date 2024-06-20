/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the eQEP (Enhanced Quadrature Encoder Pulse) module to measure the position of a quadrature encoder
 * on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The quadrature encoder signals are connected to GPIO20 (eQEP1A) and GPIO21 (eQEP1B).
 *
 * The code initializes the system control and GPIO settings, configures the eQEP module to capture the encoder signals,
 * and calculates the position of the encoder.
 *
 * This example is intended to help users get started with basic eQEP operations and position measurement on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pull-up on GPIO20 (eQEP1A)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0; // Synch to SYSCLKOUT GPIO20 (eQEP1A)
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;  // Configure GPIO20 as eQEP1A

    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pull-up on GPIO21 (eQEP1B)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 0; // Synch to SYSCLKOUT GPIO21 (eQEP1B)
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;  // Configure GPIO21 as eQEP1B
    EDIS;
}

void InitEQep1()
{
    EALLOW;
    SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1; // Enable eQEP1 clock
    EDIS;

    EQep1Regs.QUPRD = 2000000;                // Unit Timer for 100Hz at 20 MHz SYSCLKOUT
    EQep1Regs.QDECCTL.bit.QSRC = 0;           // Quadrature count mode
    EQep1Regs.QEPCTL.bit.FREE_SOFT = 2;       // Emulation mode
    EQep1Regs.QEPCTL.bit.PCRM = 0;            // Reset on index event
    EQep1Regs.QEPCTL.bit.UTE = 1;             // Enable unit timer
    EQep1Regs.QEPCTL.bit.QCLM = 1;            // Latch on unit time out
    EQep1Regs.QPOSMAX = 0xFFFFFFFF;           // Maximum position count
    EQep1Regs.QEPCTL.bit.QPEN = 1;            // QEP enable
    EQep1Regs.QCAPCTL.bit.UPPS = 5;           // 1/32 for unit position prescaler
    EQep1Regs.QCAPCTL.bit.CCPS = 7;           // 1/128 for CAP clock prescaler
    EQep1Regs.QCAPCTL.bit.CEN = 1;            // Enable eCAP module
}

void main(void)
{
    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO
    InitPieCtrl(); // Initialize the PIE control registers
    InitPieVectTable(); // Initialize the PIE vector table

    InitEQep1();   // Initialize eQEP1

    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    while(1)
    {
        // The position of the encoder can be read from EQep1Regs.QPOSCNT
        Uint32 position = EQep1Regs.QPOSCNT;
        // Do something with the position value
    }
}
