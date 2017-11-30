/* ISC license. */

#include <stdio.h>

#include <s6canbus/s6canbus.h>
#include <private/fillbuf_p.h>

#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/Automated.h>

#define MSG1_SIZE   12
s6canbus_id_t id1=0x1234;
char msg1[MSG1_SIZE];

static int init_suite(void) { 
    s6cb_fillbuf_init(); 
    s6cb_fillbuf_register_id(id1, msg1, MSG1_SIZE); 
    memset(msg1, 0, MSG1_SIZE);
    return 0; 
}

static int clean_suite(void) { 
    s6cb_fillbuf_fini(); 
    s6cb_fillbuf_unregister_id(id1); 
    return 0; 
}

static void test_valid_defines(void) { 
    CU_ASSERT(S6CANBUS_FILLBUF_MAX_IDS>1); 
}

static void test_reset(void) {
    int r=0;
    int i=0;
    s6cb_fillbuf_data_t *p=0;
    
    // check 1st element
    p=&s6cb_fillbuf_storage_data.d[0];
    CU_ASSERT_EQUAL(p->id, id1);
    CU_ASSERT_EQUAL(p->buf, msg1);
    CU_ASSERT_EQUAL(p->size, MSG1_SIZE);
    
    // insert id1
    r=s6cb_fillbuf_reset_id(id1);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check buffer really erased
    for(; i<MSG1_SIZE; i++) {
        unsigned char *buf=(unsigned char*)p->buf;
        CU_ASSERT(buf[i]==S6CANBUS_FILLBUF_RESET_PATTERN);
    }
}

static void test_fill(void) {
}

int main(void) {
    
    CU_pSuite pSuite = NULL;
    
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("'register' and 'unregister basic'", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    if( (NULL == CU_add_test(pSuite, "Test valid defines", test_valid_defines)) ||
        (NULL == CU_add_test(pSuite, "Test s6cb_fillbuf_reset_id", test_reset)) ||
        (NULL == CU_add_test(pSuite, "Test s6cb_fillbuf_fill_id", test_fill))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* Run all tests using the automated interface */
    CU_set_output_filename("TU_fillbuf_reset_fill");
    CU_automated_run_tests();
    CU_list_tests_to_file();
    
    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
