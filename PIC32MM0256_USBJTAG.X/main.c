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

#include <stdint.h>

#include "app_device_cdc_basic.h"
//#include "app_led_usb_status.h"

#include "mcc.h"
#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

#include "pic32mm_pe.h"
#include "ejtag.h"

static uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];

void sysError( uint32_t);

void sendCommand5b( uint8_t cmd);

void UART_PutUint8( uint8_t data);
void UART_PutUint32( uint32_t data);
bool checkDeviceStatus( void);

uint32_t readPEVersion();

bool eraseDevice();
void enterSerialExecution();
void downloadPE();

void UART_PutUint8( uint8_t data);
void UART_PutUint32( uint32_t data);
bool checkDeviceStatus( void);

uint32_t readPEVersion();

void processCmd( uint8_t cmd);


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

void setTestLogicResetMode()
{

    uint32_t data= 0x44444444; //JTAG Goto <Test Logic Reset> State

    SPI2CONbits.ON = 0;

    SPI2CONbits.CKE = 0;
      
    TG_PGED_O_SetLow(); //SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow(); 
    SPI2CONbits.ON = 1;
    
    data = SPI2_Exchange32bit( data);

    
    SPI2CONbits.ON = 0;
    
}

void setRunTestIdleMode()
{

    uint32_t data= 0x44444000; //JTAG Goto <Run Test/Idle> State

    SPI2CONbits.ON = 0;

    SPI2CONbits.CKE = 0;
       
    TG_PGED_O_SetLow(); //SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow(); 
    SPI2CONbits.ON = 1;
    
    data = SPI2_Exchange32bit( data);

    SPI2CONbits.ON = 0;    
}


void enterICSP()
{
    uint32_t data= 0x4D434850; //ICSP Entry Code

    SPI2CONbits.ON = 0;

    SPI2CONbits.CKE = 1;
    
    
    TG_PGED_O_SetLow(); //SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow(); 
    SPI2CONbits.ON = 1;
   
    TG_MCLR_SetLow();     //MCLR_LOW P6(100ns)
    TG_MCLR_SetLow();
    TG_MCLR_SetLow();    
    TG_MCLR_SetHigh();    //MCLR_HIGH < P14+P20 (501us)
    TG_MCLR_SetHigh();    
    TG_MCLR_SetLow();     //MCLR_LOW P18(40ns)
    
    data = SPI2_Exchange32bit( data);
    
    //Delay P19(40ns)
    TG_MCLR_SetHigh();    //MCLR_HIGH P7(500ns)
    
    SPI2CONbits.ON = 0;
    TG_PGED_O_SetLow(); //SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow(); 

    UART_PutUint32( data);
    
}

void exitICSP()
{

    uint32_t data= 0x44444444; //JTAG Goto <Test Logic Reset> State

    SPI2CONbits.ON = 0;

    SPI2CONbits.CKE = 0;
     
    TG_PGED_O_SetLow(); //SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow(); 
    SPI2CONbits.ON = 1;
    
    data = SPI2_Exchange32bit( data);
    
    //TG_MCLR_SetHigh();   //MCLR_HIGH P16(0ns)
    TG_MCLR_SetLow();    // < MCLR_LOW P17(100ns)
    TG_MCLR_SetLow();    //

    SPI2CONbits.ON = 0;
    TG_PGED_O_SetLow(); //SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow(); 

    //Send a pulse SCK1.H    
    TG_PGEC_SetHigh();
    TG_PGEC_SetHigh(); 
    TG_PGEC_SetLow(); //SCK1_SetLow(); 

    
}

