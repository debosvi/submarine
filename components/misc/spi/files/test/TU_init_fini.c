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

int main(void) {
    
    CU_pSuite pSuite = NULL;
    
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("SPI init fini", init_suite_success, clean_suite_success);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    if( (NULL == CU_add_test(pSuite, "Test 'boz_spi_init'", test_boz_spi_init)) ||
        (NULL == CU_add_test(pSuite, "Test 'boz_spi_fini'", test_boz_spi_fini))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* Run all tests using the automated interface */
    CU_set_output_filename("TU_spi_init_fini");
    CU_automated_run_tests();
    CU_list_tests_to_file();
    
    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
