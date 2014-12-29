PROG =	dwmstatus
SRCS =	main.c status.c
MAN =

CFLAGS +=	-I/usr/X11R6/include
LDFLAGS +=	-L/usr/X11R6/lib
LDADD +=	-lX11

.include <bsd.prog.mk>
