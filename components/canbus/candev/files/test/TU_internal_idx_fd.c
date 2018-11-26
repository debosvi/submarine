/* ISC license. */

#include <stdio.h>

#include <s6canbus/errors.h>
#include <private/candev_p.h>

#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/Automated.h>

static int init_suite_success(void) { return 0; }
static int clean_suite_success(void) { return 0; }

#if S6CANBUS_CANDEV_FAKE
static void test_valid_init(void) {
    CU_ASSERT_EQUAL(gensetdyn_n(&s6cb_candev_internal_data_g), 0);
}
#endif

static void test_open(void) {
    int r;
    r=s6cb_candev_open("/dev/can0");
    CU_ASSERT_EQUAL(r, 0);
    r=s6cb_candev_open("/dev/can1");
    CU_ASSERT_EQUAL(r, 1);
}

#if S6CANBUS_CANDEV_FAKE
static void test_idx(void) {
    unsigned i;
    
    i=s6cb_candev_internal_idx_fd(0);
    CU_ASSERT_EQUAL(i, 0);    
    
    i=s6cb_candev_internal_idx_fd(1);
    CU_ASSERT_EQUAL(i, 1);    
    
    i=s6cb_candev_internal_idx_fd(2);
    CU_ASSERT_EQUAL(i, -1);    
}
#endif

int main(void) {
    
    CU_pSuite pSuite = NULL;
    
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("CANDEV internal get storage index from fd", init_suite_success, clean_suite_success);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    if(
#if S6CANBUS_CANDEV_FAKE
        (NULL == CU_add_test(pSuite, "Test valid init", test_valid_init)) ||
#endif
        (NULL == CU_add_test(pSuite, "Test s6cb_candev_open", test_open)) 
#if S6CANBUS_CANDEV_FAKE
        || (NULL == CU_add_test(pSuite, "Test s6cb_candev_idx", test_idx)) 
#endif
        
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* Run all tests using the automated interface */
    CU_set_output_filename("TU_candev_internal_idx_fd");
    CU_automated_run_tests();
    CU_list_tests_to_file();
    
    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
