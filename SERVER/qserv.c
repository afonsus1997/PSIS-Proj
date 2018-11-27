#include "qserv.h"

struct mq_attr ma;


int initQueue(){

  
  ma.mq_flags = 0;
  ma.mq_maxmsg = 2;
  ma.mq_msgsize = sizeof(msg);
  printf("\nStarting Queue...\n");
  if ((mqids=mq_open(SERVNAME, O_RDWR|O_CREAT, 0666, &ma)) < 0) {
    perror("Servidor: Erro a criar queue servidor");
    exit(-1);
  }


}

int sendQMessage(){
     
    if (mq_receive(mqids, (char *)&msg, sizeof(msg), NULL) < 0) {
    perror("Servidor: erro a receber mensagem");
  }
  else {
    for (i=0; i<TXTSIZE; i++)
      printf("%c", msg.mtext[i]);

    if ((mqidc=mq_open(msg.id, O_RDWR)) < 0) {
      perror("Servidor: Erro a associar a queue cliente");
    }

     printf("Servidor vai enviar\n");
      for (i=0; i<TXTSIZE; i++)
	msg.mtext[i] = 'S';
      if (mq_send(mqidc, (char *)&msg, sizeof(msg), 0) < 0) {
	perror("Servidor: erro a enviar mensagem");
    }
  }
}


int closeQServer(){
    
    mq_unlink(SERVNAME);
    //perror("Servidor: Erro a eliminar queue servidor");
  

}