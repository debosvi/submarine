
#include <stdio.h>
#include <errno.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include <skalibs/djbunix.h>

#include "private/canmsg_p.h"
#include "private/daemon_p.h"

///////////////////////////////////////////////////////////////////////////////
int handle_candev(candev_t *item) {
    int ret=-1;
    struct can_frame frame;
    
    if(!item) return -1;
    
    ret = recv(item->fd, &frame, sizeof(struct can_frame), MSG_WAITALL);
    if(ret < (int)sizeof(struct can_frame)) {
        strerr_warn2x(__PRETTY_FUNCTION__, ": error reading frame from RAW socket\n");
        goto exit;
    } 
    else {
        if(frame.can_id & CAN_ERR_FLAG) {
            /* TODO implement */
        } 
        else if(frame.can_id & CAN_RTR_FLAG) {
            /* TODO implement */
        } 
        else {
            char *msg=build_can_frame(&frame);
            
            if(msg) {
                strerr_warn4x(__PRETTY_FUNCTION__, ": CAN frame to transmit (", msg, ")");
                free(msg);
            }
            else {
                strerr_warn2x(__PRETTY_FUNCTION__, ": unable to build CAN frame");
            }
            
            
        }
        ret=0;
    }
    
exit:
    return ret;
}