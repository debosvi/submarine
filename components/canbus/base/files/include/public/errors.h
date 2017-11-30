
#ifndef __S6CANBUS_ERRORS_H__
#define __S6CANBUS_ERRORS_H__

#define S6CANBUS_ERROR_NONE         (0)     // success return
#define S6CANBUS_ERROR_NULLPTR      (1)     // pointer in args is NULL
#define S6CANBUS_ERROR_INVAL        (2)     // one or more args are invalid
#define S6CANBUS_ERROR_EMPTY        (3)     // data contains no data
#define S6CANBUS_ERROR_FULL         (4)     // data is full
#define S6CANBUS_ERROR_OVERLAY      (5)     // data overlay
#define S6CANBUS_ERROR_NOTFOUND     (6)     // element not found
#define S6CANBUS_ERROR_ALREADY      (7)     // element is already present
#define S6CANBUS_ERROR_INTERNAL     (8)     // internal error

#endif // __S6CANBUS_ERRORS_H__
