#ifndef INTGEST_h
#define INTGEST_h

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "structs.h"


#define NPROSS 3
#define TRUE 1
#define SERVNAME "/tmp/SERV1"
#define CLINAME "/tmp/CLI"
#define MSG "Cliente pergunta?!"

#endif

int clientInit();

int sendInfo(MESSAGE* msg);

int closeServer();

void splashscreen();