/* ISC license. */

#define __USE_MISC
#define _DEFAULT_SOURCE

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>


#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <skalibs/environ.h>
#include <skalibs/sgetopt.h>
#include <skalibs/strerr2.h>
#include <skalibs/types.h>

#define USAGE "s6canbus-showfds [-v verbosity] prog..."
#define dieusage() strerr_dieusage(100, USAGE)

/* check whether a file-descriptor is valid */
// static int pth_util_fd_valid(int fd)
// {
//      if (fd < 3 || fd >= FD_SETSIZE)
//           return FALSE;
//      if (fcntl(fd, F_GETFL) == -1 && errno == EBADF)
//           return FALSE;
//      return TRUE;
// }


static char *fcntl_flags(int flags)
{
    static char output[128];
    *output = 0;

    if (flags & O_RDONLY)
        strcat(output, "O_RDONLY ");
    if (flags & O_WRONLY)
        strcat(output, "O_WRONLY ");
    if (flags & O_RDWR)
        strcat(output, "O_RDWR ");
    if (flags & O_CREAT)
        strcat(output, "O_CREAT ");
    if (flags & O_EXCL)
        strcat(output, "O_EXCL ");
    if (flags & O_NOCTTY)
        strcat(output, "O_NOCTTY ");
    if (flags & O_TRUNC)
        strcat(output, "O_TRUNC ");
    if (flags & O_APPEND)
        strcat(output, "O_APPEND ");
    if (flags & O_NONBLOCK)
        strcat(output, "O_NONBLOCK ");
    if (flags & O_SYNC)
        strcat(output, "O_SYNC ");
    if (flags & O_ASYNC)
        strcat(output, "O_ASYNC ");

    return output;
}

static char *fd_info(int fd, int max_fds)
{
    if (fd < 0 || fd >= max_fds)
        return 0;
    // if (fcntl(fd, F_GETFL) == -1 && errno == EBADF)
    int rv = fcntl(fd, F_GETFL);
    return (rv == -1) ? strerror(errno) : fcntl_flags(rv);
}


/* check first 1024 (usual size of FD_SESIZE) file handles */
static int test_fds()
{
     int i;
     int fd_dup;
     char errst[64];
     int max_fds=getdtablesize();
     for (i = 0; i < max_fds; i++) {
          *errst = 0;
          fd_dup = dup(i);
          if (fd_dup == -1) {
                strcpy(errst, strerror(errno));
                // EBADF  oldfd isnâ€™t an open file descriptor, or newfd is out of the allowed range for file descriptors.
                // EBUSY  (Linux only) This may be returned by dup2() during a race condition with open(2) and dup().
                // EINTR  The dup2() call was interrupted by a signal; see signal(7).
                // EMFILE The process already has the maximum number of file descriptors open and tried to open a new one.
          } else {
                close(fd_dup);
                strcpy(errst, "dup() ok");
                fprintf(stderr, "%4i: %5i %24s %s\n", i, fcntl(i, F_GETOWN), fd_info(i, max_fds), errst);
          }
     }
     return 0;
}

int main (int argc, char const *const *argv, char const *const *envp) {
    unsigned int verbosity = 1;
    
    PROG = "s6canbus-showfds" ;
    environ=(char**)envp;

    {
        subgetopt_t l = SUBGETOPT_ZERO ;
        for (;;) {
            int opt = subgetopt_r(argc, argv, "v:", &l) ;
            if (opt == -1) break ;
            switch (opt) {
                case 'v' : if (!uint0_scan(l.arg, &verbosity)) dieusage() ; break ;
                default : dieusage() ;
            }
        }
        argc -= l.ind ; argv += l.ind ;
    }
    if (argc < 1) dieusage() ;
    
    test_fds();
    
    xpathexec_run(argv[0], argv, envp) ;
}

