
#include <stdio.h>

#include "private/data_multiplexer.h"

#define MODULO_SHIFT_BASIC  (8)
#define MODULO_SHIFT_SHIFT  (3)

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
    
    fprintf(stderr, "\n%s: lsb(%d), size(%d), index(%d)\n", __PRETTY_FUNCTION__, lsb, size, index);         

    if(!size) {
        fprintf(stderr, "%s: no size\n", __PRETTY_FUNCTION__);    
        goto _exit;
    }
    if(index%MODULO_SHIFT_BASIC) {
        fprintf(stderr, "%s: index not aligned on byte\n", __PRETTY_FUNCTION__);    
        goto _exit;
    }
    if(lsb<size-1) {
        fprintf(stderr, "%s: size greater than lsb\n", __PRETTY_FUNCTION__);    
        goto _exit;
    }
    if(lsb<index) {
        fprintf(stderr, "%s: index out of range\n", __PRETTY_FUNCTION__);    
        goto _exit;
    }
    
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

        fprintf(stderr, "%s: nmax(%d), nmin(%d), nindex(%d)\n", __PRETTY_FUNCTION__, nmax, nmin, nindex);    
        
        if(nindex<nmin) {
            fprintf(stderr, "%s: index lower than min\n", __PRETTY_FUNCTION__);    
        }
        else if(nindex==nmax) {
            uint8_t nb=lsb-index+1;
            uint8_t rem2=0;
            if(rem>size) {
                nb=size;
                rem2=rem-nb;
            }
            fprintf(stderr, "%s: index max, nb(%d), rem2(%d)\n", __PRETTY_FUNCTION__, nb, rem2);    
            b_pos=lsb+1-size-index;
            b_sz=lsb-index+1;
            if(b_sz>size) b_sz=size;
            if(b_pos>=MODULO_SHIFT_BASIC) b_pos=0; 
            
        }
        else if(nindex==nmin) {
            fprintf(stderr, "%s: index min\n", __PRETTY_FUNCTION__);    
            b_sz=lsb-MODULO_SHIFT_BASIC*(nmax-1)+1;   // part of size of nmax byte
            b_sz=size-b_sz-MODULO_SHIFT_BASIC*(nmax-nmin-1);   
            b_pos=MODULO_SHIFT_BASIC-b_sz;
        }
        else {
            fprintf(stderr, "%s: intermediate full byte\n", __PRETTY_FUNCTION__);    
            // mask=dm_compute_mask8(MODULO_SHIFT_BASIC);
            mask=0xff;
        }
             
        if(b_sz) {
            fprintf(stderr, "%s: b_sz(%d), b_pos(%d)\n", __PRETTY_FUNCTION__, b_sz, b_pos);    
            mask=dm_compute_mask8(b_sz)<<b_pos;
        }
    }
    
    
_exit:
    return mask;
}
