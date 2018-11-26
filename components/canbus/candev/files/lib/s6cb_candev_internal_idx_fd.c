/* ISC license. */

#include <private/candev_p.h>

#if S6CANBUS_CANDEV_FAKE

typedef struct {
    int fd;
    int found;
} s6cb_candev_iter_data_t;

static int s6cb_candev_iter_getfd (char *elem, void *data) {
    s6cb_candev_internal_t *p_elem=(s6cb_candev_internal_t*)elem;
    s6cb_candev_iter_data_t *p_data=(s6cb_candev_iter_data_t*)data;
    
    if(p_elem->fd==p_data->fd)  { p_data->found=1; return 0; }
    return 1;    
}

int s6cb_candev_internal_idx_fd(const int fd) {
    s6cb_candev_iter_data_t data= { .fd=fd, .found=0 };
    uint32_t idx=gensetdyn_iter(&s6cb_candev_internal_data_g, s6cb_candev_iter_getfd, &data);
    if(data.found) return idx-1;
    
    return -1;
}

#endif
