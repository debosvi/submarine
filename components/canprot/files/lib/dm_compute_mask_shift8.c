
#include "private/data_multiplexer.h"

#define MODULO_SHIFT_BASIC  (8)
#define MODULO_SHIFT_SHIFT  (3)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static uint8_t get_nb_bytes(const uint8_t nb) {
    uint8_t _ret=(nb>>MODULO_SHIFT_SHIFT);
    if((nb+1)-(MODULO_SHIFT_BASIC*_ret)) _ret++;
    return _ret;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uint8_t dm_compute_mask_shift8(const uint8_t lsb, const uint8_t size, const uint8_t index) {
    uint8_t mask=0;
    uint8_t b_sz=0;
    uint8_t b_pos=0;
    

    if(!size) goto _exit;
    if(index%MODULO_SHIFT_BASIC) goto _exit;
    if(lsb<size-1) goto _exit;
    if(lsb<index) goto _exit;
    
    {
        uint8_t nmax=get_nb_bytes(lsb);
        uint8_t nindex=get_nb_bytes(index);
        uint8_t nmin=nmax;
        uint8_t sz=size;
        uint8_t rem=(lsb%MODULO_SHIFT_BASIC)+1;
        
        if(rem>sz) rem=sz;                
        sz-=rem;
        
        while(sz) {
            nmin--;
            if(sz>MODULO_SHIFT_BASIC) sz-=MODULO_SHIFT_BASIC;
            else sz=0;
        }

        if(nindex<nmin) {
        }
        else if(nindex==nmax) {
            b_sz=lsb-index+1;
            b_pos=lsb+1-size-index;
            if(b_sz>size) b_sz=size;
            if(b_pos>=MODULO_SHIFT_BASIC) b_pos=0;             
        }
        else if(nindex==nmin) {
            b_sz=lsb-MODULO_SHIFT_BASIC*(nmax-1)+1;   // part of size of nmax byte
            b_sz=size-b_sz-MODULO_SHIFT_BASIC*(nmax-nmin-1);   
            b_pos=MODULO_SHIFT_BASIC-b_sz;
        }
        else {
            // mask=dm_compute_mask8(MODULO_SHIFT_BASIC);
            mask=0xff;
        }
             
        if(b_sz) {
            mask=dm_compute_mask8(b_sz)<<b_pos;
        }
    }
    
    
_exit:
    return mask;
}
