
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test_binn.h"

static void die(const char const *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

///////////////////////////////////////////////////////////////////////////////
#define INIT_TEST_BASIC(name,type,value, size)           			\
        int _ret_##name=0;									\
	type v_##name[size];								\
	type *rv_##name=0;									\
	unsigned int  rs_##name=0;									\
	binn_t b_##name=binn_##name(&v_##name[0], size);                     \
    if(b_##name==BINN_INVALID)                              \
        die("Unable to create binn type ##type");           \
    fprintf(stderr, "binn type %s created\n", #type);		\
	if(binn_to_##name(b_##name, &rv_##name, &rs_##name))					\
		die("Get value fails for type ##type");           	\
	if(size!=rs_##name)									\
		fprintf(stderr, "Size differs for type %s\n", #type);           	\
    fprintf(stderr, "binn sizes match for type %s\n", #type);		\
	for(int i=0; i<size; i++)							\
		if(rv_##name[i]!=v_##name[i])		\
			_ret_##name=1;					\
	if(_ret_##name)				\
		fprintf(stderr, "Value differs for type %s\n", #type);           	\
    	else 				\
		fprintf(stderr, "binn values match for type %s\n", #type);	

#define END_TEST_BASIC(name)	                            \
    binn_free(b_##name);                            
                        
    
///////////////////////////////////////////////////////////////////////////////
int main(int ac, char** av) {
	(void)ac;
	(void)av;

	INIT_TEST_BASIC(blob, char, 0xA5, 65)
	END_TEST_BASIC(blob)
    
	binn_term();
	return 0;
}