bool eraseDevice()
{
    uint8_t status, cnt;
    uint32_t i;

    sendCommand5b( MTAP_SW_MTAP);
    sendCommand5b( MTAP_COMMAND);
     
    xferData8b( MCHP_ERASE);
    xferData8b( MCHP_DE_ASSERT_RST);
    
    cnt=0xFF;
    
    while(cnt--)
    {
      status= xferData8b( MCHP_STATUS);
     
      // CPS<7>,NVMERR<5>,CFGRDY<3>,FCBUSY<2>,DEVRST<0>
      // break: CFGRDY==1 and FCBUSY==0
      if( (status & 0x08) && ((~status) & 0x04) ) break;
      
      //delay 10 ms
      for( i=0; i<100; i++);
    }
    
    UART_PutUint8(status);

    //FIXME: UART2_Write('#');
    
    UART_PutUint8(cnt);
    
    return ((cnt==0)?false:true);
}

void processCmd( uint8_t cmd)
{
    uint32_t i;

    writeBuffer[0]=cmd;

    switch (cmd) {
        case 'P': //Load PE
            enterICSP();
            
            if(checkDeviceStatus())
            {
                //FIXME: LATBSET = _LATB_LATB5_MASK;

                enterSerialExecution();
                
                downloadPE();
            
                readPEVersion();
                
                //FIXME: while(UART2_ReceiveBufferIsEmpty());
                //FIXME: UART2_Read();
             
                //FIXME: LATBCLR = _LATB_LATB5_MASK;

            }
            
            
            exitICSP();
            
            break;
            
        case 'D': //ID CODE
            enterICSP();

            setRunTestIdleMode();

            sendCommand5b(MTAP_IDCODE);
            UART_PutUint32(xferData32b(0x00));

            exitICSP();
            break;
            
        case 'S': //Status
            enterICSP();

            for( i=0; i<1000; i++);
            
            checkDeviceStatus();

            exitICSP();
            
            break;

        case 'I': //Enter ICSP Mode
            enterICSP();
            putUSBUSART(writeBuffer,9);
            break;

        case 'E': //Exit ICSP Mode
            exitICSP();
            putUSBUSART(writeBuffer,1);
            break;

        case 'Q':
            setRunTestIdleMode();
            sendCommand5b( MTAP_SW_MTAP);
            sendCommand5b( MTAP_COMMAND);
            xferData8b( MCHP_DE_ASSERT_RST);

            putUSBUSART(writeBuffer,1);
            break;

        case 'R':
            setRunTestIdleMode();
            sendCommand5b( MTAP_SW_MTAP);
            sendCommand5b( MTAP_COMMAND);
            xferData8b( MCHP_ASSERT_RST);

            putUSBUSART(writeBuffer,1);
            break;
            
        case 'H':
            TG_MCLR_SetHigh();
            putUSBUSART(writeBuffer,1);
            break;

        case 'L':
            TG_MCLR_SetLow();
            putUSBUSART(writeBuffer,1);
            break;

        default:
            break;
    }

}

void UART_PutUint32( uint32_t data)
{
    int32_t i;
    uint32_t tmp;
    uint8_t c, str[8];   
    
    tmp=data;
    
    for( i=7; i>=0; i--)
    {
        c= (uint8_t)(tmp & 0x0F);
        
        if( c<0x0A) c+= '0';
        else c+='A'-10;
        
        str[i]=c;
        
        tmp = tmp>>4;
    }
    
    for( i=0; i<=7; i++)
    {
        //FIXME: while( UART2_TransmitBufferIsFull());
        //FIXME: UART2_Write(str[i]);
        writeBuffer[i+1]= str[i];
    }
    
}

void UART_PutUint8( uint8_t data)
{
    int32_t i;
    uint8_t tmp;
    uint8_t c, str[2];   
    
    tmp=data;
    
    for( i=1; i>=0; i--)
    {
        c= (uint8_t)(tmp & 0x0F);
        
        if( c<0x0A) c+= '0';
        else c+='A'-10;
        
        str[i]=c;
        
        tmp = tmp>>4;
    }
    
    for( i=0; i<=1; i++)
    {
        //FIXME: while( UART2_TransmitBufferIsFull());
        //FIXME: UART2_Write(str[i]);
    }
    
}

