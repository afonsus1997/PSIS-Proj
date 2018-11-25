CC=gcc
CFLAGS= -g

OBJS= server.o sdsrv.o management.o
DEPS = structs.h server.h management.h server.h


all: $(OBJS)
	$(CC) -o server $(OBJS) $(DEPS) $(CFLAGS)


%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)


sd: $(EXSD)

ss: $(EXSS)

clean:
	rm -f $(EXALL)

