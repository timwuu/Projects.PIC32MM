#include "mcc.h"
#include "ejtag.h"

//from <Run Test/Idle>
//Xfer Data and goto <Run Test/Idle>
uint8_t xferData8b( uint8_t data8) 
{

    uint32_t data[2];
    
    //Cmd.LSB first
    // TDI:0000.cccc.cccc.0000
    // TMS:0100.0000.0001.1000
    data[0]= 0x04000000; 
    data[1]= 0x00044000; //JTAG Goto <Run Test/Idle> State

    switch(data8)
    {
        case MCHP_STATUS:
            break;
        case MCHP_ASSERT_RST:
            data[0] |= 0x00008000;
            data[1] |= 0x80880000;
            break;
        case MCHP_DE_ASSERT_RST:
            data[0] |= 0x00000000;
            data[1] |= 0x80880000;
            break;
        case MCHP_ERASE:
            data[0] |= 0x00000088;
            data[1] |= 0x88880000;
            break;
        default:
            return 0x00;
    }
    
    
    uint8_t result;
    uint8_t _bit;
    uint32_t _mask;
    uint32_t i,j;
    
    SPI2CONbits.ON = 0;

    SPI2CONbits.CKE = 0;
     
    TG_PGED_O_SetLow(); //SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow();    
    SPI2CONbits.ON = 1;
    
    data[0] = SPI2_Exchange32bit( data[0]);
    data[1] = SPI2_Exchange32bit( data[1]);
    //SPI2_Exchange( (uint8_t*)&data[0], (uint8_t*)&data[0] );
    //SPI2_Exchange( (uint8_t*)&data[1], (uint8_t*)&data[1] );
    
    SPI2CONbits.ON = 0;
    
    result=0x00000000;
    _bit  =0x00000001;
    _mask =0x00020000;

    for( i=0,j=0; i<8; i++)
    {
        if( data[j] & _mask) result |= _bit;
        
        _mask = _mask >> 4;
        _bit  = _bit << 1;
        if(_mask==0x0)
        {
            _mask=0x20000000;
            j++;
        }
    }

    return result;
    
}

