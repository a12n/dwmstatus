include common.mk

CFLAGS +=	-Wall -Wextra

.PHONY: clean

${PROG}: ${OBJS}
	${CC} ${CFLAGS} -o $@ $^ ${LDFLAGS} ${LDADD}

clean:
	${RM} ${PROG} ${OBJS}
