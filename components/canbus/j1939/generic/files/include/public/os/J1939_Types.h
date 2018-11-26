
#ifndef __J1939_TYPES_H__
#define __J1939_TYPES_H__

#include <stdint.h>

/*-------------------------------------------------------------------------
	Types
-------------------------------------------------------------------------*/

typedef uint8_t     J1939_bit_fields8_t;        /**< champ de 8 bits   */
typedef uint16_t    J1939_bit_fields16_t;       /**< champ de 16 bits  */
typedef uint8_t     J1939_size_t;               /**<  255 ipdus possible (ems + rcp) dans la NM */

// typedef struct
// {
//   /*! position of a frame in a schedule table */
//   uint8_t u8FrameIndex; 
//   /*! time distance with respect to the scheduler time tick before */
//   /*the frame header is sent (TX/RX)                               */  
//   uint8_t u8FrameTimeDistance;
// } st_OS_Sche_FrmPosDisType;
/*-------------------------------------------------------------------------
	Defines
-------------------------------------------------------------------------*/

#ifndef J1939_FALSE
#define J1939_FALSE     (0x55u)
#endif
#ifndef J1939_TRUE
#define J1939_TRUE      (0xAAu)
#endif
#ifndef J1939_BOOL
#define J1939_BOOL      uint8_t
#endif
#ifndef NULL
#define NULL            ((void *)0)     /**< definition de NULL   */
#endif

 /* this defines are used for schedule table management       */
#define OS_NO_SCHEDULE_TABLE_CHANGE_REQUEST_PENDING ((uint8_t) 0xFF)
#define OS_SCHEDULE_EMPTY_TABLE ((uint8_t)0)

#define _BITWISE_GEN_8(x)     (uint8_t)((uint8_t)1 << (uint8_t)x)
#define _BITWISE_GEN_16(x)    (uint16_t)((uint16_t)1 << (uint16_t)x)

#define _BIT_0        _BITWISE_GEN_8(0)     /**< definition pour lecture bit 0   */
#define _BIT_1        _BITWISE_GEN_8(1)     /**< definition pour lecture bit 1   */
#define _BIT_2        _BITWISE_GEN_8(2)     /**< definition pour lecture bit 2   */
#define _BIT_3        _BITWISE_GEN_8(3)     /**< definition pour lecture bit 3   */
#define _BIT_4        _BITWISE_GEN_8(4)     /**< definition pour lecture bit 4   */
#define _BIT_5        _BITWISE_GEN_8(5)     /**< definition pour lecture bit 5   */
#define _BIT_6        _BITWISE_GEN_8(6)     /**< definition pour lecture bit 6   */
#define _BIT_7        _BITWISE_GEN_8(7)     /**< definition pour lecture bit 7   */


#endif // __J1939_TYPES_H__
/*-------------------------------- end of file -------------------------------*/

