
#ifndef __BOZ_SPI_ERRORS_H__
#define __BOZ_SPI_ERRORS_H__

#include <stdint.h>

typedef uint8_t spi_error_t;

#define SPI_ERROR_NONE          (0)
#define SPI_ERROR_ITF           (1)
#define SPI_ERROR_BAD_ARG       (2)
#define SPI_ERROR_RANGE         (3)
#define SPI_ERROR_FAIL          (4)
#define SPI_ERROR_NOT_IMPL      (5)
#define SPI_ERROR_ALREADY       (6)

#endif // __BOZ_SPI_ERRORS_H__
