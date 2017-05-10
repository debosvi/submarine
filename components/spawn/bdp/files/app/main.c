
#include <poll.h>

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

#include <subm/equipment.h>

static const char* ccs_prog_sname = "ccs_prog";
    
int equipment_fct(void) {
    int ccs_fds[2] = { -1, -1 };
    char const *cargv[2] = { ccs_prog_sname, 0};
    char const *cenvp[1] = { 0 };

    strerr_warnw3x("try to start CCS (", ccs_prog_sname, ")");
    
    pid_t ccs_pid=child_spawn (ccs_prog_sname, cargv, cenvp, ccs_fds, 2) ;
    if(!ccs_pid)
        strerr_diefu1x(100, "unable to start CCS");
    
    poll(0,0,2000);
    return 0;
}