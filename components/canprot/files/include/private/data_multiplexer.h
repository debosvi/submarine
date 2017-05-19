
#ifndef _DATA_MULTIPLEXER_H_
#define _DATA_MULTIPLEXER_H_

#include <stdint.h>

#define DM_OUTPUT_MAX_BYTES     (16)
#define DM_OUTPUT_MAX_BITS      (8*DM_OUTPUT_MAX_BYTES)

#define DM_INPUT_MAX_BYTES      (8)
#define DM_INPUT_MAX_BITS       (8*DM_INPUT_MAX_BYTES)

#define DM_ERR_NO_ERROR     (0)
#define DM_ERR_NULL_PTR     (1)
#define DM_ERR_BAD_PARAM    (2)
#define DM_ERR_OVERLAP      (3)

#define dm_set_data dm_set_data_lsb

// limited to 8 bits
uint8_t dm_compute_mask8(const uint8_t size);
// limited to 864 bits
uint64_t dm_compute_mask64(const uint8_t size);

// lsb in bits, size in bits, shift in bits from lsb
uint8_t dm_compute_mask_shift8(const uint8_t lsb, const uint8_t size, const uint8_t shift);


int dm_set_data_msb(void* out, const uint16_t max, const uint8_t pos, const uint8_t size, const uint64_t in);
int dm_set_data_lsb(void* out, const uint16_t max, const uint8_t pos, const uint8_t size, const uint64_t in);

#endif  // _DATA_MULTIPLEXER_H_
