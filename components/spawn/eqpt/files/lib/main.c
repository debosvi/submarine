
#include <skalibs/selfpipe.h>
#include <skalibs/strerr2.h>

#include <subm/equipment.h>

#ifndef PROG_NAME
#error "Must set PROG_NAME variable"
#endif

int main(void) {
    int r=0;
    PROG=PROG_NAME;    
    strerr_warnw3x("start of (", PROG, ")");
    
    strerr_warnw1x("call 'equipment_fct'");
    r=equipment_fct();
    if(!r)
        strerr_warnw1x("end 'equipment_fct' success");
    else
        strerr_warnw1x("end 'equipment_fct' error");
    
    strerr_warnw3x("end of (", PROG, ")");
    return 0;
}