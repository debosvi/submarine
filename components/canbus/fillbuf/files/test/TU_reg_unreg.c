/* ISC license. */

#include <stdio.h>

#include <s6canbus/errors.h>
#include <s6canbus/fillbuf.h>
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

static void myfunc(const s6canbus_id_t id, void* own) {
    (void)own;
    fprintf(stderr, "%s: %d\n", __PRETTY_FUNCTION__, id);
}

static int init_suite(void) { s6cb_fillbuf_init(); return 0; }
static int clean_suite(void) { s6cb_fillbuf_fini(); return 0; }

static void test_valid_defines(void) { 
    CU_ASSERT(S6CANBUS_FILLBUF_MAX_IDS>2); 
}
    
static void test_register_valid(void) {
    int r=0;
    s6cb_fillbuf_data_t *p=0;
    
    s6cb_fillbuf_reset_all();
    
    // insert id1
    r=s6cb_fillbuf_register_id(id1, msg1, MSG1_SIZE, myfunc, &id1);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check nb ids 
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 1);
    
    // check 1st element
    p=&s6cb_fillbuf_storage_data.d[0];
    CU_ASSERT_EQUAL(p->id, id1);
    CU_ASSERT_EQUAL(p->buf, msg1);
    CU_ASSERT_EQUAL(p->size, MSG1_SIZE);
    CU_ASSERT_EQUAL(p->func, myfunc);
    CU_ASSERT_EQUAL(p->own, &id1);
    
    // insert id2
    r=s6cb_fillbuf_register_id(id2, msg2, MSG2_SIZE, myfunc, &id2);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check nb ids 
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 2);
    
    // check 2nd element
    p=&s6cb_fillbuf_storage_data.d[1];
    CU_ASSERT_EQUAL(p->id, id2);
    CU_ASSERT_EQUAL(p->buf, msg2);
    CU_ASSERT_EQUAL(p->size, MSG2_SIZE);
    CU_ASSERT_EQUAL(p->func, myfunc);
    CU_ASSERT_EQUAL(p->own, &id2);
    
}

static void test_register_twice(void) {
    int r=0;
    
    s6cb_fillbuf_reset_all();
    
    // insert id1
    r=s6cb_fillbuf_register_id(id1, msg1, MSG1_SIZE, myfunc, &id1);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);

    // insert id2
    r=s6cb_fillbuf_register_id(id2, msg2, MSG2_SIZE, myfunc, &id2);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check nb ids 
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 2);
    
    // insert id2 again, must fail
    r=s6cb_fillbuf_register_id(id2, msg2, MSG2_SIZE, myfunc, 0);
    CU_ASSERT_NOT_EQUAL(r, S6CANBUS_ERROR_NONE);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_ALREADY);
    
    // insert id1 again, must fail
    r=s6cb_fillbuf_register_id(id1, msg1, MSG1_SIZE, myfunc, 0);
    CU_ASSERT_NOT_EQUAL(r, S6CANBUS_ERROR_NONE);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_ALREADY);
}

static void test_unregister_valid(void) {
    int r=0;
    s6cb_fillbuf_data_t *p=0;
    
    s6cb_fillbuf_reset_all();
   
    // insert id1
    r=s6cb_fillbuf_register_id(id1, msg1, MSG1_SIZE, myfunc, &id1);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // insert id2
    r=s6cb_fillbuf_register_id(id2, msg2, MSG2_SIZE, myfunc, &id2);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);

    // check nb ids 
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 2);

    // remove id1
    r=s6cb_fillbuf_unregister_id(id1);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check nb ids 
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 1);

    // check 1st element
    p=&s6cb_fillbuf_storage_data.d[0];
    CU_ASSERT_EQUAL(p->id, id2);
    CU_ASSERT_EQUAL(p->buf, msg2);
    CU_ASSERT_EQUAL(p->size, MSG2_SIZE);
    CU_ASSERT_EQUAL(p->func, myfunc);
    CU_ASSERT_EQUAL(p->own, &id2);
    
    // check 2nd element
    p=&s6cb_fillbuf_storage_data.d[1];
    CU_ASSERT_EQUAL(p->id, S6CANBUS_ID_INVALID);
    CU_ASSERT_EQUAL(p->buf, 0);
    CU_ASSERT_EQUAL(p->size, 0);
    CU_ASSERT_EQUAL(p->func, 0);
}

static void test_unregister_twice(void) {
    int r=0;

    s6cb_fillbuf_reset_all();
    
    // insert id1
    r=s6cb_fillbuf_register_id(id1, msg1, MSG1_SIZE, myfunc, &id1);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // insert id2
    r=s6cb_fillbuf_register_id(id2, msg2, MSG2_SIZE, myfunc, &id2);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);

    // check nb ids 
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 2);

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
}

static void test_register_limits(void) {
    int r=0;
    int i=0;
    s6cb_fillbuf_data_t *p=0;
    
    for(; i<S6CANBUS_FILLBUF_MAX_IDS; i++) {
        // insert id1 + i
        r=s6cb_fillbuf_register_id(id1+i, msg1, MSG1_SIZE+i, myfunc, &id1);
        CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
        // check nb ids 
        CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, (size_t)i+1);
    
        // check 1st element
        p=&s6cb_fillbuf_storage_data.d[i];
        CU_ASSERT_EQUAL(p->id, id1+i);
        CU_ASSERT_EQUAL(p->buf, msg1);
        CU_ASSERT_EQUAL(p->size, (size_t)MSG1_SIZE+i);
    }
    
    r=s6cb_fillbuf_register_id(id1+i, msg1, MSG1_SIZE+i, myfunc, &id1);
    CU_ASSERT_NOT_EQUAL(r, S6CANBUS_ERROR_NONE);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_FULL);    
}

static void test_unregister_limits(void) {
    int r=0;
    int i=0;
    
    for(; i<S6CANBUS_FILLBUF_MAX_IDS; i++) {
        // remove id1 + i
        r=s6cb_fillbuf_unregister_id(id1+i);
        CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
        
        // check nb ids 
        CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, (size_t)S6CANBUS_FILLBUF_MAX_IDS-1-i);
    }
    
    r=s6cb_fillbuf_unregister_id(id1+i);
    CU_ASSERT_NOT_EQUAL(r, S6CANBUS_ERROR_NONE);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_EMPTY);    
}

int main(void) {
    
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("'s6cb_fillbuf_register_id'", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    if( (NULL == CU_add_test(pSuite, "Test valid defines", test_valid_defines)) ||
        (NULL == CU_add_test(pSuite, "Test register valid id", test_register_valid)) ||
        (NULL == CU_add_test(pSuite, "Test register id twice", test_register_twice))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("'s6cb_fillbuf_register_id'", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    if( (NULL == CU_add_test(pSuite, "Test valid defines", test_valid_defines)) ||
        (NULL == CU_add_test(pSuite, "Test unregister valid id", test_unregister_valid)) ||
        (NULL == CU_add_test(pSuite, "Test unregister id twice", test_unregister_twice)) 
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("'register' and 'unregister limits'", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    if( (NULL == CU_add_test(pSuite, "Test register limits", test_register_limits)) ||
        (NULL == CU_add_test(pSuite, "Test unregister limits", test_unregister_limits))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* Run all tests using the automated interface */
    CU_set_output_filename("TU_fillbuf_reg_unreg");
    CU_automated_run_tests();
    CU_list_tests_to_file();

    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
