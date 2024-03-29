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
#include <signal.h>
#include <time.h>
#include <sys/time.h>

#include "structs.h"


#define NPROSS 3
#define TRUE 1
#define SERVNAME "/tmp/SERV1"
#define CLINAME "/tmp/CLI"
#define MSG "Cliente pergunta?!"

#define NDIG 4 /* numero de digitos do identificador */
#define IDX "9999" /* identificador especial de acesso */
#define MAXN 50 /* dimensao maxima do nome do utilizador */
#define CMAX 5 /* dimensao da cache de utilizadores */
#define UMAX 15 /* numero maximo de utilizadores */
#define FUTI "USERS.DAT" /* ficheiro relativo aos utilizadores */
#define NREG 150 /* numero maximo de registos no ficheiro */
#define FLOG "ACESSOS.LOG" /* ficheiro com historico dos acessos */
#define SERVS "/tmp/SERV" /* nome do servidor (socket) */
#define SERVQ "/SERV" /* nome do servidor (queue) */
// ou #define SERVQ 0x53 /* (’S’) nome (chave) do servidor (msg) */
#define NPOR 3 /* numero de portas a controlar (ABC...) */
#define CTLA "/CTLA" /* nome do controlador A (queue) */
// ou #define CTLA 0x4341 /* (’C’’A’) nome (chave) do controlador A (msg) */
#define CTLB "/CTLB" /* nome do controlador B (queue) */
// ou #define CTLB 0x4342 /* (’C’’B’) nome (chave) do controlador B (msg) */
#define CTLC "/CTLC" /* nome do controlador C (queue) */
// ou #define CTLC 0x4343 /* (’C’’C’) nome (chave) do controlador C (msg) */


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"




#endif

int clientInit();

int sendInfo(message_t* msg);

int closeServer();

void splashscreen();

void exitHandler();