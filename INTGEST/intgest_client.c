#include "intgest.h"

int sd;
struct sockaddr_un my_addr;
socklen_t addrlen;
struct sockaddr_un to;
socklen_t tolen;
char buf[100];
char cliname[100] = "/tmp/CLI";
int cliid;

int clientInit()
{
  /*
 * Function:  clientInit 
 * --------------------
 *  Initializes the Socket communication. 
 * 
 *  Returns:
 *      1: If Successful
 *      0: If not Successful
 * 
 */
  unlink(cliname); 

  printf("Client Name: %s\n", cliname);
  if ((sd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
  {
    perror("Erro a criar socket");
    exit(-1);
  }

  my_addr.sun_family = AF_UNIX;
  (my_addr.sun_path, 0, sizeof(my_addr.sun_path));
  strcpy(my_addr.sun_path, cliname);
  addrlen = sizeof(my_addr.sun_family) + strlen(my_addr.sun_path);

  if (bind(sd, (struct sockaddr *)&my_addr, addrlen) < 0)
  {
    perror("Erro no bind");
    exit(-1);
  }

  to.sun_family = AF_UNIX;
  memset(to.sun_path, 0, sizeof(to.sun_path));
  strcpy(to.sun_path, SERVNAME);
  tolen = sizeof(my_addr.sun_family) + strlen(to.sun_path);
}

int sendInfo(message_t *msg)
{
 /*
 * Function:  sendInfo 
 * --------------------
 *  Send message of type message_t using Sockets.
 * 
 *  Returns:
 *      1: If Successful
 *      0: If not Successful
 */
  if (sendto(sd, msg, sizeof(message_t), 0, (struct sockaddr *)&to, tolen) < 0)
  {
    perror("CLI: Erro no sendto");
    return 0;
  }
  else
    return 1;
}

message_t recieveInfo()
{ 
  /*
 * Function:  recieveInfo 
 * --------------------
 *  Receives message of type message_t using Sockets.
 * 
 *  Returns:
 *      (message_t) message
 */ 
  message_t msgIN;
  if (recvfrom(sd, &msgIN, sizeof(message_t), 0, (struct sockaddr *)&to,
               &tolen) < 0)
  {
    perror("CLI: Erro no recvfrom");
  }
  else if (strcmp(msgIN.header, "LAPUC") != 0)
  {

    printf("\nServer: %s\n", msgIN.header);
    return msgIN;
  }
  else
  {
    return msgIN;
  }
}

int closeServer()
{
/*
 * Function:  Close server 
 * --------------------
 * Closes Server.
 * 
 *  Returns:
 *      (int)
 */ 
  system("clear");
  printf("\n\nStopping client...\n");
  close(sd);
  unlink(cliname);
  printf("\nDone!\n");
}

