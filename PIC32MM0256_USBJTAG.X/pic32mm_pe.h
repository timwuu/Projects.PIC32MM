/* 
 * File:   pic32mm_pe.h
 * Author: Tim
 *
 * Created on February 17, 2017, 12:36 PM
 */

#ifndef PIC32MM_PE_H
#define	PIC32MM_PE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define PE_LOADER_SIZE 30 //22+8
#define PIC32MM_PE_SIZE 553

    extern uint16_t pe_Loader[];
    extern uint32_t pic32_PE_Version_MM;
    extern uint32_t PIC32_PE_MM[];

#ifdef	__cplusplus
}
#endif

#endif	/* PIC32MM_PE_H */

