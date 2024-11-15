/*******************************************************************************
  Input / Output Port COnfiguration Routine source File

  File Name:
    port_config.c

  Summary:
    This file includes subroutine for initializing GPIO pins as analog/digital,
    input or output etc. Also to PPS functionality to Remap-able input or output 
    pins

  Description:
    Definitions in the file are for dsPIC33CDVL64MC106 on Motor Control 
    Development board from Microchip
 
*******************************************************************************/
/*******************************************************************************
 * Copyright (c) 2022 Microchip Technology Inc. and its subsidiaries
 * 
 * Subject to your compliance with these terms, you may use Microchip software
 * and any derivatives exclusively with Microchip products. You are responsible
 * for complying with 3rd party license terms applicable to your use of 3rd
 * party software (including open source software) that may accompany Microchip
 * software. SOFTWARE IS ?AS IS.? NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR
 * STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF
 * NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN
 * NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S TOTAL LIABILITY ON ALL CLAIMS
 * RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID
 * DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <xc.h>
#include "port_config.h"
#include "userparms.h"

static void configureGateDriverFault(void);
// *****************************************************************************
/* Function:
    SetupGPIOPorts()

  Summary:
    Routine to set-up GPIO ports

  Description:
    Function initializes GPIO pins for input or output ports,analog/digital pins,
    remap the peripheral functions to desires RPx pins.

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */

void SetupGPIOPorts(void)
{
    // Reset all PORTx register (all inputs)
    #ifdef TRISA
        TRISA = 0xFFFF;
        LATA  = 0x0000;
    #endif
    #ifdef ANSELA
        ANSELA = 0x0000;
    #endif

    #ifdef TRISB
        TRISB = 0xFFFF;
        LATB  = 0x0000;
    #endif
    #ifdef ANSELB
        ANSELB = 0x0000;
    #endif

    #ifdef TRISC
        TRISC = 0xFFFF;
        LATC  = 0x0000;
    #endif
    #ifdef ANSELC
        ANSELC = 0x0000;
    #endif

    #ifdef TRISD
        TRISD = 0xFFFF;
        LATD  = 0x0000;
    #endif
    #ifdef ANSELD
        ANSELD = 0x0000;
    #endif

    #ifdef TRISE
        TRISE = 0xFFFF;
        LATE  = 0x0000;
    #endif
    #ifdef ANSELE
        ANSELE = 0x0000;
    #endif

    MapGPIOHWFunction();

    return;
}
// *****************************************************************************
/* Function:
    Map_GPIO_HW_Function()

  Summary:
    Routine to setup GPIO pin used as input/output analog/digital etc

  Description:
    Function initializes GPIO pins as input or output port pins,analog/digital 
    pins,remap the peripheral functions to desires RPx pins.

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */

