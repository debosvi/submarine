/* ISC license. */

#ifndef S6SYS_WRAPPER_PRIVATE_H
#define S6SYS_WRAPPER_PRIVATE_H

extern int __wrap_socket(int domain, int type, int protocol);    
extern int __wrap_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
extern int __wrap_ioctl(int d, int req, ...);
extern ssize_t __wrap_setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);

#endif // S6SYS_WRAPPER_PRIVATE_H
