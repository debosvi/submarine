
#ifndef __S6CANBUS_J1939_PGNS_H__
#define __S6CANBUS_J1939_PGNS_H__

typedef uint32_t s6cb_pgn_t;
#define S6CB_PGN_INVALID     ((s6cb_pgn_t)0)

// tools and macros
#define S6CB_PGN_MASK_8(val)    (val&0xff)
#define S6CB_PGN_MASK_16(val)   (val&0xffff)

#define S6CB_PGN_BUILD_ID(format,specific)      ((S6CB_PGN_MASK_8(format)<<8)+S6CB_PGN_MASK_8(specific))
#define S6CB_PGN_SPECIFIC(id)                   (S6CB_PGN_MASK_8(id>>0))
#define S6CB_PGN_FORMAT(id)                     (S6CB_PGN_MASK_8(id>>8))

#define S6CB_PGN_RUDDER         (0x01)
// #define S6CB_PGN_PROPELLER      (0x02)

#endif // __S6CANBUS_J1939_PGNS_H__
