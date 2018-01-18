/* ISC license. */

#ifndef __S6CANBUS_FILLBUF_PRIVATE_H__
#define __S6CANBUS_FILLBUF_PRIVATE_H__

#include <s6canbus/errors.h>
#include <s6canbus/candev.h>

#if S6CANBUS_CANDEV_REGULAR

#elif S6CANBUS_CANDEV_FAKE
#include <skalibs/gensetdyn.h>

#define S6CANBUS_CANDEV_PRIV_DEVNAME_SIZE (64)

typedef struct s6cb_candev_internal_s s6cb_candev_internal_t, *s6cb_candev_internal_ref ;
struct s6cb_candev_internal_s
{
    int fd;
    unsigned char dev[S6CANBUS_CANDEV_PRIV_DEVNAME_SIZE];
};
#define S6CB_CANDEV_INTERNAL_ZERO { .fd=-1, .dev={0} }
extern const s6cb_candev_internal_t s6cb_candev_internal_zero ;

extern gensetdyn s6cb_candev_internal_data_g ;

// get storage index based on fd
extern int s6cb_candev_internal_idx_fd(const int fd);
// get storage index based on dev name
extern int s6cb_candev_internal_idx_name(const char *pathname);

#endif

#endif // __S6CANBUS_FILLBUF_PRIVATE_H__
