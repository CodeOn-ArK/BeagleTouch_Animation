#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <io.h>
#include <ansi/style.h>

int printws(const style_t *style, const char *format, ...)
{
    char str[SEND_BUF_SIZ];
    va_list args;
    int bytes;

    /* extract the arg list using va apis */
    va_start(args, format);
    bytes = vsnprintf(str, SEND_BUF_SIZ, format, args);
    va_end(args);

    if ( style ) set_style(style);

    if ( bytes >= 0 ) {
        /* `vsnprintf()` didn't report an error */
        str[SEND_BUF_SIZ - 1] = '\0';
        write(STDOUT_FILENO, (void *) str, strlen(str));
    }

    if ( style ) reset_all();

    return bytes;
}

int scanmsg(const char *format, ...)
{
    char str[RECV_BUF_SIZ];
    va_list args;
    int items;

    /* `read()` will timeout after 100 ms */
    read(STDIN_FILENO, str, RECV_BUF_SIZ);
    str[RECV_BUF_SIZ - 1] = '\0';

    /* extract the arg list using va apis */
    va_start(args, format);
    items = vsscanf(str, format, args);
    va_end(args);

    return items;
}

