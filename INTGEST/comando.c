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

/*
	CMD LIST:
	NUTI - NEW USER
		u - ID
		nome - NOME
		portas[] - PORTAS COM ACESSO 
	

	LUIT - LISTAR UTILIZADOR
		u - UTILIZADOR (0 - todos) (id, nome, portas) 
	EUTI - ELIMINAR UTILIZADORES 
		u - UTILIZAODR (0 - todos)
	MPU - MODIFICAR PORTAS UTILIZADOR
		u - UTILIZADOR (0 - todos)
		portas - PORTAS ABC
	LAPU - LISTAR ACESSOS 
		p - PORTA p (0 - todas)
		u - UTILIZADOR (0 - todos)
		[t1, t2] - TEMPO entre t1 e t2
	TSERV 
	CEP 
		p
	MEP 
		p
		e
	RIP
		p
	
	*/



#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------------------------------------------+
| Function: cmd_sair - termina a aplicacao
+--------------------------------------------------------------------------*/ 
message_t nuti (int argc, char **argv)
{
  message_t msgOut;
  strcpy(msgOut.header, "NUTI");
  strcpy(msgOut.reguti.id, argv[1]);
  strcpy(msgOut.reguti.nome, argv[2]);
  strcpy(msgOut.reguti.port, argv[3]);
  return msgOut;
}

/*-------------------------------------------------------------------------+
| Function: cmd_test - apenas como exemplo
+--------------------------------------------------------------------------*/ 
message_t luti (int argc, char** argv)
{
  message_t msgOut;
  strcpy(msgOut.header, "LUIT");
  strcpy(msgOut.reguti.id, argv[1]);
  return msgOut;
}

message_t euti (int argc, char** argv)
{
  message_t msgOut;
  strcpy(msgOut.header, "EUTI");
  strcpy(msgOut.reguti.id, argv[1]);
  return msgOut;
}

message_t mpu (int argc, char** argv)
{
  message_t msgOut;
  strcpy(msgOut.header, "MPU");
  strcpy(msgOut.reguti.id, argv[1]);
  strcpy(msgOut.reguti.port, argv[2]);
  return msgOut;
}

message_t lapu (int argc, char** argv)
{
  message_t msgOut;
  strcpy(msgOut.header, "LAPU");
  strcpy(msgOut.reguti.port, argv[1]);
  strcpy(msgOut.reguti.id, argv[2]);
  //strcpy(msgOut.reguti.nome, argv[3]);   TEMPO
  
  return msgOut;
}

message_t tserv (int argc, char** argv)
{
  message_t msgOut;
  strcpy(msgOut.header, "TSERV");
  return msgOut;
}

message_t cep (int argc, char** argv)
{
  message_t msgOut;
  strcpy(msgOut.header, "CEP");
  strcpy(msgOut.reguti.port, argv[1]);
  return msgOut;
}

message_t mep (int argc, char** argv)
{
  message_t msgOut;
  strcpy(msgOut.header, "MEP");
  strcpy(msgOut.reguti.nome, argv[2]);  //ESTADO
  strcpy(msgOut.reguti.port, argv[1]);
  return msgOut;
}

message_t rip (int argc, char** argv)
{
  message_t msgOut;
  strcpy(msgOut.header, "RIP");
  strcpy(msgOut.reguti.port, argv[1]);
  return msgOut;
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