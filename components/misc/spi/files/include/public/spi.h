
#ifndef __BOZ_SPI_BUS_H__
#define __BOZ_SPI_BUS_H__

// #include <stddef.h>
#include <stdint.h>
#include <boz/spi/errors.h>

typedef uint8_t spi_t;
#define SPI_INVALID_VALUE   ((spi_t)-1)

typedef uint8_t spi_itf_t;
typedef uint16_t spi_clock_khz_t;

extern spi_error_t boz_spi_init(void);
extern spi_error_t boz_spi_fini(void);

extern spi_error_t boz_spi_open(spi_t* const spi, const spi_itf_t itf, const spi_clock_khz_t clock);
extern spi_error_t boz_spi_reset(spi_t spi);
extern spi_error_t boz_spi_close(spi_t spi);

extern spi_error_t boz_spi_begin(spi_t spi);
extern spi_error_t boz_spi_end(spi_t spi);
extern spi_error_t boz_spi_read(spi_t spi, uint8_t *data);
extern spi_error_t boz_spi_write(spi_t spi, const uint8_t data);

#endif // __BOZ_SPI_BUS_H__
