
// #include <stdio.h>

#include "private/data_multiplexer.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int dm_set_data8_lsb(void* out, const uint16_t max, const uint8_t pos, const uint8_t size, const uint8_t* const in) {
    uint8_t *p=0;
    uint8_t fbyte=0;
    uint8_t lbyte=0;
    uint8_t fbit=0;
    uint8_t i=0, j=0;
    uint8_t omax=0, imax=0;    
    
    // fprintf(stderr, "%s: max(%d), pos(%d), size(%d)\n", __PRETTY_FUNCTION__, max, pos, size);  
    
    if(!out) return DM_ERR_NULL_PTR;
    if(max>DM_OUTPUT_MAX_BITS) return DM_ERR_BAD_PARAM;
    if(size>DM_INPUT_MAX_BITS) return DM_ERR_BAD_PARAM;
    if(pos>max) return DM_ERR_OVERLAP;
    {
        uint16_t t=(uint16_t)pos+size;
        if(t>max) return DM_ERR_OVERLAP;
    }
    
    omax=dm_get_nb_bytes(max);
    imax=dm_get_nb_bytes(size);
    fbyte=pos>>DM_MODULO_SHIFT_SHIFT;
    fbit=pos-(fbyte<<DM_MODULO_SHIFT_SHIFT);

    {
        int8_t sz=0;
        sz=size-fbit;
        lbyte=fbyte;
        while(sz>0) {
            sz-=DM_MODULO_SHIFT_BASIC;
            lbyte++;        
        }
    }
    
    // fprintf(stderr, "%s: imax(%d), omax(%d), fbyte(%d), fbit(%d), lbyte(%d)\n", __PRETTY_FUNCTION__, imax, omax, fbyte, fbit, lbyte);  
    
    p=(uint8_t*)out;          
    for(j=0; j<omax; j++) {
        uint8_t mask=dm_compute_mask_shift8(pos+size-1, size, DM_MODULO_SHIFT_BASIC*(omax-1-j));
        p[j]&=~mask;
    }
    
    i=0;
    j=fbyte;
    p=(uint8_t*)out;
    while(1) {
        uint8_t v1=0, v2=0;
        int i1=-1, i2=-1;        
                
        if(i<imax) {
            i1=imax-i-1;
            v1=in[i1]<<fbit;
        }
        if(i) {
            i2=imax-i;
            v2=in[i2]>>(DM_MODULO_SHIFT_BASIC-fbit);
        }
        
        // fprintf(stderr, "%s: i(%d), j(%d), i1(%d), i2(%d), v1(0x%02x), v2(0x%02x)\n", __PRETTY_FUNCTION__, i, j, i1, i2, v1, v2);  
        // fprintf(stderr, "%s: value(0x%02x)\n", __PRETTY_FUNCTION__, v1|v2);  
        p[omax-j-1] |= (v1|v2);
        if(j==lbyte) break;
        j++;
        i++;
    }   
    
    return DM_ERR_NO_ERROR;
}