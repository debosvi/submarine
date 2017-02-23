
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
	const char *key1="key1";
	const char *key2="key2";
	int8_t i8_r=0;
	uint16_t u16_r=0;
    (void)ac;
    (void)av;
    
    binn_t sub=binn_object();   
	binn_t bi8=binn_int8(i8);
	binn_t bu16=binn_uint16(u16);

    binn_t bi8_r=BINN_INVALID;   
    binn_t bu16_r=BINN_INVALID;   
    
    fprintf(stderr, "sub (%d)\n", sub);

    fprintf(stderr, "insert int8\n");
    if(binn_object_add_item(sub, key1, bi8))
        die("Unable to add int8 value");  

    fprintf(stderr, "insert uint16\n");
    if(binn_object_add_item(sub, key2, bu16))
        die("Unable to add int8 value");  
    
    fprintf(stderr, "\npouplate success\n");
  
    if(binn_object_get_item(sub, key1, &bi8_r))
        fprintf(stderr, "Unable to get binn item (%s) from sub list\n", key1);
	else if(binn_to_int8(bi8_r, &i8_r))
        fprintf(stderr, "Unable to get value of binn item (%s)\n", key1);
	else if(i8_r!=i8)
        fprintf(stderr, "i8 values differs for binn item (%s), expected (%d), current (%d)\n", key1, i8, i8_r);
    else
		fprintf(stderr, "i8 values matches for binn item (%s), value(%d)\n", key1, i8);
  
    if(binn_object_get_item(sub, key2, &bu16_r))
        fprintf(stderr, "Unable to get binn item (%s) from sub list\n", key2);
	else if(binn_to_uint16(bu16_r, &u16_r))
        fprintf(stderr, "Unable to get value of binn item (%s)\n", key2);
	else if(u16_r!=u16)
        fprintf(stderr, "u16 values differs for binn item (%s), expected (%d), current (%d)\n", key2, u16, u16_r);
    else
		fprintf(stderr, "u16 values matches for binn item (%s), value(%d)\n", key2, u16);

	if(binn_to_int8(bu16_r, &i8_r))
        fprintf(stderr, "Unable to get value of binn item (%s) (normal case)\n", key2);
	
    fprintf(stderr, "%s: SUCCESS\n", __FUNCTION__);
    
    binn_free(sub);
    binn_term();
    return 0;
}
