/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/** INCLUDES *******************************************************/
//#include "system.h"

#include "app_device_cdc_basic.h"
//#include "app_led_usb_status.h"

#include "mcc.h"
#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"


void sysError( uint32_t);

void sendCommand5b( uint8_t cmd);


/********************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *******************************************************************/
void main(void)
{
    //SYSTEM_Initialize(SYSTEM_STATE_USB_START);

    SYSTEM_Initialize();
    
    //USBDeviceInit();
    //USBDeviceAttach();
    
    while(1)
    {
        //SYSTEM_Tasks();

        #if defined(USB_POLLING)
            // Interrupt or polling method.  If using polling, must call
            // this function periodically.  This function will take care
            // of processing and responding to SETUP transactions
            // (such as during the enumeration process when you first
            // plug in).  USB hosts require that USB devices should accept
            // and process SETUP packets in a timely fashion.  Therefore,
            // when using polling, this function should be called
            // regularly (such as once every 1.8ms or faster** [see
            // inline code comments in usb_device.c for explanation when
            // "or faster" applies])  In most cases, the USBDeviceTasks()
            // function does not take very long to execute (ex: <100
            // instruction cycles) before it returns.
            USBDeviceTasks();
        #endif

        //Application specific tasks
        APP_DeviceCDCBasicDemoTasks();

    }//end while
}//end main

void sendCommand5b( uint8_t cmd) 
{

    uint32_t data[2];
            
    //Cmd.LSB first
    // TDI:0000.cccc.c000.0000
    // TMS:1100.0000.1100.0000
    data[0]= 0x44000000; //JTAG Goto <Run Test/Idle> State
    data[1]= 0x44000000; //JTAG Goto <Run Test/Idle> State
    
    uint8_t _bit;
    uint32_t _mask;
    uint32_t i,j;

    _bit  =0x01;
    _mask =0x00008000;

    for( i=0,j=0; i<5; i++)
    {
        if( cmd & _bit) data[j] |= _mask;
        
        _mask = _mask >> 4;
        _bit  = _bit << 1;
        if(_mask==0x0)
        {
            _mask=0x80000000;
            j++;
        }
    }

    SPI2CONbits.ON = 0;

    SPI2CONbits.CKE = 0;
      
    TG_PGED_O_SetLow(); //SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow(); 
    SPI2CONbits.ON = 1;
    
    data[0] = SPI2_Exchange32bit( data[0]);
    data[1] = SPI2_Exchange32bit( data[1]);
    
    SPI2CONbits.ON = 0;
    
}

void sysError( uint32_t dat)
{
    
}
/*******************************************************************************
 End of File
*/
