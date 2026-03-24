/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
*/

/*
? [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA2 aliases
#define SW_TRIS                 TRISAbits.TRISA2
#define SW_LAT                  LATAbits.LATA2
#define SW_PORT                 PORTAbits.RA2
#define SW_WPU                  WPUAbits.WPUA2
#define SW_OD                   ODCONAbits.ODCA2
#define SW_ANS                  ANSELAbits.ANSA2
#define SW_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define SW_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define SW_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define SW_GetValue()           PORTAbits.RA2
#define SW_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define SW_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define SW_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define SW_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define SW_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define SW_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define SW_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define SW_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA4 aliases
#define VR_TRIS                 TRISAbits.TRISA4
#define VR_LAT                  LATAbits.LATA4
#define VR_PORT                 PORTAbits.RA4
#define VR_WPU                  WPUAbits.WPUA4
#define VR_OD                   ODCONAbits.ODCA4
#define VR_ANS                  ANSELAbits.ANSA4
#define VR_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define VR_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define VR_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define VR_GetValue()           PORTAbits.RA4
#define VR_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define VR_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define VR_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define VR_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define VR_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define VR_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define VR_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define VR_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RA5 aliases
#define VIN_TRIS                 TRISAbits.TRISA5
#define VIN_LAT                  LATAbits.LATA5
#define VIN_PORT                 PORTAbits.RA5
#define VIN_WPU                  WPUAbits.WPUA5
#define VIN_OD                   ODCONAbits.ODCA5
#define VIN_ANS                  ANSELAbits.ANSA5
#define VIN_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define VIN_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define VIN_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define VIN_GetValue()           PORTAbits.RA5
#define VIN_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define VIN_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define VIN_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define VIN_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define VIN_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define VIN_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define VIN_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define VIN_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)
// get/set IO_RC6 aliases
#define SCL_TRIS                 TRISCbits.TRISC6
#define SCL_LAT                  LATCbits.LATC6
#define SCL_PORT                 PORTCbits.RC6
#define SCL_WPU                  WPUCbits.WPUC6
#define SCL_OD                   ODCONCbits.ODCC6
#define SCL_ANS                  ANSELCbits.ANSC6
#define SCL_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define SCL_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define SCL_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define SCL_GetValue()           PORTCbits.RC6
#define SCL_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define SCL_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define SCL_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define SCL_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define SCL_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define SCL_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define SCL_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)
// get/set IO_RC7 aliases
#define SDA_TRIS                 TRISCbits.TRISC7
#define SDA_LAT                  LATCbits.LATC7
#define SDA_PORT                 PORTCbits.RC7
#define SDA_WPU                  WPUCbits.WPUC7
#define SDA_OD                   ODCONCbits.ODCC7
#define SDA_ANS                  ANSELCbits.ANSC7
#define SDA_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define SDA_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define SDA_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define SDA_GetValue()           PORTCbits.RC7
#define SDA_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define SDA_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define SDA_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define SDA_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define SDA_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define SDA_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define SDA_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/