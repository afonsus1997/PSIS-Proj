#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <pthread.h>
#include <semaphore.h>

#define NORMAL 0
#define ABERTO 1
#define FECHADO 2

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
#define NPOR 4 /* numero de portas a controlar (ABC...) */
#define CTLA "/CTLA" /* nome do controlador A (queue) */
// ou #define CTLA 0x4341 /* (’C’’A’) nome (chave) do controlador A (msg) */
#define CTLB "/CTLB" /* nome do controlador B (queue) */
// ou #define CTLB 0x4342 /* (’C’’B’) nome (chave) do controlador B (msg) */
#define CTLC "/CTLC" /* nome do controlador C (queue) */
// ou #define CTLC 0x4343 /* (’C’’C’) nome (chave) do controlador C (msg) */


#endif

typedef struct uti_s { /* estrutura de um registo utilizador */
	char id[NDIG+1]; /* identificador do utilizador */
	char nome[MAXN]; /* nome do utilizador */
	unsigned char port[NPOR]; /* portas acess´ıveis ao utilizador: 1-acesso 0-n~ao */
} uti_t;
typedef struct reg_s { /* estrutura de um registo historico */
	//struct timespec t; /* estampilha temporal */
	char p; /* identificador da porta: A,B,C */
	char id[NDIG+1]; /* identificador do utilizador */
	unsigned char ac; /* acesso: 1-concedido; 0-recusado */
} reg_t;

typedef struct message{
	
	char header[20]; 
	uti_t reguti[UMAX+1];
	reg_t regt[UMAX+1];
	
	
}message_t;

typedef struct doorcomm{
    char    cid[10];
    char    porta;
    char    id[UMAX][NDIG+1];   
  } doorcomm_t;

  char usersCache[UMAX][NDIG+1];


char cliname[10];
char readBuf[NDIG+5];
struct mq_attr ma;
char message[NDIG+1];
char servmsg[30];
int mqids, mqidc;
int cliid;
doorcomm_t msgIN;
doorcomm_t askDoor;

char clientDoor;