//from <Run Test/Idle>
//Xfer Data and goto <Run Test/Idle>
uint32_t xferData32b( uint32_t data32) 
{

    uint32_t data[5];
    
    //Cmd.LSB first
    // TDI:0000.cccc:cccc.cccc:cccc.cccc:cccc.cccc:cccc.0000
    // TMS:0100.0000:0000.0000.0000.0000:0000.0000:0001.1000
    // TDO:000d.dddd:dddd.dddd.dddd.dddd:dddd.dddd:ddd0.0000
    data[0]= 0x04000000; //JTAG Goto <Run Test/Idle> State
    data[1]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[2]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[3]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[4]= 0x00044000; //JTAG Goto <Run Test/Idle> State
    //data[5]= 0x00000000; //JTAG Goto <Run Test/Idle> State

    uint32_t result;
    uint32_t _bit;
    uint32_t _mask;
    uint32_t i,j;

    _bit  =0x00000001;
    _mask =0x00008000;

    for( i=0,j=0; i<32; i++)
    {
        if( data32 & _bit) data[j] |= _mask;
        
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
     
    TG_PGED_O_SetLow();//SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow();    
    SPI2CONbits.ON = 1;
    
    data[0] = SPI2_Exchange32bit( data[0]);
    data[1] = SPI2_Exchange32bit( data[1]);
    data[2] = SPI2_Exchange32bit( data[2]);
    data[3] = SPI2_Exchange32bit( data[3]);
    data[4] = SPI2_Exchange32bit( data[4]);

    //SPI2_Exchange( (uint8_t*)&data[0], (uint8_t*)&data[0] );
    //SPI2_Exchange( (uint8_t*)&data[1], (uint8_t*)&data[1] );
    //SPI2_Exchange( (uint8_t*)&data[2], (uint8_t*)&data[2] );
    //SPI2_Exchange( (uint8_t*)&data[3], (uint8_t*)&data[3] );
    //SPI2_Exchange( (uint8_t*)&data[4], (uint8_t*)&data[4] );
    //SPI2_Exchange( (uint8_t*)&data[5], (uint8_t*)&data[5] );
    
    SPI2CONbits.ON = 0;
    
    result=0x00000000;
    _bit  =0x00000001;
    _mask =0x00020000;

    for( i=0,j=0; i<32; i++)
    {
        if( data[j] & _mask) result |= _bit;
        
        _mask = _mask >> 4;
        _bit  = _bit << 1;
        if(_mask==0x0)
        {
            _mask=0x20000000;
            j++;
        }
    }
    
    return result;
    
}

//from <Run Test/Idle>
//prerequisite ETAP_FASTDATA
//Xfer Fast Data and goto <Run Test/Idle>
uint32_t P32XferFastData32b( uint32_t data32) 
{

    uint32_t data[5];
    
    // Cmd.LSB first, p:PrAcc
    // TDI:0000.cccc:cccc.cccc:cccc.cccc:cccc.cccc:cccc.0000
    // TMS:1000.0000:0000.0000.0000.0000:0000.0000:0001.1000
    // TDO:00pd.dddd:dddd.dddd.dddd.dddd:dddd.dddd:ddd0.0000
    data[0]= 0x40000000; //JTAG Goto <Run Test/Idle> State
    data[1]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[2]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[3]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[4]= 0x00044000; //JTAG Goto <Run Test/Idle> State
    //data[5]= 0x00000000; //JTAG Goto <Run Test/Idle> State

    uint32_t result;
    uint32_t _bit;
    uint32_t _mask;
    uint32_t i,j;

    _bit  =0x00000001;
    _mask =0x00008000;

    for( i=0,j=0; i<32; i++)
    {
        if( data32 & _bit) data[j] |= _mask;
        
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
     
    //SDO1_SetLow();
    //SCK1_SetLow();    

    TG_PGED_O_SetLow();//SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow();    

    SPI2CONbits.ON = 1;

    data[0] = SPI2_Exchange32bit( data[0]);
    data[1] = SPI2_Exchange32bit( data[1]);
    data[2] = SPI2_Exchange32bit( data[2]);
    data[3] = SPI2_Exchange32bit( data[3]);
    data[4] = SPI2_Exchange32bit( data[4]);
    
    //SPI2_Exchange( (uint8_t*)&data[0], (uint8_t*)&data[0] );
    //SPI2_Exchange( (uint8_t*)&data[1], (uint8_t*)&data[1] );
    //SPI2_Exchange( (uint8_t*)&data[2], (uint8_t*)&data[2] );
    //SPI2_Exchange( (uint8_t*)&data[3], (uint8_t*)&data[3] );
    //SPI2_Exchange( (uint8_t*)&data[4], (uint8_t*)&data[4] );
    //SPI2_Exchange( (uint8_t*)&data[5], (uint8_t*)&data[5] );
    
    SPI2CONbits.ON = 0;

    //check PrAcc bit
    if( (data[0] & 0x00200000)==0 )
    {
        sysError(0xE0E0E0E0);
        return 0x00;
    }
    
    result=0x00000000;
    _bit  =0x00000001;
    _mask =0x00020000;

    for( i=0,j=0; i<32; i++)
    {
        if( data[j] & _mask) result |= _bit;
        
        _mask = _mask >> 4;
        _bit  = _bit << 1;
        if(_mask==0x0)
        {
            _mask=0x20000000;
            j++;
        }
    }
    
    return result;
    
}

//from <Run Test/Idle>
//Xfer Data and goto <Run Test/Idle>
void vXferData8b( uint8_t data8) 
{

    uint32_t data[2];
    
    //Cmd.LSB first
    // TDI:0000.cccc.cccc.0000
    // TMS:0100.0000.0001.1000
    data[0]= 0x04000000; 
    data[1]= 0x00044000; //JTAG Goto <Run Test/Idle> State

    switch(data8)
    {
        case MCHP_STATUS:
            break;
        case MCHP_ASSERT_RST:
            data[0] |= 0x00008000;
            data[1] |= 0x80880000;
            break;
        case MCHP_DE_ASSERT_RST:
            data[0] |= 0x00000000;
            data[1] |= 0x80880000;
            break;
        case MCHP_ERASE:
            data[0] |= 0x00000088;
            data[1] |= 0x88880000;
            break;
        default:
            return;
    }
    
    SPI2CONbits.ON = 0;

    SPI2CONbits.CKE = 0;

    TG_PGED_O_SetLow();//SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow();    
    SPI2CONbits.ON = 1;
    
    data[0] = SPI2_Exchange32bit( data[0]);
    data[1] = SPI2_Exchange32bit( data[1]);
    
    //SPI2_Exchange( (uint8_t*)&data[0], (uint8_t*)&data[0] );
    //SPI2_Exchange( (uint8_t*)&data[1], (uint8_t*)&data[1] );
    
    SPI2CONbits.ON = 0;

    return;
    
}

//from <Run Test/Idle>
//Xfer Data and goto <Run Test/Idle>
void vXferData32b( uint32_t data32) 
{

    uint32_t data[5];
    
    //Cmd.LSB first
    // TDI:0000.cccc:cccc.cccc:cccc.cccc:cccc.cccc:cccc.0000
    // TMS:0100.0000:0000.0000.0000.0000:0000.0000:0001.1000
    // TDO:000d.dddd:dddd.dddd.dddd.dddd:dddd.dddd:ddd0.0000
    data[0]= 0x04000000; //JTAG Goto <Run Test/Idle> State
    data[1]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[2]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[3]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[4]= 0x00044000; //JTAG Goto <Run Test/Idle> State
    //data[5]= 0x00000000; //JTAG Goto <Run Test/Idle> State

    uint32_t _bit;
    uint32_t _mask;
    uint32_t i,j;

    _bit  =0x00000001;
    _mask =0x00008000;

    for( i=0,j=0; i<32; i++)
    {
        if( data32 & _bit) data[j] |= _mask;
        
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
     
    TG_PGED_O_SetLow();//SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow();    
    SPI2CONbits.ON = 1;
    
    data[0] = SPI2_Exchange32bit( data[0]);
    data[1] = SPI2_Exchange32bit( data[1]);
    data[2] = SPI2_Exchange32bit( data[2]);
    data[3] = SPI2_Exchange32bit( data[3]);
    data[4] = SPI2_Exchange32bit( data[4]);

    //SPI2_Exchange( (uint8_t*)&data[0], (uint8_t*)&data[0] );
    //SPI2_Exchange( (uint8_t*)&data[1], (uint8_t*)&data[1] );
    //SPI2_Exchange( (uint8_t*)&data[2], (uint8_t*)&data[2] );
    //SPI2_Exchange( (uint8_t*)&data[3], (uint8_t*)&data[3] );
    //SPI2_Exchange( (uint8_t*)&data[4], (uint8_t*)&data[4] );
    //SPI2_Exchange( (uint8_t*)&data[5], (uint8_t*)&data[5] );
    
    SPI2CONbits.ON = 0;
    
    return;
    
}

//from <Run Test/Idle>
//prerequisite ETAP_FASTDATA
//Xfer Fast Data and goto <Run Test/Idle>
void vP32XferFastData32b( uint32_t data32) 
{

    uint32_t data[5];
    
    // Cmd.LSB first, p:PrAcc
    // TDI:0000.cccc:cccc.cccc:cccc.cccc:cccc.cccc:cccc.0000
    // TMS:1000.0000:0000.0000.0000.0000:0000.0000:0001.1000
    // TDO:00pd.dddd:dddd.dddd.dddd.dddd:dddd.dddd:ddd0.0000
    data[0]= 0x40000000; //JTAG Goto <Run Test/Idle> State
    data[1]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[2]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[3]= 0x00000000; //JTAG Goto <Run Test/Idle> State
    data[4]= 0x00044000; //JTAG Goto <Run Test/Idle> State
    //data[5]= 0x00000000; //JTAG Goto <Run Test/Idle> State

    uint32_t _bit;
    uint32_t _mask;
    uint32_t i,j;

    _bit  =0x00000001;
    _mask =0x00008000;

    for( i=0,j=0; i<32; i++)
    {
        if( data32 & _bit) data[j] |= _mask;
        
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
     
    TG_PGED_O_SetLow();//SDO1_SetLow();
    TG_PGEC_SetLow(); //SCK1_SetLow();    
    
    SPI2CONbits.ON = 1;
    
    data[0] = SPI2_Exchange32bit( data[0]);
    data[1] = SPI2_Exchange32bit( data[1]);
    data[2] = SPI2_Exchange32bit( data[2]);
    data[3] = SPI2_Exchange32bit( data[3]);
    data[4] = SPI2_Exchange32bit( data[4]);

    //SPI2_Exchange( (uint8_t*)&data[0], (uint8_t*)&data[0] );
    //SPI2_Exchange( (uint8_t*)&data[1], (uint8_t*)&data[1] );
    //SPI2_Exchange( (uint8_t*)&data[2], (uint8_t*)&data[2] );
    //SPI2_Exchange( (uint8_t*)&data[3], (uint8_t*)&data[3] );
    //SPI2_Exchange( (uint8_t*)&data[4], (uint8_t*)&data[4] );
    //SPI2_Exchange( (uint8_t*)&data[5], (uint8_t*)&data[5] );
    
    SPI2CONbits.ON = 0;

    //check PrAcc bit
    if( (data[0] & 0x00200000)==0 )
    {
        sysError(0xE0E0E0E0);
        return;
    }   
   
    return;
    
}

void P32XferInstruction( uint32_t instruction)
{
    uint32_t praccbyte;
    uint32_t timeout=2550;
    
    sendCommand5b(ETAP_CONTROL);
    do
    {   //timijk ?0x0004D000 P32XferData32(0x00, 0x04, 0xD0, 0x00, 0);
        praccbyte = xferData32b(0x0004D000);  
    } while (((praccbyte & 0x00040000) == 0) && --timeout);
    
    if (timeout==0) 
    { 
        sysError(praccbyte);
        return;
    }
    
    sendCommand5b(ETAP_DATA);          // ETAP_DATA
    // actual instruction:
    vXferData32b( instruction);
    
    sendCommand5b(ETAP_CONTROL);
    vXferData32b( 0x0000C000);

    //while( UART2_TransmitBufferIsFull());    
    //UART2_Write('o');

}