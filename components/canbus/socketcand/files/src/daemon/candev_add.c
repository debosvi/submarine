
#include <stdio.h>
#include <errno.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include <linux/can.h>
// #include <linux/can/bcm.h>
// #include <linux/can/error.h>

#include <skalibs/djbunix.h>

#include "private/daemon_p.h"

///////////////////////////////////////////////////////////////////////////////
static int check_device_already_there(const char* const dname) {
    for(unsigned int i=0; i<candev_count_g; i++) {
        candev_t_ref p=&candev_g[i];
        if(!strcmp(p->dname, dname))
            return i;
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////////////
static int open_can_device(const char* const dname) {
    int ret=-1;
    struct ifreq ifr;
    struct sockaddr_can caddr;
    int fd=socket(PF_CAN, SOCK_RAW, CAN_RAW);
    const int timestamp_on = 0;
    
    if(fd<0) {
        strerr_warn3x(__PRETTY_FUNCTION__, ": error while opening BCM socket: ", strerror(errno));
        goto exit;
    }

    memset(&ifr, 0, sizeof(struct ifreq));
    strcpy(ifr.ifr_name, dname);
    
    if(ioctl(fd, SIOCGIFINDEX, &ifr) < 0) {
        strerr_warn3x(__PRETTY_FUNCTION__, ": error while searching for bus: ", strerror(errno));
        goto exit;
    }

    if(setsockopt(fd, SOL_SOCKET, SO_TIMESTAMP, &timestamp_on, sizeof(timestamp_on)) < 0) {
        strerr_warn2x(__PRETTY_FUNCTION__, ": could not enable CAN timestamps");
        goto exit;
    }

    memset(&caddr, 0, sizeof(struct sockaddr_can));
    caddr.can_family = AF_CAN;
    caddr.can_ifindex = ifr.ifr_ifindex;
    
    /* bind socket */
    if(bind(fd, (struct sockaddr *) &caddr, sizeof(caddr)) < 0) {
        strerr_warn3x(__PRETTY_FUNCTION__, ": error while binding RAW socket: ", strerror(errno));
        goto exit;
    }

    ret=0;
    
exit:
    if(ret<0) {
        fd_close(fd);
        fd=-1;
    }
    return fd;
}

///////////////////////////////////////////////////////////////////////////////
int add_candev(char *name) {
    candev_t_ref p=&candev_g[candev_count_g];
    int fd=-1;
    int idx=check_device_already_there(name);
    
    if(candev_count_g>=CANDEV_MAX) return -1;
    
    if(idx<0) {        
        strerr_warn4x(__PRETTY_FUNCTION__, ": open device '", name, "'");
        fd=open_can_device(name);
        if(fd<0) return -1;
        
        p->fd=fd;
        snprintf(&p->dname[0], CANDEV_NAMELG, "%s", name);
        candev_count_g++;
    }
    else {
        strerr_warn4x(__PRETTY_FUNCTION__, ": device '", name, "' already found");
        p=&candev_g[idx];
        p->open++;
    }  

    return 0;
}