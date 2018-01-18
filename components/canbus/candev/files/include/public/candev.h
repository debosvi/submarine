/* ISC license. */

#ifndef __S6CANBUS_CANDEV_H__
#define __S6CANBUS_CANDEV_H__

#include <s6canbus/types.h>

#if !defined(USE_CANDEV_CONFIG_FILE)
    #define S6CANBUS_CANDEV_REGULAR     (1)
    #define S6CANBUS_CANDEV_FAKE        (0)
#endif

int s6cb_candev_open(const char *pathname);
int s6cb_candev_close(const int fd);
ssize_t s6cb_candev_read(int fd, void *buf, size_t count);
ssize_t s6cb_candev_write(int fd, const void *buf, size_t count);

#if defined(USE_CANDEV_CONFIG_FILE)
#include "candev-config.h"

#if !defined(S6CANBUS_CANDEV_REGULAR) || !defined(S6CANBUS_CANDEV_FAKE)
#error "Custom CANDEV config file must define either S6CANBUS_CANDEV_REGULAR or S6CANBUS_CANDEV_FAKE"
#endif

#if defined(S6CANBUS_CANDEV_REGULAR) & defined(S6CANBUS_CANDEV_FAKE)
#error "Custom CANDEV config file must define only one amog S6CANBUS_CANDEV_REGULAR and S6CANBUS_CANDEV_FAKE"
#endif

#endif // defined USE_CANDEV_CONFIG_FILE

#endif // __S6CANBUS_CANDEV_H__
