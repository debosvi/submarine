
// #include <stdio.h>

#include "private/data_multiplexer.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uint8_t dm_compute_mask_shift8(const uint8_t lsb, const uint8_t size, const uint8_t index) {
    uint8_t mask=0;
    uint8_t b_sz=0;
    uint8_t b_pos=0;
    
    // fprintf(stderr, "%s: lsb(%d), size(%d), index(%d)\n", __PRETTY_FUNCTION__, lsb, size, index);         
    
    if(!size) goto _exit;
    if(index%DM_MODULO_SHIFT_BASIC) goto _exit;
    if(lsb<size-1) goto _exit;
    if(lsb<index) goto _exit;
    
    {
        uint8_t nmax=dm_get_nb_bytes(lsb+1);
        uint8_t nindex=dm_get_nb_bytes(index+1);
        uint8_t nmin=nmax;
        uint8_t sz=size;
        uint8_t rem=(lsb%DM_MODULO_SHIFT_BASIC)+1;
        
        if(rem>sz) rem=sz;                
        sz-=rem;
        
        while(sz) {
            nmin--;
            if(sz>DM_MODULO_SHIFT_BASIC) sz-=DM_MODULO_SHIFT_BASIC;
            else sz=0;
        }

        if(nindex<nmin) {
        }
        else if(nindex==nmax) {
            b_sz=lsb-index+1;
            b_pos=lsb+1-size-index;
            if(b_sz>size) b_sz=size;
            if(b_pos>=DM_MODULO_SHIFT_BASIC) b_pos=0;             
        }
        else if(nindex==nmin) {
            b_sz=lsb-DM_MODULO_SHIFT_BASIC*(nmax-1)+1;   // part of size of nmax byte
            b_sz=size-b_sz-DM_MODULO_SHIFT_BASIC*(nmax-nmin-1);   
            b_pos=DM_MODULO_SHIFT_BASIC-b_sz;
        }
        else {
            // mask=dm_compute_mask8(DM_MODULO_SHIFT_BASIC);
            mask=0xff;
        }
             
        if(b_sz) {
            mask=dm_compute_mask8(b_sz)<<b_pos;
        }
    }
    
    
_exit:
    return mask;
}
