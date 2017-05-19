
#include <stdio.h>
#include <string.h>

#include "private/data_multiplexer.h"

typedef struct {
    uint8_t size;
    uint64_t comp;
} test_data_t;

static const test_data_t data_mask_g[] = {
    { .size=0, .comp=0x00 },
    { .size=1, .comp=0x01 },
    { .size=2, .comp=0x03 },
    { .size=3, .comp=0x07 },
    { .size=4, .comp=0x0f },
    { .size=5, .comp=0x1f },
    { .size=6, .comp=0x3f },
    { .size=7, .comp=0x7f },
    { .size=8, .comp=0xff },
    { .size=9, .comp=0x1ff },
    { .size=65, .comp=0x00 },
    { .size=12, .comp=0xfff },
    { .size=19, .comp=0x7ffff },
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static int test_all_mask(const int max) {
    int _ret=0;
    uint64_t comp=-1;
    
    for(int i=0; i<max; i++) {
        fprintf(stderr, "loop %02d: ", i);
        comp = dm_compute_mask64(data_mask_g[i].size);
        if(comp!=data_mask_g[i].comp) {
            fprintf(stderr, "error code mismatch, expected(0x%016x), current(0x%016x)\n", (unsigned int)data_mask_g[i].comp, (unsigned int)comp);
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
