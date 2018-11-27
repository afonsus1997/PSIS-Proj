CC=gcc
CFLAGS= -g -pthread
LDFLAGS= -lrt -lpthread

OBJS= server.o sdsrv.o management.o qserv.c
DEPS = structs.h server.h management.h server.h qserv.h


all: $(OBJS)
	$(CC) -o server $(OBJS) $(DEPS) $(CFLAGS) $(LDFLAGS)


%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS) $(LDFLAGS)


sd: $(EXSD)

ss: $(EXSS)

clean:
	rm -f $(EXALL)

