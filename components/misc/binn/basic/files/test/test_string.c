
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test_binn.h"

static void die(const char const *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

///////////////////////////////////////////////////////////////////////////////
#define INIT_TEST_BASIC(name,type,value)           			\
    const type v_##name=value;								\
	type r_##name=0;										\
	binn_t b_##name=binn_##name(value);                     \
    if(b_##name==BINN_INVALID)                              \
        die("Unable to create binn type ##type");           \
    fprintf(stderr, "binn type %s created\n", #type);		\
	if(binn_to_##name(b_##name, &r_##name))					\
		die("Get value fails for type ##type");           	\
	if(strcmp(r_##name, v_##name))									\
		fprintf(stderr, "Value differs for type %s\n", #type);           	\
    fprintf(stderr, "binn values match for type %s\n", #type);	

#define END_TEST_BASIC(name)	                            \
    binn_free(b_##name);                            
                        
    
///////////////////////////////////////////////////////////////////////////////
int main(int ac, char** av) {
	(void)ac;
	(void)av;

	INIT_TEST_BASIC(string, char*, "test string")
	END_TEST_BASIC(string)
    
	binn_term();
	return 0;
}
