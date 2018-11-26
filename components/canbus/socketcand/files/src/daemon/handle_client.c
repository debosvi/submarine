
#include <unistd.h>

#include <binn/json.h>

#include "private/canmsg_p.h"
#include "private/daemon_p.h"

///////////////////////////////////////////////////////////////////////////////
static int manage_server_connection(canio_t *io, char *buf, unsigned int len) {
    int ret=-1;
    int rjson=0;
    (void)len;
    
    // strerr_warn4x(__PRETTY_FUNCTION__, ": buf received (", buf, ")");
    
    switch(io->state) {
        case STATE_NO_BUS: 
        {
            char *shi=build_hi_msg();
            buffer_putsnoflush(&io->out, shi);
            io->state=STATE_INIT;
            free(shi);
        }
            ret=0;
            break;
    
        case STATE_INIT:
        {
            binn_t head=BINN_INVALID;
            rjson=json_to_binn(buf, &head);
            char* cmd=get_msg_cmd(head);
            if(cmd && !strncmp(cmd, "open", 4)) {
                char* dev=get_msg_device(head);
                char* status=0;
                
                for(unsigned int i=0; dev && i<candev_count_g; i++) {
                    candev_t* pdev=&candev_g[i];
                    if(!strcmp(pdev->dname, dev)) {
                        status=build_ok_msg();                        
                        add_candev(pdev->dname);
                        io->state=STATE_OPEN;
                    }
                }
                if(!status)  {
                    status=build_nok_msg();
                    io->state=STATE_NO_BUS;
                }
                buffer_putsnoflush(&io->out, status);  
                free(status);  
                ret=rjson;
                
            }
            else {
                remove_canio_ptr(io);
            }
            binn_free(head);
        }
            // ret=0;
            break;
            
        case STATE_OPEN:
        {
            binn_t head=BINN_INVALID;
            rjson=json_to_binn(buf, &head);
            char* cmd=get_msg_cmd(head);
            if(cmd && !strncmp(cmd, "mode", 4)) {
                canio_mode_t mode=MODE_COUNT;
                char* status=0;
                
                if(!get_msg_mode(head, &mode) && (mode==MODE_RAW)) {
                    status=build_ok_msg(); 
                    io->state=STATE_RAW;
                }

                if(!status)  {
                    status=build_nok_msg();
                    io->state=STATE_NO_BUS;
                }
                buffer_putsnoflush(&io->out, status);  
                free(status);
                ret=rjson;                
            }
            else {
                remove_canio_ptr(io);
            }
            binn_free(head);
        }
            // ret=0;
            break;

        case STATE_BCM:
        case STATE_RAW:
        case STATE_SHUTDOWN:
        case STATE_CONTROL:
        case STATE_ISOTP:
        case STATE_COUNT:
            strerr_warn2x(__PRETTY_FUNCTION__, ": state not relevant");
            break;
        default:
            strerr_warn2x(__PRETTY_FUNCTION__, ": state not managed");
            break;        
    }
    
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
static int manage_client_connection(canio_t *io, char *buf, unsigned int len) {
    int ret=-1;
    int rjson=0;
    (void)len;

    // strerr_warn4x(__PRETTY_FUNCTION__, ": buf received (", buf, ")");
    
    switch(io->state) {
        case STATE_NO_BUS: 
        {
            binn_t head=BINN_INVALID;
            rjson=json_to_binn(buf, &head);
            char* cmd=get_msg_cmd(head);
            if(cmd && !strncmp(cmd, "hi", 2)) {
                char *sopen=build_open_device(io->dname);
                if(sopen) {
                    buffer_putsnoflush(&io->out, sopen);
                    free(sopen);
                }
                io->state=STATE_INIT;
                ret=rjson;    
            }
            else {
                remove_canio_ptr(io);
            }
            binn_free(head);
        }
            // ret=0;
            break;
    
        case STATE_INIT:
        {
            binn_t head=BINN_INVALID;
            rjson=json_to_binn(buf, &head);
            char* status=get_msg_status(head);
            if(status && !strncmp(status, "ok", 2)) {
                char *mode=build_mode_msg(MODE_RAW);
                if(mode) {
                    buffer_putsnoflush(&io->out, mode);
                    free(mode);
                }
                io->state=STATE_OPEN;
                ret=rjson;    
            }
            else if(status && !strncmp(status, "nok", 3)) {
                io->state=STATE_NO_BUS;
                ret=rjson;    
            }
            else {
                remove_canio_ptr(io);
            }
            binn_free(head);
        }
            // ret=0;
            break;

        case STATE_OPEN:
        {
            binn_t head=BINN_INVALID;
            rjson=json_to_binn(buf, &head);
            char* status=get_msg_status(head);
            if(status && !strncmp(status, "ok", 2)) {
                io->state=STATE_RAW;
                ret=rjson;    
            }
            else if(status && !strncmp(status, "nok", 3)) {
                io->state=STATE_NO_BUS;
                ret=rjson;    
            }
            else {
                remove_canio_ptr(io);
            }
            binn_free(head);
        }
            // ret=0;
            break;

        case STATE_RAW:
        {
            binn_t head=BINN_INVALID;
            rjson=json_to_binn(buf, &head);
            char* cmd=get_msg_cmd(head);
            if(cmd && !strncmp(cmd, "send", 4)) {
                struct can_frame frame;
                
                if(!get_msg_frame(head, &frame)) {
                    for(unsigned int i=0; i<candev_count_g; i++) {
                        candev_t *pdev=&candev_g[i];
                        if(!strcmp(pdev->dname, io->dname))
                            write(pdev->fd, &frame, sizeof(struct can_frame));
                    }
                }
                ret=rjson;    
            }
            else {
                ret=-1;// remove_canio_ptr(io);
                break;
            }
            binn_free(head);
        }
            // ret=0;
            break;

        case STATE_BCM:
        case STATE_SHUTDOWN:
        case STATE_CONTROL:
        case STATE_ISOTP:
        case STATE_COUNT:
            strerr_warn2x(__PRETTY_FUNCTION__, ": state not relevant");
            break;
        default:
            strerr_warn2x(__PRETTY_FUNCTION__, ": state not managed");
            break;        
    }
    
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
int handle_client(canio_t *io, char *buf, unsigned int len) {
    int ret=-1;

    if(io->type==CANIO_FD_SERVER)
        ret=manage_server_connection(io, buf, len);
    else if(io->type==CANIO_FD_CLIENT)
        ret=manage_client_connection(io, buf, len);   

    return ret;
}

