/* ISC license. */

#ifndef __S6CANBUS_CANDEV_H__
#define __S6CANBUS_CANDEV_H__

#include <sys/types.h>
#include <s6canbus/types.h>

#if !defined(USE_CANDEV_CONFIG_FILE)
    #define S6CANBUS_CANDEV_REGULAR     (1)
    #define S6CANBUS_CANDEV_FAKE        (0)
#endif

#define S6CANBUS_DATA_MINSIZE (8)

int s6cb_candev_open(const char *pathname);
int s6cb_candev_close(const int fd);
ssize_t s6cb_candev_read(const int fd, void* const buf, uint32_t* const id);
ssize_t s6cb_candev_write(const int fd, const uint32_t id, const void* const buf, const size_t count);

#if defined(USE_CANDEV_CONFIG_FILE)
#include "candev-config.h"

#if !S6CANBUS_CANDEV_REGULAR & !S6CANBUS_CANDEV_FAKE
#error "Custom CANDEV config file must define either S6CANBUS_CANDEV_REGULAR or S6CANBUS_CANDEV_FAKE"
#endif

#if S6CANBUS_CANDEV_REGULAR & S6CANBUS_CANDEV_FAKE
#error "Custom CANDEV config file must define only one among S6CANBUS_CANDEV_REGULAR and S6CANBUS_CANDEV_FAKE"
#endif

#endif // defined USE_CANDEV_CONFIG_FILE

#endif // __S6CANBUS_CANDEV_H__
