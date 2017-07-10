OS !=	uname -s | tr '[A-Z]' '[a-z]'

PROG =	dwmstatus
OBJS =	battery-${OS}.o config.o cputemp-${OS}.o loadavg.o maildir.o	\
		main.o status.o time.o

CFLAGS +=	-D_BSD_SOURCE
CFLAGS +=	-Wall -Wextra
CFLAGS +=	-std=c99

# Add these lines to build in stdout mode
# CFLAGS +=	-D_NO_X11

# Remove these lines to build in stdout mode
CFLAGS +=	-I/usr/X11R6/include
LDFLAGS +=	-L/usr/X11R6/lib
LDADD +=	-lX11

# Remove these lines to build without libicu
OBJS +=	utime.o
UTIME_CFLAGS !=	pkg-config --cflags icu-i18n
UTIME_LDADD !=	pkg-config --libs icu-i18n
CFLAGS +=	-D_WITH_UTIME
CFLAGS +=	${UTIME_CFLAGS}
LDADD +=	${UTIME_LDADD}

RM ?=	rm -f

.PHONY: all clean

all: ${PROG}

clean:
	${RM} ${PROG} ${OBJS}

${PROG}: ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LDFLAGS} ${LDADD}
