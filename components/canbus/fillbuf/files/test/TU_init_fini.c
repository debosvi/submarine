/* ISC license. */

#include <stdio.h>

#include <s6canbus/s6canbus.h>
#include <private/fillbuf_p.h>

#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/Automated.h>

static int init_suite_success(void) { return 0; }
static int clean_suite_success(void) { return 0; }

static void test_init(void) {
    int r=0;
    int i=0;
   
    r=s6cb_fillbuf_init();
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check init values
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 0);
   
    for(i=0; i<S6CANBUS_FILLBUF_MAX_IDS; i++) {
        s6cb_fillbuf_data_t *p=&s6cb_fillbuf_storage_data.d[i];
        CU_PASS("loop inside s6cb_fillbuf_storage_data")
        CU_ASSERT_EQUAL(p->id, S6CANBUS_ID_INVALID);
        CU_ASSERT_EQUAL(p->buf, 0);
        CU_ASSERT_EQUAL(p->size, 0);
   }
}

static void test_fini(void) {
    int r=0;
    int i=0;
   
    r=s6cb_fillbuf_fini();
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check init values
    CU_ASSERT_EQUAL(s6cb_fillbuf_storage_data.n, 0);
   
    for(i=0; i<S6CANBUS_FILLBUF_MAX_IDS; i++) {
        s6cb_fillbuf_data_t *p=&s6cb_fillbuf_storage_data.d[i];
        CU_PASS("loop inside s6cb_fillbuf_storage_data")
        CU_ASSERT_EQUAL(p->id, S6CANBUS_ID_INVALID);
        CU_ASSERT_EQUAL(p->buf, 0);
        CU_ASSERT_EQUAL(p->size, 0);
   }
}

int main(void) {
    
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("'init' and 'fini'", init_suite_success, clean_suite_success);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if( (NULL == CU_add_test(pSuite, "Test s6cb_fillbuf_init", test_init)) ||
        (NULL == CU_add_test(pSuite, "Test s6cb_fillbuf_fini", test_fini))
       ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the automated interface */
    CU_set_output_filename("TU_fillbuf_init_fini");
    CU_automated_run_tests();
    CU_list_tests_to_file();

    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
