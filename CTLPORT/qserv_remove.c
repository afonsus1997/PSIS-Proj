#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include "structs.h"

struct mq_attr ma;
char message[30];
int main()
{
  int mqids, mqidc,i;
  char cliname[10];
  doorcomm_t cache;
  strcpy(cache.porta,"A");
  ma.mq_flags = 0;
  ma.mq_maxmsg = 2;
  ma.mq_msgsize = sizeof(message);
  

  
  if ((mqids=mq_open(SERVQ, O_RDWR|O_CREAT, 0666, &ma)) < 0) {
    perror("Servidor: Erro a criar queue servidor");
    exit(-1);
  }
    snprintf(cliname, sizeof(cliname), "/CL-%05d", atoi(cache.porta));
    if ((mqidc=mq_open(cliname, O_RDWR)) < 0) {
        perror("Servidor: Erro a associar a queue cliente");
    }
    else {
        printf("Servidor vai enviar\n");
        if (mq_send(mqidc, &cache, sizeof(cache), 0) < 0) {
        perror("Servidor: erro a enviar mensagem");
        }
        else {
            //printf("Servidor vai receber\n");
            if (mq_receive(mqids, &message, sizeof(message), NULL) < 0) {
                perror("Servidor: erro a receber mensagem");
            }
            printf("%s\n", message);    
        }
    }
  if (mq_unlink(SERVQ) < 0) {
    perror("Servidor: Erro a eliminar queue servidor");
  }

  return 0;
}