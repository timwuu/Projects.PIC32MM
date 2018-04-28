/**
  System Interrupts Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for MPLAB(c) Code Configurator interrupts.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.45
        Device            :  PIC32MM0256GPM048
    The generated drivers are tested against the following:
        Compiler          :  XC32 v1.44
        MPLAB             :  MPLAB X v4.05

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>
#include <stdbool.h>
/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RB0, high using LATBbits.LATB0.

  @Description
    Sets the GPIO pin, RB0, high using LATBbits.LATB0.

  @Preconditions
    The RB0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB0 high (1)
    TG_PGEC_SetHigh();
    </code>

*/
#define TG_PGEC_SetHigh()          ( LATBSET = (1 << 0) )
/**
  @Summary
    Sets the GPIO pin, RB0, low using LATBbits.LATB0.

  @Description
    Sets the GPIO pin, RB0, low using LATBbits.LATB0.

  @Preconditions
    The RB0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB0 low (0)
    TG_PGEC_SetLow();
    </code>

*/
#define TG_PGEC_SetLow()           ( LATBCLR = (1 << 0) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RB0, low or high using LATBbits.LATB0.

  @Preconditions
    The RB0 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RB0 to low.
    TG_PGEC_SetValue(false);
    </code>

*/
inline static void TG_PGEC_SetValue(bool value)
{
  if(value)
  {
    TG_PGEC_SetHigh();
  }
  else
  {
    TG_PGEC_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RB0, using LATBbits.LATB0.

  @Description
    Toggles the GPIO pin, RB0, using LATBbits.LATB0.

  @Preconditions
    The RB0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB0
    TG_PGEC_Toggle();
    </code>

*/
#define TG_PGEC_Toggle()           ( LATBINV = (1 << 0) )
/**
  @Summary
    Reads the value of the GPIO pin, RB0.

  @Description
    Reads the value of the GPIO pin, RB0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB0
    postValue = TG_PGEC_GetValue();
    </code>

*/
#define TG_PGEC_GetValue()         PORTBbits.RB0
/**
  @Summary
    Configures the GPIO pin, RB0, as an input.

  @Description
    Configures the GPIO pin, RB0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB0 as an input
    TG_PGEC_SetDigitalInput();
    </code>

*/
#define TG_PGEC_SetDigitalInput()   ( TRISBSET = (1 << 0) )
/**
  @Summary
    Configures the GPIO pin, RB0, as an output.

  @Description
    Configures the GPIO pin, RB0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB0 as an output
    TG_PGEC_SetDigitalOutput();
    </code>

*/
#define TG_PGEC_SetDigitalOutput()   ( TRISBCLR = (1 << 0) )
/**
  @Summary
    Sets the GPIO pin, RB1, high using LATBbits.LATB1.

  @Description
    Sets the GPIO pin, RB1, high using LATBbits.LATB1.

  @Preconditions
    The RB1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB1 high (1)
    TG_MCLR_SetHigh();
    </code>

*/
#define TG_MCLR_SetHigh()          ( LATBSET = (1 << 1) )
/**
  @Summary
    Sets the GPIO pin, RB1, low using LATBbits.LATB1.

  @Description
    Sets the GPIO pin, RB1, low using LATBbits.LATB1.

  @Preconditions
    The RB1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB1 low (0)
    TG_MCLR_SetLow();
    </code>

*/
#define TG_MCLR_SetLow()           ( LATBCLR = (1 << 1) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RB1, low or high using LATBbits.LATB1.

  @Preconditions
    The RB1 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RB1 to low.
    TG_MCLR_SetValue(false);
    </code>

*/
inline static void TG_MCLR_SetValue(bool value)
{
  if(value)
  {
    TG_MCLR_SetHigh();
  }
  else
  {
    TG_MCLR_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RB1, using LATBbits.LATB1.

  @Description
    Toggles the GPIO pin, RB1, using LATBbits.LATB1.

  @Preconditions
    The RB1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB1
    TG_MCLR_Toggle();
    </code>

*/
#define TG_MCLR_Toggle()           ( LATBINV = (1 << 1) )
/**
  @Summary
    Reads the value of the GPIO pin, RB1.

  @Description
    Reads the value of the GPIO pin, RB1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB1
    postValue = TG_MCLR_GetValue();
    </code>

*/
#define TG_MCLR_GetValue()         PORTBbits.RB1
/**
  @Summary
    Configures the GPIO pin, RB1, as an input.

  @Description
    Configures the GPIO pin, RB1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB1 as an input
    TG_MCLR_SetDigitalInput();
    </code>

*/
#define TG_MCLR_SetDigitalInput()   ( TRISBSET = (1 << 1) )
/**
  @Summary
    Configures the GPIO pin, RB1, as an output.

  @Description
    Configures the GPIO pin, RB1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB1 as an output
    TG_MCLR_SetDigitalOutput();
    </code>

*/
#define TG_MCLR_SetDigitalOutput()   ( TRISBCLR = (1 << 1) )
/**
  @Summary
    Sets the GPIO pin, RB2, high using LATBbits.LATB2.

  @Description
    Sets the GPIO pin, RB2, high using LATBbits.LATB2.

  @Preconditions
    The RB2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB2 high (1)
    TG_PGED_O_SetHigh();
    </code>

*/
#define TG_PGED_O_SetHigh()          ( LATBSET = (1 << 2) )
/**
  @Summary
    Sets the GPIO pin, RB2, low using LATBbits.LATB2.

  @Description
    Sets the GPIO pin, RB2, low using LATBbits.LATB2.

  @Preconditions
    The RB2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB2 low (0)
    TG_PGED_O_SetLow();
    </code>

*/
#define TG_PGED_O_SetLow()           ( LATBCLR = (1 << 2) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RB2, low or high using LATBbits.LATB2.

  @Preconditions
    The RB2 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RB2 to low.
    TG_PGED_O_SetValue(false);
    </code>

*/
inline static void TG_PGED_O_SetValue(bool value)
{
  if(value)
  {
    TG_PGED_O_SetHigh();
  }
  else
  {
    TG_PGED_O_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RB2, using LATBbits.LATB2.

  @Description
    Toggles the GPIO pin, RB2, using LATBbits.LATB2.

  @Preconditions
    The RB2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB2
    TG_PGED_O_Toggle();
    </code>

*/
#define TG_PGED_O_Toggle()           ( LATBINV = (1 << 2) )
/**
  @Summary
    Reads the value of the GPIO pin, RB2.

  @Description
    Reads the value of the GPIO pin, RB2.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB2
    postValue = TG_PGED_O_GetValue();
    </code>

*/
#define TG_PGED_O_GetValue()         PORTBbits.RB2
/**
  @Summary
    Configures the GPIO pin, RB2, as an input.

  @Description
    Configures the GPIO pin, RB2, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB2 as an input
    TG_PGED_O_SetDigitalInput();
    </code>

*/
#define TG_PGED_O_SetDigitalInput()   ( TRISBSET = (1 << 2) )
/**
  @Summary
    Configures the GPIO pin, RB2, as an output.

  @Description
    Configures the GPIO pin, RB2, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB2 as an output
    TG_PGED_O_SetDigitalOutput();
    </code>

*/
#define TG_PGED_O_SetDigitalOutput()   ( TRISBCLR = (1 << 2) )
/**
  @Summary
    Sets the GPIO pin, RB3, high using LATBbits.LATB3.

  @Description
    Sets the GPIO pin, RB3, high using LATBbits.LATB3.

  @Preconditions
    The RB3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB3 high (1)
    TG_PGED_I_SetHigh();
    </code>

*/
#define TG_PGED_I_SetHigh()          ( LATBSET = (1 << 3) )
/**
  @Summary
    Sets the GPIO pin, RB3, low using LATBbits.LATB3.

  @Description
    Sets the GPIO pin, RB3, low using LATBbits.LATB3.

  @Preconditions
    The RB3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB3 low (0)
    TG_PGED_I_SetLow();
    </code>

*/
#define TG_PGED_I_SetLow()           ( LATBCLR = (1 << 3) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RB3, low or high using LATBbits.LATB3.

  @Preconditions
    The RB3 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RB3 to low.
    TG_PGED_I_SetValue(false);
    </code>

*/
inline static void TG_PGED_I_SetValue(bool value)
{
  if(value)
  {
    TG_PGED_I_SetHigh();
  }
  else
  {
    TG_PGED_I_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RB3, using LATBbits.LATB3.

  @Description
    Toggles the GPIO pin, RB3, using LATBbits.LATB3.

  @Preconditions
    The RB3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB3
    TG_PGED_I_Toggle();
    </code>

*/
#define TG_PGED_I_Toggle()           ( LATBINV = (1 << 3) )
/**
  @Summary
    Reads the value of the GPIO pin, RB3.

  @Description
    Reads the value of the GPIO pin, RB3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB3
    postValue = TG_PGED_I_GetValue();
    </code>

*/
#define TG_PGED_I_GetValue()         PORTBbits.RB3
/**
  @Summary
    Configures the GPIO pin, RB3, as an input.

  @Description
    Configures the GPIO pin, RB3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB3 as an input
    TG_PGED_I_SetDigitalInput();
    </code>

*/
#define TG_PGED_I_SetDigitalInput()   ( TRISBSET = (1 << 3) )
/**
  @Summary
    Configures the GPIO pin, RB3, as an output.

  @Description
    Configures the GPIO pin, RB3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB3 as an output
    TG_PGED_I_SetDigitalOutput();
    </code>

*/
#define TG_PGED_I_SetDigitalOutput()   ( TRISBCLR = (1 << 3) )
/**
  @Summary
    Sets the GPIO pin, RC12, high using LATCbits.LATC12.

  @Description
    Sets the GPIO pin, RC12, high using LATCbits.LATC12.

  @Preconditions
    The RC12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC12 high (1)
    LED_USB_SetHigh();
    </code>

*/
#define LED_USB_SetHigh()          ( LATCSET = (1 << 12) )
/**
  @Summary
    Sets the GPIO pin, RC12, low using LATCbits.LATC12.

  @Description
    Sets the GPIO pin, RC12, low using LATCbits.LATC12.

  @Preconditions
    The RC12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC12 low (0)
    LED_USB_SetLow();
    </code>

*/
#define LED_USB_SetLow()           ( LATCCLR = (1 << 12) )

/**
  @Summary
    Sets a value to the GPIO pin.

  @Description
    Sets or Resets the GPIO pin, RC12, low or high using LATCbits.LATC12.

  @Preconditions
    The RC12 must be set to an output.

  @Returns
    None.

  @Param
    bool value; : value to be set to the GPIO pin.

  @Example
    <code>
    // Set RC12 to low.
    LED_USB_SetValue(false);
    </code>

*/
inline static void LED_USB_SetValue(bool value)
{
  if(value)
  {
    LED_USB_SetHigh();
  }
  else
  {
    LED_USB_SetLow();
  }
}

/**
  @Summary
    Toggles the GPIO pin, RC12, using LATCbits.LATC12.

  @Description
    Toggles the GPIO pin, RC12, using LATCbits.LATC12.

  @Preconditions
    The RC12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC12
    LED_USB_Toggle();
    </code>

*/
#define LED_USB_Toggle()           ( LATCINV = (1 << 12) )
/**
  @Summary
    Reads the value of the GPIO pin, RC12.

  @Description
    Reads the value of the GPIO pin, RC12.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC12
    postValue = LED_USB_GetValue();
    </code>

*/
#define LED_USB_GetValue()         PORTCbits.RC12
/**
  @Summary
    Configures the GPIO pin, RC12, as an input.

  @Description
    Configures the GPIO pin, RC12, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC12 as an input
    LED_USB_SetDigitalInput();
    </code>

*/
#define LED_USB_SetDigitalInput()   ( TRISCSET = (1 << 12) )
/**
  @Summary
    Configures the GPIO pin, RC12, as an output.

  @Description
    Configures the GPIO pin, RC12, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC12 as an output
    LED_USB_SetDigitalOutput();
    </code>

*/
#define LED_USB_SetDigitalOutput()   ( TRISCCLR = (1 << 12) )

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the PIC32MM0256GPM048
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize(void);

#endif
