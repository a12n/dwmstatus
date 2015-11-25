OS !=	uname -s | tr '[A-Z]' '[a-z]'

PROG =	dwmstatus
OBJS =	battery-${OS}.o cpu_temp-${OS}.o loadavg.o maildir.o main.o	\
		status.o time.o

CFLAGS +=	-Wall -Wextra

# Add these lines to build in stdout mode
# CFLAGS +=	-D_NO_X11

# Remove these lines to build in stdout mode
CFLAGS +=	-I/usr/X11R6/include
LDFLAGS +=	-L/usr/X11R6/lib
LDADD +=	-lX11

RM ?=	rm -f

.PHONY: all clean

all: ${PROG}

clean:
	${RM} ${PROG} ${OBJS}

${PROG}: ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LDFLAGS} ${LDADD}
