CC=gcc
CFLAGS= -Wall -g -pthread
LDFLAGS= -lrt -lpthread

EXMQ= ctldoor

EXALL= $(EXMQ)

all: $(EXALL)

ctldoor: ctldoor.o
	$(CC) -o ctldoor ctldoor.o structs.h $(LDFLAGS)
	
clean:
	rm -f $(EXALL) *.o
