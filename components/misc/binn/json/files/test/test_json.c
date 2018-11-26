
#include <stdlib.h>
#include <stdio.h>

#include "test_binn.h"

static void die(const char const *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

///////////////////////////////////////////////////////////////////////////////
static binn_t build_string(void) {
    binn_t str=binn_string("list content");   

    return str;
}

///////////////////////////////////////////////////////////////////////////////
static binn_t build_list(void) {
    const int8_t i8=-49;
    const uint16_t u16=1234;
	 
    binn_t sub=binn_list();   
	binn_t bi8=binn_int8(i8);
	binn_t bu16=binn_uint16(u16);

    if(binn_list_add_item(sub, bi8))
        die("Unable to add int8 value");  

    if(binn_list_add_item(sub, bu16))
        die("Unable to add int8 value");  

    return sub;
}

///////////////////////////////////////////////////////////////////////////////
static binn_t build_map(void) {
    const int8_t i8=-94;
    const uint16_t u16=4567;
	const unsigned int id1=12;
	const unsigned int id2=26;
 
    binn_t sub=binn_map();   
	binn_t bi8=binn_int8(i8);
	binn_t bu16=binn_uint16(u16);

    if(binn_map_add_item(sub, id1, bi8))
        die("Unable to add int8 value");  

    if(binn_map_add_item(sub, id2, bu16))
        die("Unable to add int8 value");  

    return sub;
}

///////////////////////////////////////////////////////////////////////////////
static binn_t build_object(void) {
    const int8_t i8=-123;
    const uint16_t u16=654;
	const char *key1="key1";
	const char *key2="key2";
 
    binn_t sub=binn_object();   
	binn_t bi8=binn_int8(i8);
	binn_t bu16=binn_uint16(u16);

    if(binn_object_add_item(sub, key1, bi8))
        die("Unable to add int8 value");  

    if(binn_object_add_item(sub, key2, bu16))
        die("Unable to add int8 value");  

    return sub;
}
    
///////////////////////////////////////////////////////////////////////////////
int main(int ac, char** av) {
    const char *sstr="str";
    const char *lstr="lst";
    const char *mstr="map";
    const char *ostr="obj";
    char *json=0;
	(void)ac;
    (void)av;
    
    binn_t head=binn_object();
    fprintf(stderr, "head created\n");

    if(binn_object_add_item(head, lstr, build_list()))
        die("Unable to add list to head");  
    fprintf(stderr, "list created\n");

    if(binn_object_add_item(head, mstr, build_map()))
        die("Unable to add map to head");  
    fprintf(stderr, "map created\n");

    if(binn_object_add_item(head, ostr, build_object()))
        die("Unable to add object to head");  
    fprintf(stderr, "object created\n");

    if(binn_object_add_item(head, sstr, build_string()))
        die("Unable to add string to head");  
    fprintf(stderr, "string created\n");

    json=binn_to_json_str(head);
    fprintf(stderr, "JSON: result (%s)\n", json);

    free(json);
	
    fprintf(stderr, "%s: SUCCESS\n", __FUNCTION__);
    
    binn_free(head);
    
    binn_term();
    return 0;
}
