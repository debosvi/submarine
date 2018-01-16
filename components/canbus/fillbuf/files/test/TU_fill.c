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

static void myfunc(const s6canbus_id_t id, void* own) {
    (void)own;
    fprintf(stderr, "%s: %d\n", __PRETTY_FUNCTION__, id);
}

static int init_suite(void) { 
    s6cb_fillbuf_init(); 
    s6cb_fillbuf_register_id(id1, msg1, MSG1_SIZE, myfunc, &id1); 
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

static void test_fill_args(void) {
    int r=0;
    const unsigned char* fill = (const unsigned char*)"123456";
    s6cb_fillbuf_data_t *p=0;
    
    s6cb_fillbuf_reset_id(id1); 
    
    // check 1st element
    p=&s6cb_fillbuf_storage_data.d[0];
    CU_ASSERT_EQUAL(p->id, id1);
    CU_ASSERT_EQUAL(p->buf, msg1);
    CU_ASSERT_EQUAL(p->size, MSG1_SIZE);
    
    // insert id1
    r=s6cb_fillbuf_fill_id(id1, fill, 4, 0);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_INVAL);
    
    // check buffer really erased
    {
        unsigned char *buf=(unsigned char*)p->buf;
        CU_ASSERT(buf[0]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[1]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[2]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[3]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[4]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[5]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[6]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[7]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[8]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[9]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[10]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[11]==S6CANBUS_FILLBUF_RESET_PATTERN);
    }
}


static void test_fill_partial(void) {
    int r=0;
    const unsigned char* fill = (const unsigned char*)"123456";
    s6cb_fillbuf_data_t *p=0;
    
    s6cb_fillbuf_reset_id(id1); 
    
    // check 1st element
    p=&s6cb_fillbuf_storage_data.d[0];
    CU_ASSERT_EQUAL(p->id, id1);
    CU_ASSERT_EQUAL(p->buf, msg1);
    CU_ASSERT_EQUAL(p->size, MSG1_SIZE);
    
    // insert id1
    r=s6cb_fillbuf_fill_id(id1, fill, 4, 6);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check buffer really erased
    {
        unsigned char *buf=(unsigned char*)p->buf;
        CU_ASSERT(buf[0]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[1]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[2]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[3]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[4]==fill[0]);
        CU_ASSERT(buf[5]==fill[1]);
        CU_ASSERT(buf[6]==fill[2]);
        CU_ASSERT(buf[7]==fill[3]);
        CU_ASSERT(buf[8]==fill[4]);
        CU_ASSERT(buf[9]==fill[5]);
        CU_ASSERT(buf[10]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[11]==S6CANBUS_FILLBUF_RESET_PATTERN);
    }
}

static void test_fill_complete(void) {
    int r=0;
    const unsigned char* fill = (const unsigned char*)"012345678987";
    s6cb_fillbuf_data_t *p=0;

    s6cb_fillbuf_reset_id(id1); 
    
    // check 1st element
    p=&s6cb_fillbuf_storage_data.d[0];
    CU_ASSERT_EQUAL(p->id, id1);
    CU_ASSERT_EQUAL(p->buf, msg1);
    CU_ASSERT_EQUAL(p->size, MSG1_SIZE);
    
    // insert id1
    r=s6cb_fillbuf_fill_id(id1, fill, 0, MSG1_SIZE);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check buffer really erased
    {
        unsigned char *buf=(unsigned char*)p->buf;
        unsigned int i=0;
        for(; i<MSG1_SIZE; i++)
        	CU_ASSERT(buf[i]==fill[i]);
    }
}

static void test_fill_overflow(void) {
    int r=0;
    const unsigned char* fill = (const unsigned char*)"012345678987";
    s6cb_fillbuf_data_t *p=0;

    s6cb_fillbuf_reset_id(id1); 
    
    // check 1st element
    p=&s6cb_fillbuf_storage_data.d[0];
    CU_ASSERT_EQUAL(p->id, id1);
    CU_ASSERT_EQUAL(p->buf, msg1);
    CU_ASSERT_EQUAL(p->size, MSG1_SIZE);
    
    // insert id1
    r=s6cb_fillbuf_fill_id(id1, fill, 1, MSG1_SIZE);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_OVERLAY);
    
    // check buffer really erased
    {
        unsigned char *buf=(unsigned char*)p->buf;
        unsigned int i=0;
        for(; i<MSG1_SIZE; i++)
        	CU_ASSERT(buf[i]==S6CANBUS_FILLBUF_RESET_PATTERN);
    }
}

#ifdef S6CANBUS_FILLBUF_CHECK_FILL_OVERLAY    

static void test_fill_refill(void) {
    int r=0;
    const unsigned char* fill = (const unsigned char*)"123456";
    s6cb_fillbuf_data_t *p=0;

    s6cb_fillbuf_reset_id(id1); 
    
    // check 1st element
    p=&s6cb_fillbuf_storage_data.d[0];
    CU_ASSERT_EQUAL(p->id, id1);
    CU_ASSERT_EQUAL(p->buf, msg1);
    CU_ASSERT_EQUAL(p->size, MSG1_SIZE);
    
    // insert id1
    r=s6cb_fillbuf_fill_id(id1, fill, 4, 6);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_NONE);
    
    // check buffer really erased
    {
        unsigned char *buf=(unsigned char*)p->buf;
        CU_ASSERT(buf[0]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[1]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[2]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[3]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[4]==fill[0]);
        CU_ASSERT(buf[5]==fill[1]);
        CU_ASSERT(buf[6]==fill[2]);
        CU_ASSERT(buf[7]==fill[3]);
        CU_ASSERT(buf[8]==fill[4]);
        CU_ASSERT(buf[9]==fill[5]);
        CU_ASSERT(buf[10]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[11]==S6CANBUS_FILLBUF_RESET_PATTERN);
    }
    
    // insert  again id1
    r=s6cb_fillbuf_fill_id(id1, fill, 6, 1);
    CU_ASSERT_EQUAL(r, S6CANBUS_ERROR_OVERLAY);
    
    // check buffer really erased
    {
        unsigned char *buf=(unsigned char*)p->buf;
        CU_ASSERT(buf[0]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[1]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[2]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[3]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[4]==fill[0]);
        CU_ASSERT(buf[5]==fill[1]);
        CU_ASSERT(buf[6]==fill[2]);
        CU_ASSERT(buf[7]==fill[3]);
        CU_ASSERT(buf[8]==fill[4]);
        CU_ASSERT(buf[9]==fill[5]);
        CU_ASSERT(buf[10]==S6CANBUS_FILLBUF_RESET_PATTERN);
        CU_ASSERT(buf[11]==S6CANBUS_FILLBUF_RESET_PATTERN);
    }
}
#endif

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
        (NULL == CU_add_test(pSuite, "Test fill args", test_fill_args)) ||
        (NULL == CU_add_test(pSuite, "Test fill partial", test_fill_partial)) ||
        (NULL == CU_add_test(pSuite, "Test fill complete", test_fill_complete)) ||
        (NULL == CU_add_test(pSuite, "Test fill overflow", test_fill_overflow))
#ifdef S6CANBUS_FILLBUF_CHECK_FILL_OVERLAY        
		||
        (NULL == CU_add_test(pSuite, "Test fill refill", test_fill_refill))
#endif
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* Run all tests using the automated interface */
    CU_set_output_filename("TU_fillbuf_fill");
    CU_automated_run_tests();
    CU_list_tests_to_file();
    
    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
