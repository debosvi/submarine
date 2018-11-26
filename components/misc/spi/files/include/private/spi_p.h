
#ifndef __BOZ_SPI_BUS_PRIVATE_H__
#define __BOZ_SPI_BUS_PRIVATE_H__

#include <boz/spi/spi.h>
#include <boz/spi/errors.h>

#ifdef BOZ_SPI_MICROCHIP


#else 
#error "BOZ_SPI family must be set among BOZ_SPI_MICROCHIP."
#endif

#ifndef BOZ_SPI_MAX_ITF
#define BOZ_SPI_MAX_ITF     (3)
#endif

#define SPI_ITF_STATUS_BIT_INIT (0)

#define SPI_ITF_STATUS_BIT_SET(x,b)         (x)|=(1<<(b&0xff))
#define SPI_ITF_STATUS_BIT_CLEAR(x,b)       (x)&=~(1<<(b&0xff))
#define SPI_ITF_STATUS_BIT_ISSET(x,b)       ((x)&(1<<(b&0xff)))
#define SPI_ITF_STATUS_BIT_ISCLEAR(x,b)     !((x)&(1<<(b&0xff)))

#define SPI_ITF_STATUS_INIT_SET(x)          SPI_ITF_STATUS_BIT_SET(x, SPI_ITF_STATUS_BIT_INIT)
#define SPI_ITF_STATUS_INIT_CLEAR(x)        SPI_ITF_STATUS_BIT_CLEAR(x, SPI_ITF_STATUS_BIT_INIT)
#define SPI_ITF_STATUS_INIT_ISSET(x)        SPI_ITF_STATUS_BIT_ISSET(x, SPI_ITF_STATUS_BIT_INIT)
#define SPI_ITF_STATUS_INIT_ISCLEAR(x)      SPI_ITF_STATUS_BIT_ISCLEAR(x, SPI_ITF_STATUS_BIT_INIT)

typedef struct {
    uint8_t status;
    spi_clock_khz_t clock;
} spi_itf_elem_t;

#define SPI_ITF_ELEM_ZERO    { .status=0, .clock=0 }
extern spi_itf_elem_t spi_itf_elem_zero;

extern spi_itf_elem_t spi_itf_elem_storage_g[BOZ_SPI_MAX_ITF];

#endif // __BOZ_SPI_BUS_PRIVATE_H__
