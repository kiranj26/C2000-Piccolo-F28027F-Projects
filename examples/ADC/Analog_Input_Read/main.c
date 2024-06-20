/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: Feb 21, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the ADC (Analog-to-Digital Converter) to read an analog input on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F).
 * The analog input is connected to ADCINA0 (pin 7).
 *
 * The code initializes the system control and GPIO settings, configures the ADC to read the analog input,
 * and processes the ADC result.
 *
 * This example is intended to help users get started with basic ADC operations and analog input reading on the F28027F microcontroller.
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

void main(void)
{
    Uint16 adcResult;

    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitAdc();     // Initialize the ADC

    while(1)
    {
        AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1; // Start conversion
        while(AdcRegs.ADCST.bit.SEQ1_BSY == 1); // Wait for conversion to complete
        adcResult = AdcRegs.ADCRESULT0 >> 4; // Get ADC result (12-bit value)

        // Do something with the ADC result
    }
}
