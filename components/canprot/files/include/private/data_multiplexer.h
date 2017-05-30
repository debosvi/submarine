
#ifndef _DATA_MULTIPLEXER_H_
#define _DATA_MULTIPLEXER_H_

#include <stdint.h>

#define DM_MODULO_SHIFT_BASIC  (8)
#define DM_MODULO_SHIFT_SHIFT  (3)

#define DM_OUTPUT_MAX_BYTES     (16)
#define DM_OUTPUT_MAX_BITS      (8*DM_OUTPUT_MAX_BYTES)

#define DM_INPUT_MAX_BYTES      (8)
#define DM_INPUT_MAX_BITS       (8*DM_INPUT_MAX_BYTES)

#define DM_ERR_NO_ERROR     (0)
#define DM_ERR_NULL_PTR     (1)
#define DM_ERR_BAD_PARAM    (2)
#define DM_ERR_OVERLAP      (3)

#define dm_set_data dm_set_data_lsb

extern uint8_t dm_get_nb_bytes(const uint8_t nb);

// limited to 8 bits
extern uint8_t dm_compute_mask8(const uint8_t size);
// limited to 64 bits
extern uint64_t dm_compute_mask64(const uint8_t size);

// lsb in bits, size in bits, shift in bits from lsb
extern uint8_t dm_compute_mask_shift8(const uint8_t lsb, const uint8_t size, const uint8_t shift);

extern int dm_set_data64_msb(void* out, const uint16_t max, const uint8_t pos, const uint8_t size, const uint64_t in);
extern int dm_set_data64_lsb(void* out, const uint16_t max, const uint8_t pos, const uint8_t size, const uint64_t in);

// max in bits, pos in bits, size in bits 
extern int dm_set_data8_msb(void* out, const uint16_t max, const uint8_t pos, const uint8_t size, const uint8_t* const in);
extern int dm_set_data8_lsb(void* out, const uint16_t max, const uint8_t pos, const uint8_t size, const uint8_t* const in);

#endif  // _DATA_MULTIPLEXER_H_
