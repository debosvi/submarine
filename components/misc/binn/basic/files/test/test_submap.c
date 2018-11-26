
#include <stdlib.h>
#include <stdio.h>

#include "test_binn.h"

static void die(const char const *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

///////////////////////////////////////////////////////////////////////////////
int main(int ac, char** av) {
    const int8_t i8=-123;
    const uint16_t u16=654;
	const unsigned int id1=12;
	const unsigned int id2=26;
	int8_t i8_r=0;
	uint16_t u16_r=0;
    (void)ac;
    (void)av;
    
    binn_t sub=binn_map();   
	binn_t bi8=binn_int8(i8);
	binn_t bu16=binn_uint16(u16);

    binn_t bi8_r=BINN_INVALID;   
    binn_t bu16_r=BINN_INVALID;   
    
    fprintf(stderr, "sub (%d)\n", sub);

    fprintf(stderr, "insert int8\n");
    if(binn_map_add_item(sub, id1, bi8))
        die("Unable to add int8 value");  

    fprintf(stderr, "insert uint16\n");
    if(binn_map_add_item(sub, id2, bu16))
        die("Unable to add int8 value");  
    
    fprintf(stderr, "\npouplate success\n");
  
    if(binn_map_get_item(sub, id1, &bi8_r))
        fprintf(stderr, "Unable to get binn item (%d) from sub list\n", id1);
	else if(binn_to_int8(bi8_r, &i8_r))
        fprintf(stderr, "Unable to get value of binn item (%d)\n", id1);
	else if(i8_r!=i8)
        fprintf(stderr, "i8 values differs for binn item (%d), expected (%d), current (%d)\n", id1, i8, i8_r);
    else
		fprintf(stderr, "i8 values matches for binn item (%d), value(%d)\n", id1, i8);
  
    if(binn_map_get_item(sub, id2, &bu16_r))
        fprintf(stderr, "Unable to get binn item (%d) from sub list\n", id2);
	else if(binn_to_uint16(bu16_r, &u16_r))
        fprintf(stderr, "Unable to get value of binn item (%d)\n", id2);
	else if(u16_r!=u16)
        fprintf(stderr, "u16 values differs for binn item (%d), expected (%d), current (%d)\n", id2, u16, u16_r);
    else
		fprintf(stderr, "u16 values matches for binn item (%d), value(%d)\n", id2, u16);

	if(binn_to_int8(bu16_r, &i8_r))
        fprintf(stderr, "Unable to get value of binn item (%d) (normal case)\n", id2);
	
    fprintf(stderr, "%s: SUCCESS\n", __FUNCTION__);
    
    binn_free(sub);
    binn_term();
    return 0;
}
