
#include <errno.h>

#include <skalibs/uint16.h>
#include <skalibs/buffer.h>
#include <skalibs/strerr2.h>
#include <skalibs/selfpipe.h>
#include <skalibs/sig.h>
#include <skalibs/iopause.h>
#include <skalibs/sgetopt.h>

static int cont=1;
static uint16_t counter=0;
static int verbosity = 0;

#define USAGE "echo_terminal [ -v ]"
#define dieusage() strerr_dieusage(100, USAGE)

static void handle_signals (void)
{
  for (;;)
  {
    switch (selfpipe_read())
    {
      case -1 : strerr_die3x(1, PROG, ": fatal: ", "selfpipe_read");
      case 0 : return ;
      case SIGTERM : cont = 0 ; break ;
      default: strerr_warnw1x("unmanaged signal caught");
    }
  }
}

int main(int ac, char const *const *av) {
	iopause_fd x[2] = { { -1, IOPAUSE_READ, 0 }, { -1, 0, 0 } } ;
	tain_t deadline;
	PROG = "echo_terminal" ;
	
	{
		subgetopt_t l = SUBGETOPT_ZERO ;
		for (;;) {
			int opt = subgetopt_r(ac, av, "v", &l) ;
			if (opt == -1) break ;
			switch (opt) {
				case 'v' : verbosity = 1; break ;
				default : dieusage() ;
			}
		}
		ac -= l.ind ; av += l.ind ;
	}
  
  
	
	x[0].fd = selfpipe_init();
	x[1].fd = buffer_fd(buffer_1);
	
	if (sig_ignore(SIGPIPE) < 0) 
		strerr_diefu1sys(111, "ignore SIGPIPE") ;
	
	{
		sigset_t set ;
		sigemptyset(&set) ;
		sigaddset(&set, SIGTERM) ;
		sigaddset(&set, SIGHUP) ;
		if (selfpipe_trapset(&set) < 0) 
			strerr_diefu1sys(111, "trap signals") ;
	}

	// init stamps
	tain_now_g();
	tain_addsec_g(&deadline, 1);
	
	while(cont) {
		x[1].events = (buffer_iswritable(buffer_1)?IOPAUSE_WRITE:0);
		
		int r = iopause_g(x, 2, &deadline) ;
		if (r < 0) {
			strerr_die3x(1, PROG, ": fatal: ", "iopause");
		}
		else if (!r) {
			if(verbosity) 
				strerr_warn1x("timeout");

			// restart timeout
			tain_addsec_g(&deadline, 1);

			// fill buffer_1
			buffer_putsnoflush(buffer_1, "msg ");
			{
				char digit[UINT16_FMT];
				int l=uint16_fmt(digit, counter++);
				buffer_putnoflush(buffer_1, digit, l);
			}
			
		}
		else {
			if ((x[0].revents | x[1].revents) & IOPAUSE_EXCEPT) {
				strerr_die3x(1, PROG, ": fatal: ", "iopause EXCEPT event");
			}
			if (x[0].revents & IOPAUSE_READ) handle_signals() ;
			if (x[1].revents & IOPAUSE_WRITE) {
				if(verbosity) 
					strerr_warn1x("write");
				
				// flush buffer_1
				buffer_putflush(buffer_1, "\n", 1) ;
			}
		  }
	}
	
	selfpipe_finish() ;
	buffer_putsflush(buffer_1, "exiting\n") ;
	return 0;
}