
#ifndef __PRIVATE_DAEMON_H__
#define __PRIVATE_DAEMON_H__

#include <netinet/in.h>

#include <skalibs/strerr2.h>
#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>
#include <skalibs/selfpipe.h>

// 
#define SERVER_PORT     (29536)
#define BCAST_PORT      (42000)

extern char *iface_str;
extern unsigned int loop_cont_g;

extern void determine_address(struct in_addr* i_addr);
extern void determine_address_bcast(struct in_addr* i_addr);
extern int init_bcast_fd(void);
extern int init_server_fd(void);
extern int init_sig_fd(void);

extern void handle_signals(void);
extern int handle_accept(int fd);
extern int handle_bcast_send(int fd);
extern int handle_bcast_recv(char *buf, unsigned int len);


extern stralloc beacon_sa_g;

// CAN client state
typedef enum {
    STATE_NO_BUS=0,
    STATE_INIT,
    STATE_OPEN,
    STATE_BCM,
    STATE_RAW,
    STATE_SHUTDOWN,
    STATE_CONTROL,
    STATE_ISOTP,
    STATE_COUNT
} can_state_t;

// client server mode connection
typedef enum {
    MODE_RAW=0,
    MODE_BCM,
    MODE_ISOTP,
    MODE_COUNT
} canio_mode_t;

// CAN devices
#define CANDEV_NAMELG   (16)
#define CANDEV_MAX      (8)
typedef struct candev_s candev_t, *candev_t_ref ;
struct candev_s {
    unsigned int  xindex ;          /* x array index */
    int     fd;                     /* device fd */
    int     open;                   /* current countof opening */
    char    dname[CANDEV_NAMELG];    /* device name */
};
#define CANDEV_ZERO { .xindex=CANDEV_MAX, .fd = -1, .open=0, .dname="unknwown" }

extern candev_t candev_g[CANDEV_MAX];
extern unsigned int candev_count_g;

extern int add_candev(char *name);
extern int handle_candev(candev_t *item);

// CAN I/O definitions
#define CANIO_MAXCONCURRENCY    (64)
#define CANIO_INBUF_MAX         (128)
#define CANIO_OUTBUF_MAX        (256)
#define CANIO_FD_SERVER         (0)
#define CANIO_FD_CLIENT         (1)

typedef struct canio_s canio_t, *canio_t_ref ;
struct canio_s {
    char            dname[CANDEV_NAMELG];
    char*           ai;             /* allocated in array */
    char*           ao;             /* allocated out array */
    unsigned int    xindex ;        /* x array index */
    int             type;           /* CANIO_FD_SERVER or CANIO_FD_CLIENT */
    uint32_t        ip;
    uint16_t        port;
    can_state_t     state;          /* client state */
    buffer_t        in;
    buffer_t        out;
    int             nb_error;
};
#define CANIO_ZERO { .dname= {0}, .xindex = CANIO_MAXCONCURRENCY, .type=CANIO_FD_SERVER,  \
    .ai=0, .ao=0, .in = BUFFER_ZERO, .out = BUFFER_ZERO,                    \
    .ip=0, .port=0, .state=STATE_NO_BUS, .nb_error=0 }

extern canio_t canio_g[CANIO_MAXCONCURRENCY];
extern unsigned int canio_count_g;

extern int handle_client(canio_t *io, char *buf, unsigned int len);

extern void add_canio_fd(const int fd);
extern void add_canio_ip(const uint32_t ip, const uint16_t port, const char* const dname);
extern void remove_canio_idx(const unsigned int i);
extern void remove_canio_ptr(canio_t *io);


#endif // __PRIVATE_DAEMON_H__
