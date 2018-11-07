CC=gcc
CFLAGS= -Wall -g

OBJS= structs.o intgest.o intgest_server.o monitor.o comando.o
DEPS = intgest.h structs.h 


all: $(OBJS)
	$(CC) -o intgest $(OBJS) $(DEPS) $(CFLAGS)


%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)
	

sd: $(EXSD) 

ss: $(EXSS)

clean:
	rm -f $(EXALL)

