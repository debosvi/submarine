
#include <stdio.h>
#include <string.h>

#include "private/data_multiplexer.h"

#define MAX_COMP    (8)

typedef struct {
    uint8_t lsb;
    uint8_t size;
    uint8_t shift;
    uint8_t comp;
} test_data_t;

static const test_data_t data_mask_g[] = {
    { .lsb=1, .size=2, .shift=0, .comp = 0 },       // 'lsb' out of band compared to 'size'
    { .lsb=8, .size=1, .shift=2, .comp = 0 },       // 'shift' greater than 'lsb' allows
    { .lsb=8, .size=0, .shift=1, .comp = 0 },       // correct value for 'shift' and 'lsb', no size
    { .lsb=8, .size=0, .shift=1, .comp = 0 },       // correct value for 'shift' and 'lsb', no size
    
    // iterate over all bits (1 bit) in shift 0
    { .lsb=0, .size=1, .shift=0, .comp = 0x01 },       // correct args
    { .lsb=1, .size=1, .shift=0, .comp = 0x02 },       // correct args
    { .lsb=2, .size=1, .shift=0, .comp = 0x04 },       // correct args
    { .lsb=3, .size=1, .shift=0, .comp = 0x08 },       // correct args
    { .lsb=4, .size=1, .shift=0, .comp = 0x10 },       // correct args
    { .lsb=5, .size=1, .shift=0, .comp = 0x20 },       // correct args
    { .lsb=6, .size=1, .shift=0, .comp = 0x40 },       // correct args
    { .lsb=7, .size=1, .shift=0, .comp = 0x80 },       // correct args

    // iterate over all bits (all bit to set from lsb) in shift 0
    { .lsb=1, .size=2, .shift=0, .comp = 0x03 },       // correct args
    { .lsb=2, .size=3, .shift=0, .comp = 0x07 },       // correct args
    { .lsb=3, .size=4, .shift=0, .comp = 0x0f },       // correct args
    { .lsb=4, .size=5, .shift=0, .comp = 0x1f },       // correct args
    { .lsb=5, .size=6, .shift=0, .comp = 0x3f },       // correct args
    { .lsb=6, .size=7, .shift=0, .comp = 0x7f },       // correct args
    { .lsb=7, .size=8, .shift=0, .comp = 0xff },       // correct args

    // iterate over all bits (2 bits only) in shift 0
    { .lsb=2, .size=2, .shift=0, .comp = 0x06 },       // correct args
    { .lsb=3, .size=2, .shift=0, .comp = 0x0a },       // correct args
    { .lsb=4, .size=2, .shift=0, .comp = 0x18 },       // correct args
    { .lsb=5, .size=2, .shift=0, .comp = 0x30 },       // correct args
    { .lsb=6, .size=2, .shift=0, .comp = 0x60 },       // correct args
    { .lsb=7, .size=2, .shift=0, .comp = 0xa0 },       // correct args
   
    // { .lsb=8, .size=1, .shift=1, .comp = 0x01 },       // first bit to set in 'shift' 1
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static int test_all_mask(const int max) {
    int _ret=0;
    uint8_t comp=-1;
    
    for(int i=0; i<max; i++) {
        fprintf(stderr, "loop %02d: ", i);
        comp = dm_compute_mask_shift8(data_mask_g[i].lsb, data_mask_g[i].size, data_mask_g[i].shift);
        if(comp!=data_mask_g[i].comp) {
            fprintf(stderr, "error code mismatch, expected(0x%02x), current(0x%02x)\n", data_mask_g[i].comp, comp);
            _ret=1;
        }
        else {
            fprintf(stderr, "output correct\n");
        }
    }
    
    return _ret;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main(void) {
    int _ret=0;
    int max=0;
    
    max=sizeof(data_mask_g)/sizeof(test_data_t);
    test_all_mask(max);
    
    return _ret;
}
