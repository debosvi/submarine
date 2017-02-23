
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <skalibs/stralloc.h>
#include <skalibs/buffer.h>
#include <skalibs/iopause.h>

#include "test_binn.h"

#define MAX_ALLOC_CHUNCK    (1024)
#define MAX_ALLOCATED       (10)

static char output_s_g[MAX_ALLOC_CHUNCK];
static buffer output_b_g = BUFFER_ZERO;

static char input_s_g[MAX_ALLOC_CHUNCK];
static buffer input_b_g = BUFFER_ZERO;

static stralloc input_sa_g = STRALLOC_ZERO;

static void die(const char const *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

static int parse_string(char* json) {
    int _ret=-1;
    binn_t head=BINN_INVALID;
    
    fprintf(stderr, "parse string (%s)\n", json);
    _ret=json_to_binn(json, &head);
    
    if(_ret<0)
        fprintf(stderr, "ERROR: parsing impossible\n");
    else if(!_ret)
        fprintf(stderr, "WARNING: parsing incomplete\n");
    else {
        fprintf(stderr, "SUCCESS: parsing complete\n");
        binn_free(head);
    }
    
    return _ret;    
}
    
static const char *complete_str="{ \"cmd\": \"test\", \"data\": [ 0, 1, 2, 3] }      { \"titi\": \"toto\", \"vals\": [ 0, 1, 2, 3] }  [ 10, 11, 12, 13] ";
static char *p_str=0;
static int nb_error=0;

///////////////////////////////////////////////////////////////////////////////
int main(int ac, char** av) {
    int _ret=0;
    int p[2] = {0};
    tain_t deadline;
    
    (void)ac;
    (void)av;
    
    pipe(&p[0]);
    stralloc_ready(&input_sa_g, MAX_ALLOC_CHUNCK);
    buffer_init(&output_b_g, buffer_write, p[1], output_s_g, MAX_ALLOC_CHUNCK);
    buffer_init(&input_b_g, buffer_read, p[0], input_s_g, MAX_ALLOC_CHUNCK);
        
    tain_now_g();
    tain_addsec_g(&deadline, 1);    
    p_str=(char*)complete_str;
    
    while(1) {
        iopause_fd x[2];
        int r=-1;
        
        x[0].fd = buffer_fd(&output_b_g);
        x[0].events = (buffer_iswritable(&output_b_g)?IOPAUSE_WRITE:0);
        x[1].fd = buffer_fd(&input_b_g);
        x[1].events = IOPAUSE_READ;        
        
        r=iopause_g(x, 2, &deadline);
        if(r<0) break;
        else if(!r) {
            
            int max=rand()%16;
            int count=max;
            // fprintf(stderr, "write max (%d)\n", max);
            while(count>0) {
                // fprintf(stderr, "string (%s)\n", p_str);
                int l=strlen(p_str);
                int l2=(l>count?count:l);
                // fprintf(stderr, "write length(%d), loop (%d), count(%d)\n", l, l2, count);
                buffer_putallnoflush(&output_b_g, p_str, l2);
                if(l<count) {
                    p_str=(char*)complete_str;
                }
                else { 
                    p_str+=l2;  
                }

                count-=l2;
                
            }
            deadline=STAMP;
            deadline.nano+=1000*1000*100;                
        }
        else if(x[0].revents&IOPAUSE_WRITE) {
            buffer_flush(&output_b_g);
        }
        else if(x[1].revents&IOPAUSE_READ) {
            char s[256];
            unsigned int lg=0;
            int got=0;
            lg=buffer_fill(&input_b_g);
            if(lg>256) lg=256;
            
            lg=buffer_get(&input_b_g, s, lg);
            stralloc_catb(&input_sa_g, s, lg);
            input_sa_g.s[input_sa_g.len]=0;
            
            got=parse_string(input_sa_g.s);
            if(got<0) {
                if(nb_error++>=25) break;
            }
            else {
                if(got<(int)input_sa_g.len) {
                    buffer_unget(&input_b_g, input_sa_g.len-got);
                }

                nb_error=0;
                input_sa_g.len=0;
            }
        }
        
    }
    
    binn_term();
    return 0;
}
