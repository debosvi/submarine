
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
	int8_t i8_r=0;
	uint16_t u16_r=0;
    (void)ac;
    (void)av;
    
    binn_t sub=binn_list();   
	binn_t bi8=binn_int8(i8);
	binn_t bu16=binn_uint16(u16);

    binn_t bi8_r=BINN_INVALID;   
    binn_t bu16_r=BINN_INVALID;   
    
    fprintf(stderr, "sub (%d)\n", sub);

    fprintf(stderr, "insert int8\n");
    if(binn_list_add_item(sub, bi8))
        die("Unable to add int8 value");  

    fprintf(stderr, "insert uint16\n");
    if(binn_list_add_item(sub, bu16))
        die("Unable to add int8 value");  
    
    fprintf(stderr, "\npouplate success\n");
  
    if(binn_list_get_item(sub, 0, &bi8_r))
        fprintf(stderr, "Unable to get binn item (%d) from sub list\n", 0);
	else if(binn_to_int8(bi8_r, &i8_r))
        fprintf(stderr, "Unable to get value of binn item (%d)\n", 0);
	else if(i8_r!=i8)
        fprintf(stderr, "i8 values differs for binn item (%d), expected (%d), current (%d)\n", 0, i8, i8_r);
    else
		fprintf(stderr, "i8 values matches for binn item (%d), value(%d)\n", 0, i8);
  
    if(binn_list_get_item(sub, 1, &bu16_r))
        fprintf(stderr, "Unable to get binn item (%d) from sub list\n", 1);
	else if(binn_to_uint16(bu16_r, &u16_r))
        fprintf(stderr, "Unable to get value of binn item (%d)\n", 1);
	else if(u16_r!=u16)
        fprintf(stderr, "u16 values differs for binn item (%d), expected (%d), current (%d)\n", 1, u16, u16_r);
    else
		fprintf(stderr, "u16 values matches for binn item (%d), value(%d)\n", 1, u16);

	if(binn_to_int8(bu16_r, &i8_r))
        fprintf(stderr, "Unable to get value of binn item 1 (normal case)\n");
	
    fprintf(stderr, "%s: SUCCESS\n", __FUNCTION__);
    
    binn_free(sub);
    binn_term();
    return 0;
}
