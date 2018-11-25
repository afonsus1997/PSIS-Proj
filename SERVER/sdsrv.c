/* Exemplo de utilizacao de sockets unix datagrama na comunicacao
   entre 2 processos independentes hierarquicamente (Cliente,
   Servidor).  Executar primeiro (em "background" ou noutra janela) o
   programa Servidor (este programa - "sdsrv"), e depois o programa
   Cliente ("sdcli").  -- CRA
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "structs.h"

#define TRUE 1
#define SERVNAME "/tmp/SERV1"
#define MSG "Servidor responde!!!"


int sd;
struct sockaddr_un my_addr;
socklen_t addrlen;
struct sockaddr_un from;
socklen_t fromlen;
char buf[100];
message_t msgIN;

int serverInit(){


  unlink(SERVNAME);
  if ((sd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0 ) {
    perror("Erro a criar socket"); exit(-1);
  }
      
  my_addr.sun_family = AF_UNIX;
  memset(my_addr.sun_path, 0, sizeof(my_addr.sun_path));
  strcpy(my_addr.sun_path, SERVNAME);
  addrlen = sizeof(my_addr.sun_family) + strlen(my_addr.sun_path);

  if (bind(sd, (struct sockaddr *)&my_addr, addrlen) < 0 ) {
    perror("Erro no bind"); exit(-1);
  }

  return 0;

}

int closeServer(){
  system("clear");
  printf("\n\nStopping server...\n");
  close(sd);
  unlink(SERVNAME);
  printf("\nDone!\n");
  return 0;
}

message_t recieveMessage(){

  

    fromlen = sizeof(from);
  

  if (recvfrom(sd, &msgIN, fromlen, 0, (struct sockaddr *)&from, 
	       &fromlen) < 0) {
    perror("Erro no recvfrom");
  }
  else {
    
    
    printf("SERV: Header: %s\n", msgIN.header);
    printf("SERV: User ID: %s\n", msgIN.reguti.id);
    printf("SERV: Nome: %s\n", msgIN.reguti.nome);
    printf("SERV: Portas: %s\n", msgIN.reguti.port);
    printf("\n\n\n");



    
  
    return msgIN;

  }
  
  

}

int sendMessage(message_t msgOUT){
  if (sendto(sd, &msgOUT, sizeof(msgIN), 0, (struct sockaddr *)&from, fromlen) < 0) {

      perror("Erro no sendto");
      return -1;
    }
  return 0;
}







