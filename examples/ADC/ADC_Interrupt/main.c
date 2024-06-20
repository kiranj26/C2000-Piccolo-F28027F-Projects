/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: Feb 20, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the ADC (Analog-to-Digital Converter) with interrupts on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The analog input is connected to ADCINA0.
 *
 * The code initializes the system control and GPIO settings, configures the ADC to read the analog input and trigger an interrupt,
 * and processes the ADC result in the interrupt service routine (ISR).
 *
 * This example is intended to help users get started with using ADC interrupts on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

__interrupt void adc_isr(void);

void InitAdc()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1; // Enable ADC peripheral clock
    AdcRegs.ADCTRL1.bit.ADCBGPWD = 1; // Power up bandgap
    AdcRegs.ADCTRL1.bit.ADCREFPWD = 1; // Power up reference
    AdcRegs.ADCTRL1.bit.ADCPWDN = 1; // Power up rest of ADC
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 6; // Set ADC clock prescaler
    DELAY_US(1000); // Delay for 1ms to allow ADC to power up
    EDIS;
}

void ConfigureAdc()
{
    EALLOW;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1; // Cascaded mode
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0; // One conversion
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0; // ADCINA0
    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1; // Enable SOC on EPWM SOCA
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1; // Enable interrupt
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1; // Reset SEQ1
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1; // Start conversion
    EDIS;
}

void InitEPwm()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1; // Enable TBCLK within the EPWM
    EPwm1Regs.ETSEL.bit.SOCAEN = 1; // Enable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL = 4; // Select SOC from CMPA on upcount
    EPwm1Regs.ETPS.bit.SOCAPRD = 1; // Generate pulse on 1st event
    EPwm1Regs.CMPA.half.CMPA = 0x0080; // Set compare A value
    EPwm1Regs.TBPRD = 0xFFFF; // Set period for ePWM1
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Up-count mode
    EDIS;
}

void main(void)
{
    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitAdc();     // Initialize the ADC
    ConfigureAdc(); // Configure ADC settings
    InitEPwm();    // Initialize EPWM to trigger ADC conversions

    InitPieCtrl(); // Initialize the PIE control registers
    InitPieVectTable(); // Initialize the PIE vector table

    EALLOW;
    PieVectTable.ADCINT1 = &adc_isr; // Map ISR to the PIE vector table
    EDIS;

    IER |= M_INT1; // Enable CPU INT1
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1; // Enable PIE Group 1 interrupt 6

    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    while(1) { }
}

__interrupt void adc_isr(void)
{
    Uint16 adcResult;

    adcResult = AdcRegs.ADCRESULT0 >> 4; // Get ADC result

    // Do something with the ADC result

    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Clear ADCINT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge interrupt
}
