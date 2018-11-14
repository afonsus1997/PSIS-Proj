#include "intgest.h"

int sd;
struct sockaddr_un my_addr;
socklen_t addrlen;
struct sockaddr_un to;
socklen_t tolen;
char buf[100];
char cliname[100] = "/tmp/CLI";
int cliid;


int clientInit(){
  //cliid = getpid();
  //sprintf(cliname,"%ld", cliid);
  //strcat(cliname, (char*)cliid);

  unlink(cliname);


  printf("Client Name: %s\n", cliname);
  if ((sd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0 ) {
    perror("Erro a criar socket"); exit(-1);
  }
      
  my_addr.sun_family = AF_UNIX;
    (my_addr.sun_path, 0, sizeof(my_addr.sun_path));
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
  //if(strcmp(msg->header, NULL) == 0)
  //return -1;

  void* flat_mess = (void*)malloc(msg); //flat struct to be sent
  
  memcpy(flat_mess, msg, sizeof(msg));
  //memcpy(flat_mess, msg, sizeof(msg));
  if (sendto(sd, flat_mess, sizeof(flat_mess), 0, (struct sockaddr *)&to, 
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


/*
FLATTEN

void* vptr_test = &test2;


uint8_t buffer[sizeof(MyStruct)];

memcpy(buffer, vptr_test, sizeof(MyStruct));


*/