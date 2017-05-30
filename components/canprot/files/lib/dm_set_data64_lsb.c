
#include "private/data_multiplexer.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int dm_set_data64_lsb(void* out, const uint16_t max, const uint8_t pos, const uint8_t size, const uint64_t in) {
    uint8_t *p=0;
    uint8_t fbyte=0;
    uint8_t fbit=0;
    uint64_t lin=0;
    uint64_t mask=0;
    unsigned char i=0;
    
    if(!out) return DM_ERR_NULL_PTR;
    if(max>DM_OUTPUT_MAX_BITS) return DM_ERR_BAD_PARAM;
    if(size>DM_INPUT_MAX_BITS) return DM_ERR_BAD_PARAM;
    if(pos>max) return DM_ERR_OVERLAP;
    {
        uint16_t t=(uint16_t)pos+size;
        if(t>max) return DM_ERR_OVERLAP;
    }
    
    fbyte=pos>>DM_MODULO_SHIFT_SHIFT;
    fbit=pos-(fbyte<<DM_MODULO_SHIFT_SHIFT);
    p=(uint8_t*)out + ((max>>DM_MODULO_SHIFT_SHIFT)-1) - fbyte;            
    
    while(1) {
        if(!i) {
            mask=dm_compute_mask64(size);
            lin=(in&mask)<<fbit;
            mask=mask<<fbit;
        }
        else {
            lin=in>>(DM_INPUT_MAX_BITS-fbit);
            mask=dm_compute_mask64(fbit);            
        }
        if(!mask) break;
    
        lin=lin&mask;        
        
        while(mask) {
            uint8_t v=lin;
            uint8_t m=mask;
            
            (*p)&=~m;
            (*p)|=v;
            lin=lin>>DM_MODULO_SHIFT_BASIC;
            mask=mask>>DM_MODULO_SHIFT_BASIC;
            p--;
        }
        if(i) break;        // loop 1 done, fully terminated
        if(pos+size<DM_INPUT_MAX_BITS) break;  // position + size not exceed 64 bits
        if(size<DM_INPUT_MAX_BITS) break;  // data not equal to 64 bits
        i++;
    }
    
    return DM_ERR_NO_ERROR;
}