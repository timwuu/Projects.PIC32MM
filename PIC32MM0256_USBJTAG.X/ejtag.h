/* 
 * File:   ejtag.h
 * Author: Tim
 *
 * Created on February 24, 2017, 12:22 PM
 */

#ifndef EJTAG_H
#define	EJTAG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define MTAP_IDCODE  0x01
#define MTAP_SW_MTAP 0x04
#define MTAP_SW_ETAP 0x05
#define MTAP_COMMAND 0x07

#define MCHP_STATUS        0x00
#define MCHP_ASSERT_RST    0xD1
#define MCHP_DE_ASSERT_RST 0xD0
#define MCHP_ERASE         0xFC

#define ETAP_ADDRESS   0x08
#define ETAP_DATA      0x09
#define ETAP_CONTROL   0x0A
#define ETAP_EJTAGBOOT 0x0C
#define ETAP_FASTDATA  0x0E
    
uint8_t xferData8b( uint8_t data8);
uint32_t xferData32b( uint32_t data32);

void vXferData8b( uint8_t data8);
void vXerData32b( uint32_t data32);
void vP32XferFastData32b( uint32_t data32);

void P32XferInstruction( uint32_t instruction);
uint32_t P32XferFastData32b( uint32_t data32);


#ifdef	__cplusplus
}
#endif

#endif	/* EJTAG_H */

