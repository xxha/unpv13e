include ../Make.defines

PROGS = daytimetcpcli

all: ${PROGS}

daytimetcpcli: daytimetcpcli.o
	${CC} ${CFLAGS} -o $@ daytimetcpcli.o ${LIBS}

#daytimetcpsrv: daytimetcpsrv.o
#	${CC} ${CFLAGS} -o $@ daytimetcpsrv.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
