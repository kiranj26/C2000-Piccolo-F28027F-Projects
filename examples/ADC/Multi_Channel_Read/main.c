/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: Feb 23, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the ADC (Analog-to-Digital Converter) to read multiple analog inputs sequentially on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The analog inputs are connected to ADCINA0 and ADCINA1.
 *
 * The code initializes the system control and GPIO settings, configures the ADC to read the analog inputs sequentially,
 * and processes the ADC results.
 *
 * This example is intended to help users get started with reading multiple analog inputs using the ADC on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

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

void ConfigureAdcSequence()
{
    EALLOW;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1; // Cascaded mode
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 1; // Two conversions
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0; // ADCINA0
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 1; // ADCINA1
    EDIS;
}

void main(void)
{
    Uint16 adcResult0, adcResult1;

    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitAdc();     // Initialize the ADC
    ConfigureAdcSequence(); // Configure ADC sequence

    while(1)
    {
        AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1; // Start conversion
        while(AdcRegs.ADCST.bit.SEQ1_BSY == 1); // Wait for conversion to complete
        adcResult0 = AdcRegs.ADCRESULT0 >> 4; // Get ADC result for ADCINA0
        adcResult1 = AdcRegs.ADCRESULT1 >> 4; // Get ADC result for ADCINA1

        // Do something with the ADC results
    }
}
