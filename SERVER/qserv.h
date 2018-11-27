#ifndef QSERV_H
#define QSERV_H

#include "structs.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERVNAME "/SERV"
#define TXTSIZE 10

#endif 



int mqids, mqidc, i;
  struct {
    char    id[10];
    char    mtext[TXTSIZE];   /* message text */
  } msg;

  
