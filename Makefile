PROG =	dwmstatus
SRCS =	loadavg.c maildir.c main.c status.c time.c
MAN =

CFLAGS +=	-I/usr/X11R6/include
LDFLAGS +=	-L/usr/X11R6/lib
LDADD +=	-lX11

.include <bsd.prog.mk>
