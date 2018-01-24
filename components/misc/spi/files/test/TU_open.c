/* ISC license. */

#include <stdio.h>

#include <private/spi_p.h>

#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/Automated.h>

static int init_suite_success(void) { return 0; }
static int clean_suite_success(void) { return 0; }

static void test_boz_spi_init(void) {
    int i=0;
    spi_error_t r=boz_spi_init();
    
    CU_ASSERT_EQUAL(r, SPI_ERROR_NONE);
    
    for(; i<BOZ_SPI_MAX_ITF; i++) {
        spi_itf_elem_t *p=&spi_itf_elem_storage_g[i];
        CU_ASSERT_EQUAL(memcmp(p, &spi_itf_elem_zero, sizeof(spi_itf_elem_t)), 0);
    }
}

static void test_boz_spi_fini(void) {
    int i=0;
    spi_error_t r=boz_spi_fini();
    
    CU_ASSERT_EQUAL(r, SPI_ERROR_NONE);
    
    for(; i<BOZ_SPI_MAX_ITF; i++) {
        spi_itf_elem_t *p=&spi_itf_elem_storage_g[i];
        CU_ASSERT_EQUAL(memcmp(p, &spi_itf_elem_zero, sizeof(spi_itf_elem_t)), 0);
    }
}

static void test_boz_spi_open_arg_spi(void) {
    spi_error_t r;
    
    r=boz_spi_open(0,0,0);
    CU_ASSERT_EQUAL(r, SPI_ERROR_BAD_ARG);
}

static void test_boz_spi_open_arg_itf(void) {
    spi_error_t r;
    spi_t l_spi=SPI_INVALID_VALUE;
    
    r=boz_spi_open(&l_spi, 0, 0);
    CU_ASSERT_EQUAL(r, SPI_ERROR_ITF);
    CU_ASSERT_EQUAL(l_spi, SPI_INVALID_VALUE);
}

static void test_boz_spi_open_arg_clock(void) {
    spi_error_t r;
    spi_t l_spi=SPI_INVALID_VALUE;
    
    r=boz_spi_open(&l_spi, 1, 0);
    CU_ASSERT_EQUAL(r, SPI_ERROR_RANGE);
    CU_ASSERT_EQUAL(l_spi, SPI_INVALID_VALUE);
}

static void test_boz_spi_open_over_itf(void) {
    spi_error_t r;
    spi_t l_spi=SPI_INVALID_VALUE;
    
    // open 1st time
    r=boz_spi_open(&l_spi, 1, 8);
    CU_ASSERT_EQUAL(r, SPI_ERROR_NONE);
    CU_ASSERT_EQUAL(l_spi, 0);
    
    // open 2nd time
    r=boz_spi_open(&l_spi, 1, 8);
    CU_ASSERT_EQUAL(r, SPI_ERROR_ALREADY);
    CU_ASSERT_EQUAL(l_spi, SPI_INVALID_VALUE);
    
    // open other itf
    r=boz_spi_open(&l_spi, 2, 8);
    CU_ASSERT_EQUAL(r, SPI_ERROR_NONE);
    CU_ASSERT_EQUAL(l_spi, 1);
}

static void test_boz_spi_open_over_clock(void) {
    spi_error_t r;
    spi_t l_spi=SPI_INVALID_VALUE;
    
    // open 1st time
    r=boz_spi_open(&l_spi, 3, 8);
    CU_ASSERT_EQUAL(r, SPI_ERROR_NONE);
    CU_ASSERT_EQUAL(l_spi, 2);
    
    // open 2nd time
    r=boz_spi_open(&l_spi, 4, 16);
    CU_ASSERT_EQUAL(r, SPI_ERROR_ITF);
    CU_ASSERT_EQUAL(l_spi, SPI_INVALID_VALUE);
}

int main(void) {
    
    CU_pSuite pSuite = NULL;
    
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("SPI boz_spi_open, args", init_suite_success, clean_suite_success);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    if( (NULL == CU_add_test(pSuite, "Test 'boz_spi_init'", test_boz_spi_init)) ||
        (NULL == CU_add_test(pSuite, "Test 'boz_spi_open', arg 'spi'", test_boz_spi_open_arg_spi)) ||
        (NULL == CU_add_test(pSuite, "Test 'boz_spi_open', arg 'itf'", test_boz_spi_open_arg_itf)) ||
        (NULL == CU_add_test(pSuite, "Test 'boz_spi_open', arg 'clock'", test_boz_spi_open_arg_clock)) ||
        (NULL == CU_add_test(pSuite, "Test 'boz_spi_fini'", test_boz_spi_fini))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("SPI boz_spi_open, nominal", init_suite_success, clean_suite_success);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    if( (NULL == CU_add_test(pSuite, "Test 'boz_spi_init'", test_boz_spi_init)) ||
        (NULL == CU_add_test(pSuite, "Test 'boz_spi_open', over itf'", test_boz_spi_open_over_itf)) ||
        (NULL == CU_add_test(pSuite, "Test 'boz_spi_open', over 'clock'", test_boz_spi_open_over_clock)) ||
        (NULL == CU_add_test(pSuite, "Test 'boz_spi_fini'", test_boz_spi_fini))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* Run all tests using the automated interface */
    CU_set_output_filename("TU_spi_open");
    CU_automated_run_tests();
    CU_list_tests_to_file();
    
    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
