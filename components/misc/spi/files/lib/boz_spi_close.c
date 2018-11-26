
#include "private/spi_p.h"

///////////////////////////////////////////////////////////////////////////////
spi_error_t boz_spi_close(spi_t spi) {
    if(spi>=BOZ_SPI_MAX_ITF) return SPI_ERROR_ITF;
    
    {
        spi_itf_elem_t *p=&spi_itf_elem_storage_g[spi];
        if(SPI_ITF_STATUS_INIT_ISCLEAR(p->status)) return SPI_ERROR_FAIL;
        
        SPI_ITF_STATUS_INIT_CLEAR(p->status);        
    }    
    
    return SPI_ERROR_NONE;
}
