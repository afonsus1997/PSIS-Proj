/***************************************************************************
| File: comando.c  -  Concretizacao de comandos (exemplo)
|
| Autor: Carlos Almeida (IST)
| Data:  Nov 2002
***************************************************************************/

#ifndef COMANDO_h
#define COMANDO_h

#include "structs.h"
#include <signal.h>


#endif

extern int closeServer(void);
extern message_t recieveInfo();
extern int sendInfo(message_t* msg);


#include <stdio.h>
#include <stdlib.h>

void printPorts(char ports[NPOR+1]){
    int i;
    for(i=0 ; i<NPOR ; i++){
        if(ports[i] == '1'){
            if(i==0) printf(" %c", 'A');
            if(i==1) printf(" %c", 'B');
            if(i==2) printf(" %c", 'C');
        }
    }
}

/*-------------------------------------------------------------------------+
| Function: cmd_sair - termina a aplicacao
+--------------------------------------------------------------------------*/ 
int nuti (int argc, char **argv)
{
  message_t msgOut;
  message_t msgIn;
  if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL){
    return -1;
  }
  strcpy(msgOut.header, "NUTI");
  strcpy(msgOut.reguti[0].id, argv[1]);
  strcpy(msgOut.reguti[0].nome, argv[2]);
  strcpy(msgOut.reguti[0].port, argv[3]);
  sendInfo(&msgOut);
  recieveInfo();
  
}

/*-------------------------------------------------------------------------+
| Function: cmd_test - apenas como exemplo
+--------------------------------------------------------------------------*/ 
int luti (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;

  if(argv[1] == NULL){
      return -1;
    }

  strcpy(msgOut.header, "LUTI");
  strcpy(msgOut.reguti[0].id, argv[1]);
  sendInfo(&msgOut);
  msgIn = recieveInfo();
  //if(strcmp(msgIn.header, "DONE")==0){
  int i;
  if(strcmp(msgOut.reguti[0].id, "0")!=0 && strcmp(msgIn.header, "Done")==0){
    printf("Users:\n");
    printf("\tID: %s\n", msgIn.reguti[0].id);
    printf("\tNOME: %s\n", msgIn.reguti[0].nome);
    printf("\tPORTAs:"); printPorts(msgIn.reguti[0].port); printf("\n\n");
  }
  else{
    for(i=0 ; i<UMAX-1 ; i++){
      if(strcmp(msgIn.reguti[i].id, "\0") != 0 && strcmp(msgIn.header, "Done")==0){
        printf("Users:\n");
        printf("\tID: %s\n", msgIn.reguti[i].id);
        printf("\tNOME: %s\n", msgIn.reguti[i].nome);
        printf("\tPORTAs:"); printPorts(msgIn.reguti[i].port); printf("\n\n");
      }
    }      
  }

}

int euti (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;

  if(argv[1] == NULL){
    return -1;
  }

  strcpy(msgOut.header, "EUTI");
  strcpy(msgOut.reguti[0].id, argv[1]);
  sendInfo(&msgOut);
  recieveInfo();

}

int mpu (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;

  if(argv[1] == NULL || argv[2] == NULL){
    return -1;
  }

  strcpy(msgOut.header, "MPU");
  strcpy(msgOut.reguti[0].id, argv[1]);
  strcpy(msgOut.reguti[0].port, argv[2]);
  sendInfo(&msgOut);
  recieveInfo();

}

int lapu (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;

  if(argv[1] == NULL || argv[2] == NULL){
    return -1;
  }

  strcpy(msgOut.header, "LAPU");
  strcpy(msgOut.reguti[0].port, argv[1]);
  strcpy(msgOut.reguti[0].id, argv[2]);
  //strcpy(msgOut.reguti.nome, argv[3]);   TEMPO
  
  sendInfo(&msgOut);
  recieveInfo();

}

int tserv (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;
  strcpy(msgOut.header, "TSERV");
  sendInfo(&msgOut);
  recieveInfo();
  kill(getpid(), SIGINT);


}

int cep (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;
  char door;
  strcpy(msgOut.header, "CEP");
  strcpy(msgOut.reguti[0].port, argv[1]);
  door = msgOut.reguti[0].port[0];
  sendInfo(&msgOut);

  msgIn = recieveInfo();

  if(argv[1][0] == '0'){
    printf("Door A state: %c\n\n", msgIn.reguti[0].port[0]);
    printf("Door B state: %c\n\n", msgIn.reguti[0].port[1]);
    printf("Door C state: %c\n\n", msgIn.reguti[0].port[2]);
  }
  else{
    printf("Door %c state: %c\n\n", door, msgIn.reguti[0].port[0]);
  }


}

int mep (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;

  if(argv[1] == NULL || argv[2] == NULL){
    return -1;
  }

  strcpy(msgOut.header, "MEP");
  strcpy(msgOut.reguti[0].nome, argv[2]);  //ESTADO
  strcpy(msgOut.reguti[0].port, argv[1]);
  sendInfo(&msgOut);
  
  recieveInfo();

}

int rip (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;
  strcpy(msgOut.header, "RIP");
  strcpy(msgOut.reguti[0].port, argv[1]);
  sendInfo(&msgOut);
  recieveInfo();

}

void cmd_sair (int argc, char** argv)
{
  closeServer();
  exit(0);
}

void cmd_test (int argc, char** argv)
{
  printf("This is a test dumbass\n");
}