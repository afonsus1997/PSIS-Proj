CC=gcc
CFLAGS= -Wall -g

OBJS= sdsrv.o 
DEPS = structs.h 


all: $(OBJS)
	$(CC) -o server $(OBJS) $(DEPS) $(CFLAGS)


%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)
	

sd: $(EXSD) 

ss: $(EXSS)

clean:
	rm -f $(EXALL)

