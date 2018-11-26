/* ISC license. */

#ifndef S6CANBUS_H
#define S6CANBUS_H

#include <sys/types.h>
#include <skalibs/gccattributes.h>

typedef enum {
    S6CANBUS_FLAG_ENABLE = 1,
    S6CANBUS_FLAG_DISABLE = 0
} s6canbus_flag_t;

extern int s6canbus_open(const char* const dev);
extern int s6canbus_set_loopback(const int fd, const s6canbus_flag_t flag);
extern int s6canbus_set_notmine(const int fd, const s6canbus_flag_t flag);
extern int s6canbus_get_openfd(void);

#endif
