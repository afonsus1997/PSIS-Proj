#include "intgest.h"

int sd;
struct sockaddr_un my_addr;
socklen_t addrlen;
struct sockaddr_un to;
socklen_t tolen;
char buf[100];
int cliid;
char cliname[20];
struct timeval tv;

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
  //unlink(CLINAME);
  int clipid = getpid();
  snprintf(cliname, sizeof(cliname), "/tmp/CLI-%05d", clipid);

  printf("Client Name: %s\n", cliname);
  if ((sd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
  {
    perror("Erro a criar socket");
    exit(-1);
  }

  my_addr.sun_family = AF_UNIX;
  memset(my_addr.sun_path, 0, sizeof(my_addr.sun_path));
  strcpy(my_addr.sun_path, cliname);
  addrlen = sizeof(my_addr.sun_family) + strlen(my_addr.sun_path);

  if (bind(sd, (struct sockaddr *)&my_addr, addrlen) < 0)
  {
    perror("Erro no bind");
    exit(-1);
  }

  tv.tv_sec = 2;

  if (setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
  {
    perror("Timeout\n");
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
    printf("%s\nCant connect to server, try again later.\n%s", KRED, KWHT);
    closeServer();
    exit(0);
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
    printf("%s\nReceive error! Please reset intgest.\n\n%s", KRED, KWHT);
    closeServer();
    exit(-1);
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
  //system("clear");
  printf("\n\nStopping client...\n");
  close(sd);
  unlink(CLINAME);
  printf("\nDone!\n");
}
