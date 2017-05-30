
#include "private/data_multiplexer.h"

#define MAX_SIZE    (8)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uint8_t dm_compute_mask8(const uint8_t size) {
    uint8_t mask=0x01;
    register uint8_t s=size;
    
    if(!size) return 0;
    if(size>MAX_SIZE) return 0;
    
    while(--s) {
        mask = (mask<<1) | 0x01;
    }
    return mask;
}