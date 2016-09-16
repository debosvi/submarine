#include <stdarg.h>
#include "x86_support.h"

static void my_puts(const char *s)
{
    unsigned int i;
    for (i = 0; s[i] != '\0'; i++) vScreenPutchar(s[i]);
}

static void my_puth(unsigned int x)
{
    char x2c[] = "0123456789abcdef";
    char s[20], *ps;

    if (x == 0) vScreenPutchar('0');
    else {
        s[19] = '\0';
        ps = s + 18;
        for (; x; x /= 16, ps--) *ps = x2c[x % 16];
        my_puts(ps + 1);
    }
}

void printf(const char *format, ...)
{
    va_list args;
    unsigned int i;

    va_start(args, format);
    for (i = 0; format[i]; i++) {
        if (format[i] == '%') {
            i++;
            if (format[i] == 'x') my_puth(va_arg(args, unsigned int));
            else if (format[i] == 's') my_puts(va_arg(args, const char *));
            else if (format[i] == '%') vScreenPutchar('%');
            else if (format[i] == '\0') break;
        }
        else vScreenPutchar(format[i]);
    }
    va_end(args);
}

/*
int sprintf(char *out, const char *format, ...)
{
        va_list args;
        
        va_start( args, format );
        return print( &out, format, args );
}


int snprintf( char *buf, unsigned int count, const char *format, ... )
{
        va_list args;
        
        ( void ) count;
        
        va_start( args, format );
        return print( &buf, format, args );
}
*/