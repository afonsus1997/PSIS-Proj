CC=gcc
CFLAGS= -Wall -g
LDFLAGS= -lrt

EXMQ= qserv qclient

EXALL= $(EXMQ)

all: $(EXALL)

qserv: qserv.o
	$(CC) -o qserv qserv.o $(LDFLAGS)

qclient: qclient.o
	$(CC) -o ctldoor qclient.o structs.h $(LDFLAGS)
	
clean:
	rm -f $(EXALL) *.o
