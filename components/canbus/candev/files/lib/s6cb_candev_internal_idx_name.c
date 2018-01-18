/* ISC license. */

#include <private/candev_p.h>

#if S6CANBUS_CANDEV_FAKE

static int s6cb_candev_iter_getfd (char *elem, void *data) {
    s6cb_candev_internal_t *p_elem=(s6cb_candev_internal_t*)elem;
   
    return strncmp(p_elem->dev, str_len(p_elem->dev), data);    
}

int s6cb_candev_internal_idx_name(const char *pathname) {
    return gensetdyn_iter(&s6cb_candev_internal_data_g, s6cb_candev_iter_getfd, (void*)pathname)
}

#endif
