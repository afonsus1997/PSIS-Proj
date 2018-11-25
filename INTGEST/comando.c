/***************************************************************************
| File: comando.c  -  Concretizacao de comandos (exemplo)
|
| Autor: Carlos Almeida (IST)
| Data:  Nov 2002
***************************************************************************/

#ifndef COMANDO_h
#define COMANDO_h

#include "structs.h"


#endif

extern int closeServer(void);
extern message_t recieveInfo();
extern int sendInfo(message_t* msg);


#include <stdio.h>
#include <stdlib.h>



/*-------------------------------------------------------------------------+
| Function: cmd_sair - termina a aplicacao
+--------------------------------------------------------------------------*/ 
message_t nuti (int argc, char **argv)
{
  message_t msgOut;
  message_t msgIn;
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
message_t luti (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;
  strcpy(msgOut.header, "LUTI");
  strcpy(msgOut.reguti[0].id, argv[1]);
  sendInfo(&msgOut);
  msgIn = recieveInfo();
  printf("Users:\n");
  int i;
  if(strcmp(msgOut.reguti[0].id, "0")!=0){
    printf("\tID: %s\n", msgIn.reguti[0].id);
    printf("\tNOME: %s\n", msgIn.reguti[0].nome);
    printf("\tPORTAs: %s\n\n", msgIn.reguti[0].port);
  }
  else{
    for(i=0 ; i<UMAX-1 ; i++){
        if(strcmp(msgIn.reguti[i].id, "\000") != 0){
          printf("\tID: %s\n", msgIn.reguti[i].id);
          printf("\tNOME: %s\n", msgIn.reguti[i].nome);
          printf("\tPORTAs: %s\n\n", msgIn.reguti[i].port);
        }
    }      
  }

}

message_t euti (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;
  strcpy(msgOut.header, "EUTI");
  strcpy(msgOut.reguti[0].id, argv[1]);
  sendInfo(&msgOut);
  recieveInfo();

}

message_t mpu (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;
  strcpy(msgOut.header, "MPU");
  strcpy(msgOut.reguti[0].id, argv[1]);
  strcpy(msgOut.reguti[0].port, argv[2]);
  sendInfo(&msgOut);
  recieveInfo();

}

message_t lapu (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;
  strcpy(msgOut.header, "LAPU");
  strcpy(msgOut.reguti[0].port, argv[1]);
  strcpy(msgOut.reguti[0].id, argv[2]);
  //strcpy(msgOut.reguti.nome, argv[3]);   TEMPO
  
  sendInfo(&msgOut);
  recieveInfo();

}

message_t tserv (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;
  strcpy(msgOut.header, "TSERV");
  sendInfo(&msgOut);
  recieveInfo();

}

message_t cep (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;
  strcpy(msgOut.header, "CEP");
  strcpy(msgOut.reguti[0].port, argv[1]);
  sendInfo(&msgOut);
  recieveInfo();

}

message_t mep (int argc, char** argv)
{
  message_t msgOut;
  message_t msgIn;
  strcpy(msgOut.header, "MEP");
  strcpy(msgOut.reguti[0].nome, argv[2]);  //ESTADO
  strcpy(msgOut.reguti[0].port, argv[1]);
  sendInfo(&msgOut);
  recieveInfo();

}

message_t rip (int argc, char** argv)
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