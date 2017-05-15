
#include <canbus/canbus.h>

int main(void) {
    int fd=-1;
    
    fd=canbus_open("/dev/can0", 0);
    
    return 1;
}