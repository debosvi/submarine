
#include "private/spi_p.h"

///////////////////////////////////////////////////////////////////////////////
spi_error_t boz_spi_init(void) {
    int i=0;
    
    for(; i<BOZ_SPI_MAX_ITF; i++) {
        spi_itf_elem_storage_g[i]=spi_itf_elem_zero;
    }

    return SPI_ERROR_NONE;
}
