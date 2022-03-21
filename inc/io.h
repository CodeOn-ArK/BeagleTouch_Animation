#ifndef __IO_H_
# define __IO_H_

# include <ansi/style.h>

# define SEND_BUF_SIZ 4096
# define RECV_BUF_SIZ 4096

int printws(const style_t *, const char *format, ...);
int scanmsg(const char *format, ...);

#endif  /* __IO_H_ */

