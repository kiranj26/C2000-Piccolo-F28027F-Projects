/*
 * Author: Kiran Jojare
 * Email: kijo7257@colorado.edu
 * Date: June 19, 2024
 * Version: 1.0
 *
 * Description:
 * This code demonstrates how to use the UART (Universal Asynchronous Receiver/Transmitter) module with interrupts to handle both transmitting and receiving data
 * on the Texas Instruments C2000 Piccolo LaunchPad Evaluation Kit (LAUNCHHXL-F28027F). The UART is configured to communicate at a baud rate of 9600.
 *
 * The code initializes the system control and GPIO settings, configures the UART module, and handles data transmission and reception in interrupt service routines (ISRs).
 *
 * This example is intended to help users get started with using UART interrupts for both transmitting and receiving data on the F28027F microcontroller.
 */

#include "F2802x_Device.h"
#include "f2802x_examples.h"

__interrupt void scia_rx_isr(void);
__interrupt void scia_tx_isr(void);

char txBuffer[] = "Hello, UART Interrupt!";
int txIndex = 0;

void InitGpio()
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;   // Enable pull-up on GPIO28 (SCIRXDA)
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;   // Enable pull-up on GPIO29 (SCITXDA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; // Asynchronous input GPIO28 (SCIRXDA)
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;  // Configure GPIO28 as SCIRXDA
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // Configure GPIO29 as SCITXDA
    EDIS;
}

void InitScia()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1; // Enable SCI-A clock
    SciaRegs.SCICCR.all = 0x0007;         // 1 stop bit, No loopback, No parity, 8 char bits, async mode, idle-line protocol
    SciaRegs.SCICTL1.all = 0x0003;        // Enable TX, RX, internal SCICLK
    SciaRegs.SCICTL2.all = 0x0003;        // Enable TX, RX interrupts
    SciaRegs.SCICTL1.all = 0x0023;        // Relinquish SCI from Reset
    SciaRegs.SCIHBAUD = 0x0001;           // Set baud rate to 9600
    SciaRegs.SCILBAUD = 0x00E7;
    SciaRegs.SCIFFTX.all = 0xC022;        // Enable FIFO enhancements, clear TX FIFO, set TX FIFO level to 2
    SciaRegs.SCIFFRX.all = 0x0022;        // Enable RX FIFO, clear RX FIFO, set RX FIFO level to 2
    SciaRegs.SCIFFCT.all = 0x0;
    EDIS;
}

void main(void)
{
    InitSysCtrl(); // Initialize the CPU and configure the clock
    DINT;          // Disable CPU interrupts

    InitGpio();    // Initialize the GPIO
    InitScia();    // Initialize the UART

    InitPieCtrl(); // Initialize the PIE control registers
    InitPieVectTable(); // Initialize the PIE vector table

    EALLOW;
    PieVectTable.SCIRXINTA = &scia_rx_isr; // Map RX ISR to the PIE vector table
    PieVectTable.SCITXINTA = &scia_tx_isr; // Map TX ISR to the PIE vector table
    EDIS;

    IER |= M_INT9; // Enable CPU INT9
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1; // Enable PIE Group 9 interrupt 1 (RX)
    PieCtrlRegs.PIEIER9.bit.INTx2 = 1; // Enable PIE Group 9 interrupt 2 (TX)

    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    while(1)
    {
        // Wait for interrupt-driven communication
    }
}

__interrupt void scia_rx_isr(void)
{
    Uint16 receivedChar;

    receivedChar = SciaRegs.SCIRXBUF.all; // Read received character
    SciaRegs.SCITXBUF = receivedChar; // Echo received character

    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1; // Clear RX interrupt flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9; // Acknowledge interrupt
}

__interrupt void scia_tx_isr(void)
{
    if(txBuffer[txIndex] != '\0')
    {
        SciaRegs.SCITXBUF = txBuffer[txIndex++]; // Send next character
    }
    else
    {
        txIndex = 0; // Reset index if end of message is reached
    }

    SciaRegs.SCIFFTX.bit.TXFFINTCLR = 1; // Clear TX interrupt flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9; // Acknowledge interrupt
}
