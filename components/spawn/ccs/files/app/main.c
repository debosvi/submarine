
#include <poll.h>

#include <skalibs/strerr2.h>

#include <subm/equipment.h>

int equipment_fct(void) {
    poll(0,0,1000);
    return 0;
}