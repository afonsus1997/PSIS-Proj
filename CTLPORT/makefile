CC=gcc
CFLAGS= -Wall -g -pthread  
LDFLAGS= -lrt -lpthread 

EXMQ= ctldoor

EXALL= $(EXMQ)

all: $(EXALL)

ctldoor: ctldoor.o management.o queuecl.o
	$(CC) -o ctldoor ctldoor.o management.o queuecl.o structs.h $(LDFLAGS) $(CFLAGS)
	
clean:
	rm -f $(EXALL) *.o
