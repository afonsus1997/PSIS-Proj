CC=gcc
CFLAGS= -g
LDFLAGS= -lrt

OBJS= ctlgeral.o qclient.o
DEPS = structs.h


all: $(OBJS)
	$(CC) -o ctlport $(OBJS) $(DEPS) $(CFLAGS) $(LDFLAGS)


%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS) $(LDFLAGS)


sd: $(EXSD)

ss: $(EXSS)

clean:
	rm -f $(EXALL)