bool checkDeviceStatus()
{
    uint8_t status, cnt;
    uint32_t i;
    
    setRunTestIdleMode();
    sendCommand5b( MTAP_SW_MTAP);
    sendCommand5b( MTAP_COMMAND);
    
    cnt=0xFF;
    
    while(cnt--)
    {
      status= xferData8b( MCHP_STATUS);
     
      // CPS<7>,NVMERR<5>,CFGRDY<3>,FCBUSY<2>,DEVRST<0>
      // break: CFGRDY==1 and FCBUSY==0
      if( (status & 0x08) && ((~status) & 0x04) ) break;
      
      for( i=0; i<100; i++);
    }
    
    UART_PutUint8(status);

    //FIXME: UART2_Write('#');
    
    UART_PutUint8(cnt);
    
    return ((cnt==0)?false:true);
    
}

// assuming already checking device status
// and ready to program??
void enterSerialExecution()
{
    uint32_t i;
    
    sendCommand5b( MTAP_SW_MTAP);
    sendCommand5b( MTAP_COMMAND);
    xferData8b( MCHP_ASSERT_RST);
      
    sendCommand5b( MTAP_SW_ETAP);

    setRunTestIdleMode();

    sendCommand5b( ETAP_EJTAGBOOT);
    
    //checkDeviceStatus();

    sendCommand5b( MTAP_SW_MTAP);
    sendCommand5b( MTAP_COMMAND);  
    xferData8b( MCHP_DE_ASSERT_RST);

    //checkDeviceStatus();
    
}

void downloadPE()
{
    uint32_t i;
    
    sendCommand5b( MTAP_SW_ETAP);   

    setRunTestIdleMode();
    
    // step 0. Turn On LED at RB5
    P32XferInstruction( 0x0C00ED20);
    P32XferInstruction( 0xBF8041A3);
    P32XferInstruction( 0x2734F843);  //LATBCLR

    P32XferInstruction( 0xBF8041A3);
    P32XferInstruction( 0x2714F843);  //TRISBCLR
    
    //P32XferInstruction( 0xBF8041A3);
    //P32XferInstruction( 0x2738F843);  //LATBSET
    
    // step 1. setup the PIC32MM RAM A000.0200
    P32XferInstruction( 0xA00041A4);
    P32XferInstruction( 0x02005084);
    
    // step 2. download the PE loader
    for( i=0; i<PE_LOADER_SIZE; i+=2)
    {
        P32XferInstruction( (pe_Loader[i+1] << 16) | 0x41A6);
        P32XferInstruction( (pe_Loader[i] << 16) | 0x50c6);
        P32XferInstruction( 0x6e42eb40);
    }
    
    // step 3. jump to PE Loader A000.0201
    P32XferInstruction( 0xa00041b9);
    P32XferInstruction( 0x02015339);
    P32XferInstruction( 0x0c004599);
    P32XferInstruction( 0x0c000c00);  //nop; nop; required
    P32XferInstruction( 0x0c000c00);  //nop; nop; required
    
    // step 4.A
    sendCommand5b( MTAP_SW_ETAP);   
    setRunTestIdleMode();

    sendCommand5b( ETAP_FASTDATA);
    vP32XferFastData32b( 0xA0000300);
    vP32XferFastData32b( PIC32MM_PE_SIZE);
    
    
    // step 4.B
    for( i=0; i<PIC32MM_PE_SIZE; i++)
        vP32XferFastData32b(PIC32_PE_MM[i]);
    
    // step 5. Jump to PE
    vP32XferFastData32b( 0x00000000);
    vP32XferFastData32b( 0xDEAD0000);
    
    
}



uint32_t readPEVersion()
{
    uint32_t ver=0x0000;
    
    sendCommand5b(ETAP_FASTDATA);
    
    P32XferFastData32b(0x00070000);
    
    //wait??
    
    ver=P32XferFastData32b(0x00000000);
    
    //FIXME: while( UART2_TransmitBufferIsFull());    
    //FIXME: UART2_Write('v');
    UART_PutUint32(ver);

    return ver;
}

void sysError( uint32_t dat)
{
    
}
/*******************************************************************************
 End of File
*/
