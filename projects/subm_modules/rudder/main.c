
#include <skalibs/strerr2.h>

#include <s6canbus/candev.h>


int main(int ac, char **av) {
    int r;
    r=s6cb_candev_open("/dev/vcan0");
    
    
}
