
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test_binn.h"

static char global_buffer[1024];

static void die(const char const *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

static int parse_string(char* json) {
    int _ret=-1;
    binn_t head=BINN_INVALID;
    
    strcat(global_buffer, json);

    fprintf(stderr, "parse string (%s)\n", global_buffer);
    _ret=json_to_binn(global_buffer, &head);
    
    if(_ret<0)
        fprintf(stderr, "ERROR: parsing impossible\n");
    else if(!_ret)
        fprintf(stderr, "WARNING: parsing incomplete\n");
    else {
        fprintf(stderr, "SUCCESS: parsing complete\n");
        memcpy(global_buffer, global_buffer+_ret, 1204-_ret);
        global_buffer[_ret]=0;
        binn_free(head);
    }
    
    return _ret;    
}
    
#define MAX_LOOP    (5)
#define MACRO_PERFORM(str)      _ret=0; while(_ret++<MAX_LOOP) { fprintf(stderr, "loop(%d)\n", _ret); if(parse_string((char*)str)>0) break; } ;   
// #define MACRO_PERFORM(str)      parse_string((char*)str);   

///////////////////////////////////////////////////////////////////////////////
int main(int ac, char** av) {
    const char *complete_str="{ \"cmd\": \"test\", \"data\": [ 0, 1, 2, 3] }";
    const char *complete_and_partial_str="{ \"cmd\": \"test\", \"data\": [ 0, 1, 2, 3] }    { \"titi\": \"toto\", \"d";
    const char *end_partial_str="ata\": [ 0, 1, 2, 3] }  ";
    const char *complete_str2="[ 0, 1, 2, 3]   ";
    const char *complete_and_partial_str2="{ \"cmd\": \"test\", \"data\": [ 0, 1, 2, 3] }                [ 0, 1, ";
    const char *end_partial_str2="12, 2, 3]  ";
    int _ret=0;
    
    (void)ac;
    (void)av;
    
    MACRO_PERFORM(complete_str)
    MACRO_PERFORM(complete_and_partial_str)
    MACRO_PERFORM(end_partial_str)

    
    MACRO_PERFORM(complete_str2)
    MACRO_PERFORM(complete_and_partial_str2)
    MACRO_PERFORM(end_partial_str2)
    MACRO_PERFORM("           ")
    
    binn_term();
    return 0;
}
