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



int main()
{
  int sd;
  struct sockaddr_un my_addr;
  socklen_t addrlen;
  struct sockaddr_un from;
  socklen_t fromlen;
  char buf[100];


  MESSAGE msgIN;

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


  while(TRUE){

    fromlen = sizeof(from);
  

  if (recvfrom(sd, &msgIN, fromlen, 0, (struct sockaddr *)&from, 
	       &fromlen) < 0) {
    perror("Erro no recvfrom");
  }
  else {
    printf("SERV: Recebi: %s\n", msgIN.header);
//    if (sendto(sd, MSG, strlen(MSG)+1, 0, (struct sockaddr *)&from, fromlen) < 0) {
    
    //MESSAGE buffer[sizeof(MESSAGE)];

    //memcpy(msgIN, buffer, sizeof(MESSAGE));

    if (sendto(sd, MSG, strlen(MSG)+1, 0, (struct sockaddr *)&from, fromlen) < 0) {

      perror("Erro no sendto");
    }
  }

  }
  

  close(sd);
  unlink(SERVNAME);

  return 0;
}


