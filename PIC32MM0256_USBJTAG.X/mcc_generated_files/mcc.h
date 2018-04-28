/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.h

  @Summary:
    This is the mcc.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.53.0.1
        Device            :  PIC32MM0256GPM048
    The generated drivers are tested against the following:
        Compiler          :  XC32 v1.44
        MPLAB             :  MPLAB X v4.05
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef MCC_H
#define	MCC_H
#define WDT_CLR_KEY 0x5743
#include <xc.h>
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include "spi2.h"
#include "interrupt_manager.h"
#include "exceptions.h"
#include "usb/usb.h"

#define _XTAL_FREQ  24000000UL

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Unlocks the write protected register to enable any write operation
 *                  MCC GUI
 * @Example
    SYSTEM_RegUnlock();
 */
inline static void SYSTEM_RegUnlock(void)
{
    SYSKEY = 0x0; //write invalid key to force lock
    SYSKEY = 0xAA996655; //write Key1 to SYSKEY
    SYSKEY = 0x556699AA; //write Key2 to SYSKEY
}

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Locks the write protected register to disable any write operation
 *                  MCC GUI
 * @Example
    SYSTEM_RegLock();
 */
inline static void SYSTEM_RegLock(void)
{
   SYSKEY = 0x00000000; 
}

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the device to the default states configured in the
 *                  MCC GUI
 * @Example
    SYSTEM_Initialize(void);
 */
void SYSTEM_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the oscillator to the default states configured in the
 *                  MCC GUI
 * @Example
    OSCILLATOR_Initialize(void);
 */
void OSCILLATOR_Initialize(void);

/* Enables Watch Dog Timer (WDT) using the software bit.
 * @example
 * <code>
 * WDT_WatchdogtimerSoftwareEnable();
 * </code>
 */
inline static void WDT_WatchdogtimerSoftwareEnable(void)
{
    WDTCONbits.ON = 1;
}
/* Disables Watch Dog Timer (WDT) using the software bit.
 * @example
 * <code>
 * WDT_WatchdogtimerSoftwareDisable();
 * </code>
 */
inline static void WDT_WatchdogtimerSoftwareDisable(void)
{
    WDTCONbits.ON = 0;
}
/* Clears the Watch Dog Timer (WDT).
 * @example
 * <code>
 * WDT_WatchdogTimerClear();
 * </code>
 */
inline static void WDT_WatchdogTimerClear(void)
{
    WDTCONbits.WDTCLRKEY = WDT_CLR_KEY;
}
#endif	/* MCC_H */
/**
 End of File
*/