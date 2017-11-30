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

#define MSG2_SIZE   48
s6canbus_id_t id2=0x3456;
char msg2[MSG2_SIZE];

static int init_suite(void) { s6cb_fillbuf_init(); return 0; }
static int clean_suite(void) { s6cb_fillbuf_fini(); return 0; }

static void test_register(void) {
    int r=0;
    s6cb_fillbuf_data_t *p=0;
    
    // insert id1
    r=s6cb_fillbuf_register_id(id1, msg1, MSG1_SIZE);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check nb ids 
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 1);
   
    // check 1st element
    p=&s6cb_fillbuf_storage_data.d[0];
    CU_ASSERT_EQUAL(p->id, id1);
    CU_ASSERT_EQUAL(p->buf, msg1);
    CU_ASSERT_EQUAL(p->size, MSG1_SIZE);
    
    // insert id2
    r=s6cb_fillbuf_register_id(id2, msg2, MSG2_SIZE);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check nb ids 
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 2);
   
    // check 2nd element
    p=&s6cb_fillbuf_storage_data.d[1];
    CU_ASSERT_EQUAL(p->id, id2);
    CU_ASSERT_EQUAL(p->buf, msg2);
    CU_ASSERT_EQUAL(p->size, MSG2_SIZE);
    
    // insert id2 again, must fail
    r=s6cb_fillbuf_register_id(id2, msg2, MSG2_SIZE);
    CU_ASSERT_NOT_EQUAL(r, S6CANBUS_ERROR_NONE);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_ALREADY);
    
    // insert id1 again, must fail
    r=s6cb_fillbuf_register_id(id1, msg1, MSG1_SIZE);
    CU_ASSERT_NOT_EQUAL(r, S6CANBUS_ERROR_NONE);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_ALREADY);
}

static void test_unregister(void) {
    int r=0;
    s6cb_fillbuf_data_t *p=0;
    
    // remove id1
    r=s6cb_fillbuf_unregister_id(id1);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);

    // check nb ids 
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 1);
    
    // remove id1 again, must fail
    r=s6cb_fillbuf_unregister_id(id1);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NOTFOUND);
    CU_ASSERT_NOT_EQUAL(r, S6CANBUS_ERROR_NONE);

    // check nb ids 
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 1);
   
    // check 1st element
    p=&s6cb_fillbuf_storage_data.d[0];
    CU_ASSERT_EQUAL(p->id, id2);
    CU_ASSERT_EQUAL(p->buf, msg2);
    CU_ASSERT_EQUAL(p->size, MSG2_SIZE);
   
    // check 2nd element
    p=&s6cb_fillbuf_storage_data.d[1];
    CU_ASSERT_EQUAL(p->id, S6CANBUS_ID_INVALID);
    CU_ASSERT_EQUAL(p->buf, 0);
    CU_ASSERT_EQUAL(p->size, 0);
}

int main(void) {
    
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("'register' and 'unregister'", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

#if 1
    /* add the tests to the suite */
    if( (NULL == CU_add_test(pSuite, "Test s6cb_fillbuf_register_id", test_register)) ||
        (NULL == CU_add_test(pSuite, "Test s6cb_fillbuf_unregister_id", test_unregister))
       ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
#endif

    /* Run all tests using the automated interface */
    CU_set_output_filename("TU_fillbuf_register_unregister");
    CU_automated_run_tests();
    CU_list_tests_to_file();

    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
