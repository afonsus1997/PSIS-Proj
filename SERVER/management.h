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

message_t intgestParser(message_t msgIN);

#endif