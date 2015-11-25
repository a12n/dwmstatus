OS !=	uname -s | tr '[A-Z]' '[a-z]'

WARNINGS =	yes

PROG =	dwmstatus
SRCS =	battery-${OS}.c loadavg.c maildir.c main.c status.c time.c
MAN =

# Add these lines to build in stdout mode
# CFLAGS +=	-D_NO_X11

# Remove these lines to build in stdout mode
CFLAGS +=	-I/usr/X11R6/include
LDFLAGS +=	-L/usr/X11R6/lib
LDADD +=	-lX11

.include <bsd.prog.mk>
