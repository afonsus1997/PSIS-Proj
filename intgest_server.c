#include "intgest.h"

int sd;
struct sockaddr_un my_addr;
socklen_t addrlen;
struct sockaddr_un to;
socklen_t tolen;
char buf[100];
char cliname[100] = "/tmp/";
int cliid;


int serverInit(){
  cliid = getpid();
  sprintf(cliname,"%ld", cliid);
  //strcat(cliname, (char*)cliid);

  if ((sd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0 ) {
    perror("Erro a criar socket"); exit(-1);
  }
      
  my_addr.sun_family = AF_UNIX;
  memset(my_addr.sun_path, 0, sizeof(my_addr.sun_path));
  strcpy(my_addr.sun_path, cliname);
  addrlen = sizeof(my_addr.sun_family) + strlen(my_addr.sun_path);

  if (bind(sd, (struct sockaddr *)&my_addr, addrlen) < 0 ) {
    perror("Erro no bind"); exit(-1);
  }

  to.sun_family = AF_UNIX;
  memset(to.sun_path, 0, sizeof(to.sun_path));
  strcpy(to.sun_path, SERVNAME);
  tolen = sizeof(my_addr.sun_family) + strlen(to.sun_path);
}
  
int sendInfo(MESSAGE* msg){
  if (sendto(sd, MSG, strlen(MSG)+1, 0, (struct sockaddr *)&to, 
	     tolen) < 0) {
    perror("CLI: Erro no sendto");
  }
  else {
    if (recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&to, 
		 &tolen) < 0) {
      perror("CLI: Erro no recvfrom");
    }
    else {
      printf("CLI: Recebi: %s\n", buf);
    }
  }   

}

int closeServer(){
  close(sd);
  unlink(cliname);
}