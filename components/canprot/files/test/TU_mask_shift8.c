
#include <stdio.h>
#include <string.h>

#include "private/data_multiplexer.h"

#define MAX_COMP    (8)

#define KNRM  "\e[0m"
#define KRED  "\e[0;31m"
#define KGRN  "\e[0;32m"

typedef struct {
    uint8_t lsb;
    uint8_t size;
    uint8_t index;
    uint8_t comp;
} test_data_t;

static const test_data_t data_mask_g[] = {
    { .lsb=1, .size=3, .index=0, .comp = 0 },           // 'lsb' out of band compared to 'size'
    { .lsb=8, .size=1, .index=7, .comp = 0 },           // index not aligned on bytes 
    { .lsb=8, .size=1, .index=16, .comp = 0 },          // 'index' greater than 'lsb' allows
    { .lsb=8, .size=0, .index=0, .comp = 0 },           // correct value for 'index' and 'lsb', no size
    { .lsb=15, .size=1, .index=16, .comp = 0x00 },      // index out of range
    { .lsb=63, .size=64, .index=64, .comp = 0x00 },     // index out of range
 
    // iterate over all bits (1 bit) in index 0
    { .lsb=0, .size=1, .index=0, .comp = 0x01 },       // correct args
    { .lsb=1, .size=1, .index=0, .comp = 0x02 },       // correct args
    { .lsb=2, .size=1, .index=0, .comp = 0x04 },       // correct args
    { .lsb=3, .size=1, .index=0, .comp = 0x08 },       // correct args
    { .lsb=4, .size=1, .index=0, .comp = 0x10 },       // correct args
    { .lsb=5, .size=1, .index=0, .comp = 0x20 },       // correct args
    { .lsb=6, .size=1, .index=0, .comp = 0x40 },       // correct args
    { .lsb=7, .size=1, .index=0, .comp = 0x80 },       // correct args

    // iterate over all bits (all bit to set from lsb) in index 0
    { .lsb=1, .size=2, .index=0, .comp = 0x03 },       // correct args
    { .lsb=2, .size=3, .index=0, .comp = 0x07 },       // correct args
    { .lsb=3, .size=4, .index=0, .comp = 0x0f },       // correct args
    { .lsb=4, .size=5, .index=0, .comp = 0x1f },       // correct args
    { .lsb=5, .size=6, .index=0, .comp = 0x3f },       // correct args
    { .lsb=6, .size=7, .index=0, .comp = 0x7f },       // correct args
    { .lsb=7, .size=8, .index=0, .comp = 0xff },       // correct args

    // iterate over all bits (2 bits only) in index 0
    { .lsb=2, .size=2, .index=0, .comp = 0x06 },       // correct args
    { .lsb=3, .size=2, .index=0, .comp = 0x0c },       // correct args
    { .lsb=4, .size=2, .index=0, .comp = 0x18 },       // correct args
    { .lsb=5, .size=2, .index=0, .comp = 0x30 },       // correct args
    { .lsb=6, .size=2, .index=0, .comp = 0x60 },       // correct args
    { .lsb=7, .size=2, .index=0, .comp = 0xc0 },       // correct args
   
    { .lsb=8, .size=1, .index=0, .comp = 0x00 },       // 1 bit lsb in byte 1 ('index' 0)
    { .lsb=8, .size=1, .index=8, .comp = 0x01 },       // 1 bit lsb in byte 1 ('index' 1)
    { .lsb=9, .size=1, .index=8, .comp = 0x02 },       // 2nd bit lsb in byte 1 ('index' 1)
    { .lsb=10, .size=1, .index=8, .comp = 0x04 },      // 3rd bit lsb in byte 1 ('index' 1)
    { .lsb=8, .size=2, .index=0, .comp = 0x80 },       // 1 bit lsb in byte 1, and 1 bit msb in byte 0 ('index' 0)
    { .lsb=8, .size=2, .index=8, .comp = 0x01 },       // 1 bit lsb in byte 1, and 1 bit msb in byte 0 ('index' 1)
   
    { .lsb=8, .size=9, .index=0, .comp = 0xff },       // all 9 bits set ('index' 0)
    { .lsb=8, .size=9, .index=8, .comp = 0x01 },       // all 9 bits set ('index' 1)

    { .lsb=16, .size=10, .index=0, .comp = 0x80 },     
    { .lsb=16, .size=10, .index=8, .comp = 0xff },     
    { .lsb=16, .size=10, .index=16, .comp = 0x01 },     

    { .lsb=17, .size=11, .index=0, .comp = 0x80 },     
    { .lsb=17, .size=11, .index=8, .comp = 0xff },     
    { .lsb=17, .size=11, .index=16, .comp = 0x03 },     

    { .lsb=18, .size=12, .index=0, .comp = 0x80 },     
    { .lsb=18, .size=12, .index=8, .comp = 0xff },     
    { .lsb=18, .size=12, .index=16, .comp = 0x07 },     

    { .lsb=26, .size=8, .index=0, .comp = 0x00 },     
    { .lsb=26, .size=8, .index=8, .comp = 0x00 },     
    { .lsb=26, .size=8, .index=16, .comp = 0xf8 },     
    { .lsb=26, .size=8, .index=24, .comp = 0x07 },     

    { .lsb=26, .size=20, .index=0, .comp = 0x80 },     
    { .lsb=26, .size=20, .index=8, .comp = 0xff },     
    { .lsb=26, .size=20, .index=16, .comp = 0xff },     
    { .lsb=26, .size=20, .index=24, .comp = 0x07 },     

};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static int test_all_mask(const int max) {
    int _ret=0;
    uint8_t comp=-1;
    
    for(int i=0; i<max; i++) {
        fprintf(stderr, "\nloop %02d: ", i);
        comp = dm_compute_mask_shift8(data_mask_g[i].lsb, data_mask_g[i].size, data_mask_g[i].index);
        if(comp!=data_mask_g[i].comp) {
            fprintf(stderr, KRED "error code mismatch" KNRM ", expected(0x%02x), current(0x%02x)\n", data_mask_g[i].comp, comp);
            _ret=1;
        }
        else {
            fprintf(stderr, KGRN "output correct" KNRM ", value(0x%02x)\n", comp);
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
