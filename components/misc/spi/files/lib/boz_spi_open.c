
#include "private/spi_p.h"

///////////////////////////////////////////////////////////////////////////////
spi_error_t boz_spi_open(spi_t* const spi, const spi_itf_t itf, const spi_clock_khz_t clock) {
    spi_error_t ret=SPI_ERROR_NONE;
    
    if(!spi) { ret=SPI_ERROR_BAD_ARG; goto _exit; }
    if(!itf || (itf>BOZ_SPI_MAX_ITF)) { ret=SPI_ERROR_ITF; goto _exit; }
    if(!clock) { ret=SPI_ERROR_RANGE; goto _exit; }
    
    {
        uint8_t idx=itf-1;
        spi_itf_elem_t *p=&spi_itf_elem_storage_g[idx];
        if(SPI_ITF_STATUS_INIT_ISSET(p->status)) { 
            ret=SPI_ERROR_ALREADY; 
            goto _exit; 
        }
        
        SPI_ITF_STATUS_INIT_SET(p->status);  
        p->clock = clock;
        (*spi)=idx;
    }    

_exit:
    if(ret!=SPI_ERROR_NONE) {
        if(spi) (*spi)=SPI_INVALID_VALUE;
    }
    return ret;
}
