
#include <stdio.h>
#include <string.h>

#include "private/data_multiplexer.h"

#define KNRM  "\e[0m"
#define KRED  "\e[0;31m"
#define KGRN  "\e[0;32m"
#define KYLW  "\e[0;33m"

typedef struct {
    const uint8_t* i_val;   // default value
    const uint8_t* o_val;   // default value
    const uint8_t* comp;   // default value
    uint8_t pos; 
    uint8_t i_sz; 
    uint8_t o_sz; 
} test_data_t;

static const uint8_t input1_val[] = {0xa3, 0x5b};
static uint8_t output1_val[] = {0xff, 0xff, 0xff};
static const uint8_t output1_comp[] = {0xfa, 0x35, 0xbf};

static const uint8_t input2_val[] = {0x02};
static uint8_t output2_val[] = {0x3f, 0xf5};
static const uint8_t output2_comp[] = {0x3f, 0xb5};

static const uint8_t input3_val[] = {0x01, 0x72};
static uint8_t output3_val[] = {0xff, 0xff, 0xff, 0xff};
static const uint8_t output3_comp[] = {0xff, 0xf5, 0xcb, 0xff};

static const uint8_t input4_val[] = {0x25, 0x37, 0xcd};
static uint8_t output4_val[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static const uint8_t output4_comp[] = {0xff, 0xff, 0xff, 0xa5, 0x37, 0xcd, 0xff, 0xff};

static const uint8_t input5_val[] = {0x00};
static uint8_t output5_val[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static const uint8_t output5_comp[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff};

static const uint8_t input6_val[] = {0x05};
static uint8_t output6_val[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint8_t output6_comp[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00 };

static const test_data_t data_mask_g[] = {
    { .i_val=input1_val, .o_val=output1_val, .comp=output1_comp, .i_sz=16, .o_sz=24, .pos=4},
    { .i_val=input2_val, .o_val=output2_val, .comp=output2_comp, .i_sz=2, .o_sz=14, .pos=6},
    { .i_val=input3_val, .o_val=output3_val, .comp=output3_comp, .i_sz=10, .o_sz=30, .pos=10},
    { .i_val=input4_val, .o_val=output4_val, .comp=output4_comp, .i_sz=23, .o_sz=64, .pos=16},
    { .i_val=input5_val, .o_val=output5_val, .comp=output5_comp, .i_sz=3, .o_sz=64, .pos=12},
    { .i_val=input6_val, .o_val=output6_val, .comp=output6_comp, .i_sz=3, .o_sz=64, .pos=12},
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static int test_all_mask(const int max, const unsigned lsb) {
    int _ret=0;
    
    for(int i=0; i<max; i++) {
        fprintf(stderr, "\nloop %02d: ", i);
        if(lsb)
            dm_set_data8_lsb((void*)data_mask_g[i].o_val, data_mask_g[i].o_sz, data_mask_g[i].pos, data_mask_g[i].i_sz, data_mask_g[i].i_val);
        else
            dm_set_data8_msb((void*)data_mask_g[i].o_val, data_mask_g[i].o_sz, data_mask_g[i].o_sz-data_mask_g[i].pos-data_mask_g[i].i_sz, data_mask_g[i].i_sz, data_mask_g[i].i_val);
        
        size_t sz=dm_get_nb_bytes(data_mask_g[i].o_sz);
        // fprintf(stderr, KYLW "sz comp (%d)\n" KNRM, sz);
        if(memcmp(data_mask_g[i].o_val, data_mask_g[i].comp, sz)) {
            fprintf(stderr, KRED "error code mismatch, "  KNRM "\nexpected(");
            for(int j=0; j<(int)sz; j++) 
                fprintf(stderr, "0x%02x, ", data_mask_g[i].comp[j]);
            fprintf(stderr, "\e[2D), \ncurrent (");
            for(int j=0; j<(int)sz; j++) 
                fprintf(stderr, "0x%02x, ", data_mask_g[i].o_val[j]);
            fprintf(stderr, "\e[2D)\n");
            _ret=1;
        }
        else {
            fprintf(stderr, KGRN "output correct\n" KNRM);
        }
    }
    
    return _ret;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main(int ac, char **av) {
    int _ret=0;
    int max=0;
    int lsb=1;
    
    if(ac>1)
        lsb=0;
    
    max=sizeof(data_mask_g)/sizeof(test_data_t);
    test_all_mask(max, lsb);
    
    return _ret;
}
