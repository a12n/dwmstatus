OS !=	uname -s | tr '[A-Z]' '[a-z]'

PROG =	dwmstatus
OBJS =	battery-${OS}.o cpu_temp-${OS}.o loadavg.o maildir.o main.o	\
		status.o time.o

# Add these lines to build in stdout mode
# CFLAGS +=	-D_NO_X11

# Remove these lines to build in stdout mode
CFLAGS +=	-I/usr/X11R6/include
LDFLAGS +=	-L/usr/X11R6/lib
LDADD +=	-lX11