void MapGPIOHWFunction(void)
{
    
    /* ANALOG SIGNALS */

    // Configure Port pins for Motor Current Sensing
    
    // Ibus Out
    ANSELAbits.ANSELA0 = 1;
    TRISAbits.TRISA0 = 0;   // Pin 15: OA1OUT/AN0/CMP1A/IBIAS0/RA0
    
    //Ia Out
    ANSELBbits.ANSELB2 = 1;
    TRISBbits.TRISB2 = 0;   //Pin 32: OA2OUT/AN1/AN7/ANA0/CMP1D/CMP2D/CMP3D/RP34/SCL3/INT0/RB2
    
    //Ib Out
    ANSELAbits.ANSELA4 = 1;
    TRISAbits.TRISA4 = 0;   //Pin 19: OA3OUT/AN4/CMP3B/IBIAS3/RA4
    
    //Ibus-
    ANSELAbits.ANSELA1 = 1;
    TRISAbits.TRISA1 = 1;   //Pin 16: OA1IN-/ANA1/RA1
    
    //Ibus+ 
    ANSELAbits.ANSELA2 = 1;
    TRISAbits.TRISA2 = 1;   //Pin 17: OA1IN+/AN9/PMA6/RA2
    
    //Ia- 
    ANSELBbits.ANSELB3 = 1;
    TRISBbits.TRISB3 = 1;   //Pin 22: PGD2/OA2IN-/AN8/RP35/RB3
    
    //Ia+ 
    ANSELBbits.ANSELB4 = 1;
    TRISBbits.TRISB4 = 1;   //Pin 23: PGC2/OA2IN+/RP36/RB4
    
    //Ib- 
    ANSELCbits.ANSELC1 = 1;
    TRISCbits.TRISC1 = 1;   //Pin 33: OA3IN-/AN13/CMP1B/ISRC0/RP49/PMA7/RC1
    
    //Ib+ 
    ANSELCbits.ANSELC2 = 1;
    TRISCbits.TRISC2 = 1;   //Pin 34: OA3IN+/AN14/CMP2B/ISRC1/RP50/PMD13/PMA13/RC2
    
    //Op-Amp Configuration
    AMPCON1Hbits.NCHDIS2 = 0;    //Wide input range for Op Amp #2
    AMPCON1Lbits.AMPEN2 = 1;     //Enables Op Amp #2
    
    AMPCON1Hbits.NCHDIS1 = 0;    //Wide input range for Op Amp #1
    AMPCON1Lbits.AMPEN1 = 1;     //Enables Op Amp #1
    
    AMPCON1Hbits.NCHDIS3 = 0;    //Wide input range for Op Amp #3
    AMPCON1Lbits.AMPEN3 = 1;     //Enables Op Amp #3
    
    AMPCON1Lbits.AMPON = 1;      //Enables op amp modules if their respective AMPENx bits are also asserted
    
    /*DC Bus Voltage Signals*/
    ANSELCbits.ANSELC0 = 1;
    TRISCbits.TRISC0 = 1;   
    
    //Phase_B Voltage
    ANSELBbits.ANSELB8 = 1;
    TRISBbits.TRISB8 = 1; 
    
    //Phase A Voltage
    ANSELBbits.ANSELB9 = 1;
    TRISBbits.TRISB9 = 1;   
    /* Digital SIGNALS */   
    // DIGITAL INPUT/OUTPUT PINS

    // Inverter Control - PWM Outputs
    // PWM1L : PIN #3  RP47/PWM1L/PMD6/RB15
    // PWM1H : PIN #1  RP46/PWM1H/PMD5/RB14
    // PWM2L : PIN #80  RP45/PWM2L/PMD4/RB13
    // PWM2H : PIN #78  TDI/RP44/PWM2H/PMD3/RB12
    // PWM3L : PIN #76  TCK/RP43/PWM3L/PMD2/RB11
    // PWM3H : PIN #75  TMS/RP42/PWM3H/PMD1/RB10
    TRISBbits.TRISB14 = 0 ;          
    TRISBbits.TRISB15 = 0 ;         
    TRISBbits.TRISB12 = 0 ;          
    TRISBbits.TRISB13 = 0 ;           
    TRISBbits.TRISB10 = 0 ;          
    TRISBbits.TRISB11 = 0 ;         
    
    /** Configure RC5 and RC10 for GPIO output (RC10 LIN_EN) */
    //ANSELCbits.ANSELC10 = 1;
    LATCbits.LATC10 = 1;
    TRISCbits.TRISC10 = 0;
    LATCbits.LATC5 = 1;
    TRISCbits.TRISC5 = 0;
	
	/** Re-map UART Channels to the device pins connected to the following 
        pins on the Motor Control Development Boards .
    */
    _U1RXR = 72;
    _RP57R = 0b000001;
    
    /** Re-map UART pins to interface with LIN transceiver interconnect
        pins.
    */
    _RP53R = 27;  // RC5/RP53 LIN_TXD, map to UART3 TXD
    _U3RXR = 59; // RC11/RP59 LIN_RXD, map to UART3 RXD
    //_RP51R = 3;
    
    _RP60R = 3;
    
    _CNPUC12 = 1;
    TRISCbits.TRISC13 = 0;
    
     configureGateDriverFault();
    /*Configuring DE2 Pin*/
     _U2RXR = 60;
     _RP60R = 3; 
    
}
void configureGateDriverFault(void)
{
    uint16_t bufferPortD;
  
    TRISDbits.TRISD1 = 1;
   _CNPUD1 = 1;
   
    CNCOND = 0;
/*  ON: Change Notification (CN) Control for PORTx On bit
    1 = CN is enabled
    0 = CN is disabled   */
    CNCONDbits.ON = 1;
/*    CNSTYLE: Change Notification Style Selection bit
    1 = Edge style (detects edge transitions, bits are used for a CNE)
    0 = Mismatch style (detects change from last port read event)       */    
    CNCONDbits.CNSTYLE = 1;
     
    CNEN0D = 0;
    CNEN0Dbits.CNEN0D1 = 0;
    CNEN1D = 0;
    CNEN1Dbits.CNEN1D1 = 1;
    
    bufferPortD = PORTD;
    _CNDIF = 0;
    _CNDIE = 1;
    _CNDIP = 7;
     
}
