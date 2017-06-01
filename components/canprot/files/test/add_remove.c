
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include <skalibs/strerr2.h>

#include <canprot/canprot.h>

#include "private/canprot_p.h"
// #include "restricted/canprot_r.h"

const canbus_frame_t frame_invalid0 = { .dlc=9, .id=0x123456, .data={0} };
const canbus_frame_t frame_invalid1 = { .dlc=0, .id=0x123456, .data={0} };
const canbus_frame_t frame_valid[] = { 
    { .dlc=3, .id=0x123456, .data={0,1,2} },
    { .dlc=5, .id=0x123457, .data={1,2,3,4,5} },
    { .dlc=1, .id=0x123458, .data={6} },
    { .dlc=8, .id=0x123459, .data={2,3,4,5,6,7,8,9} },
    { .dlc=4, .id=0x123459, .data={0} },
};

static void print_run(void) {
    fprintf(stderr, "run status, next(%d), count(%d), next order(%d)\n", 
        canprot_tosend_run_g.next, canprot_tosend_run_g.count, canprot_tosend_run_g.n_order);
}

static void print_list(void) {
    register int i=0;
    for(; i<CANPROT_MAX_TOSEND_FRAMES; i++) {
        fprintf(stderr, "run value[%d], order(%d), dlc(%d), id(0x%08x)\n", 
            i, canprot_tosend_frames_storage_g[i].order, 
            canprot_tosend_frames_storage_g[i].frame.dlc, canprot_tosend_frames_storage_g[i].frame.id);
    }
        
        
}

int main(void) {
    int r=-1;
    
    PROG = PROG_NAME;
    
    // strerr_warni1x("canprot_init");
    // if(canprot_init()) {
        // strerr_warnwu1x("canprot_init");
        // goto _exit;
    // }
    
    {
        register int i=0;
        for(; i<CANPROT_MAX_TOSEND_FRAMES; i++) {
            canprot_tosend_frames_storage_g[i] = canprot_tosend_zero;
        }
    }

    print_run();
    print_list();
    
    strerr_warni1x("canprot_tosend_add_frame (no frame)");
    r=canprot_tosend_add_frame(0);
    if(r!=1) strerr_warnw1x("canprot_tosend_add_frame should fail with (no frame)");
    
    strerr_warni1x("canprot_tosend_add_frame (no dlc)");
    r=canprot_tosend_add_frame(&frame_invalid0);
    if(r!=1) strerr_warnw1x("canprot_tosend_add_frame should fail with (no dlc)");
    
    strerr_warni1x("canprot_tosend_add_frame (excess dlc)");
    r=canprot_tosend_add_frame(&frame_invalid1);
    if(r!=1) strerr_warnw1x("canprot_tosend_add_frame should fail (excess dlc)");

    print_run();
    print_list();
    
    for(int i=0; i<CANPROT_MAX_TOSEND_FRAMES; i++) {
        strerr_warni1x("canprot_tosend_add_frame");
        r=canprot_tosend_add_frame(&frame_valid[i%4]);
        if(r) strerr_warnwu1x("canprot_tosend_add_frame");
        // else strerr_warnw1x("canprot_tosend_add_frame success");
    }

    print_run();
    print_list();
    
    strerr_warni1x("canprot_tosend_add_frame (limit reached)");
    r=canprot_tosend_add_frame(&frame_valid[2]);
    if(r!=1) strerr_warnw1x("canprot_tosend_add_frame should fail (limit reached)");
 
    strerr_warni1x("canprot_tosend_remove_frame idx 0");
    r=canprot_tosend_remove_frame(0);
    if(r) strerr_warnwu1x("canprot_tosend_remove_frame");
 
    strerr_warni1x("canprot_tosend_remove_frame idx 0");
    r=canprot_tosend_remove_frame(0);
    if(r) strerr_warnwu1x("canprot_tosend_remove_frame");
 
    strerr_warni1x("canprot_tosend_remove_frame idx 1");
    r=canprot_tosend_remove_frame(1);
    if(r) strerr_warnwu1x("canprot_tosend_remove_frame");
 
    strerr_warni1x("canprot_tosend_remove_frame idx 5");
    r=canprot_tosend_remove_frame(5);
    if(r) strerr_warnwu1x("canprot_tosend_remove_frame");
 
    strerr_warni1x("canprot_tosend_remove_frame idx 7");
    r=canprot_tosend_remove_frame(7);
    if(r) strerr_warnwu1x("canprot_tosend_remove_frame");

    print_run();
    print_list();
    
    strerr_warni1x("canprot_tosend_remove_frame (greater than allowed)");
    r=canprot_tosend_remove_frame(CANPROT_MAX_TOSEND_FRAMES);
    if(r!=1) strerr_warnw1x("canprot_tosend_remove_frame (greater than allowed)");

    print_run();
    print_list();
    
    for(int i=0; i<CANPROT_MAX_TOSEND_FRAMES; i++) {
        strerr_warni1x("canprot_tosend_add_frame");
        r=canprot_tosend_add_frame(&frame_valid[i%4]);
        if(r) strerr_warnwu1x("canprot_tosend_add_frame");
        // else strerr_warnw1x("canprot_tosend_add_frame success");
        // print_run();
        // print_list();
    }
    
    print_run();
    print_list();
    
    for(int i=0; i<CANPROT_MAX_TOSEND_FRAMES+1; i++) {
        strerr_warni1x("canprot_tosend_remove_next");
        r=canprot_tosend_remove_next();
        if(r) strerr_warnwu1x("canprot_tosend_remove_next");
        // else strerr_warnw1x("canprot_tosend_add_frame success");
        // print_run();
        // print_list();
    }
    
    print_run();
    print_list();
    
    for(int i=0; i<CANPROT_MAX_TOSEND_FRAMES; i++) {
        strerr_warni1x("canprot_tosend_add_frame");
        r=canprot_tosend_add_frame(&frame_valid[i%4]);
        if(r) strerr_warnwu1x("canprot_tosend_add_frame");
        // else strerr_warnw1x("canprot_tosend_add_frame success");
    }
    
    print_run();
    print_list();
    
    for(int i=0; i<CANPROT_MAX_TOSEND_FRAMES; i++) {
        strerr_warni1x("canprot_tosend_remove_next");
        r=canprot_tosend_remove_next();
        if(r) strerr_warnwu1x("canprot_tosend_remove_next");
        // else strerr_warnw1x("canprot_tosend_remove_next success");
    }
    
    print_run();
    print_list();
    
    
// _exit:
    // strerr_warni1x("canprot_fini");
    // if(canprot_fini()) {
        // strerr_warnwu1x("canprot_fini");
    // }
    
    return 0;
}