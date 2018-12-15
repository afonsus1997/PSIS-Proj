#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "structs.h"
#include <sys/mman.h>
#include <fcntl.h>

//#include "structs.h"

int intgestParser(message_t msgIN);

#endif

extern int sendQMessage(doorcomm_t inQMsg, doorcomm_t outQMsg);
extern int sendQMessage2(doorcomm_t inQMsg, doorcomm_t outQMsg);
doorcomm_t recieveQMessage();
doorcomm_t sendAcesses;