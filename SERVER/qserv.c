/*
***********************************************************************************
----------------------------------------QSERV.c-----------------------------------

    -> Has all the functions needed for the queue comm with the doors

    -> qserv.h keeps necessary libraries and contants and function prototypes

    -> 
-----------------------------------------------------------------------------------
***********************************************************************************
*/


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
  printf("Done.\n\n");

  printf("\nReady\n\n");

}

int sendQMessage(doorcomm_t inQMsg, doorcomm_t outQMsg){
    
    if ((mqidc=mq_open(outQMsg.cid, O_RDWR)) < 0) {
      perror("Servidor: Erro a associar a queue cliente");
    }
      
    if (mq_send(mqidc, &outQMsg, sizeof(doorcomm_t), 0) < 0) {
	perror("Servidor: erro a enviar mensagem");
    }
}


doorcomm_t recieveQMessage(){
  doorcomm_t inQMsg;
  if (mq_receive(mqids, &inQMsg, sizeof(message_t), NULL) < 0) {
    perror("Servidor: erro a receber mensagem");
  }
}


int closeQServer(){
    
    mq_unlink(SERVNAME);
    //perror("Servidor: Erro a eliminar queue servidor");
  

}


