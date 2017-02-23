
#define __USE_MISC

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <skalibs/strerr2.h>
#include <skalibs/fmtscan.h>

//#include "private/daemon_p.h"

static const char *ip_link_cmd0 = "ip link show type vcan";
#define MAX_BUF (40)

int main(int ac, char **av) {
    FILE *iplink_fp = 0;
    char line[MAX_BUF];

    // inits
    PROG = "socketcan_iface_scan" ;  
    strerr_warn1x("scan for any SocketCAN interfaces");

    // open command pipe
    iplink_fp = popen(ip_link_cmd0, "r");
    if(!iplink_fp) 
        strerr_diefu1x(111, "unable to scan for interfaces");

    // scan for results
    while(1) {
        char *if_name=0, *p=0;
        int id=0;
 
        fgets(line, MAX_BUF, iplink_fp);
        if(feof(iplink_fp))
            break;

        if(!sscanf(line, "%d:", &id)) continue;

        if_name=strchr(line, ':')+2;
        p=strchr(if_name, ':');
        if(p) (*p)=0;
        
        p=strstr(p+1, ",UP,");
        if(p)
            strerr_warn2x("iface name: ", if_name);

        // read until end of line
        p=strchr(line, 0x0A);
        while(!p) {
            fgets(line, MAX_BUF, iplink_fp);
            if(feof(iplink_fp))
                break;
            p=strchr(line, 0x0A);
        }
    }

    exit(EXIT_SUCCESS);
}
