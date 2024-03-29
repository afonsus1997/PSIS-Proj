/*

***********************************************************************************
----------------------------------------SDSRV.c-----------------------------------

    -> Has all the functions needed for the socket comm with the intgest

    -> sdserv.h keeps necessary libraries and constants and function prototypes

    -> 
-----------------------------------------------------------------------------------
***********************************************************************************
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

int sd;
struct sockaddr_un my_addr;
socklen_t addrlen;
struct sockaddr_un from;
socklen_t fromlen;
char buf[100];
message_t msgIN;
extern int closeFileSystem();
extern int closeQServer();

int serverInit()
{
  /*
 * Function:  serverInit 
 * --------------------
 *  Initializes socket comms. 
 * 
 *  Returns:
 *      1: If successful
 *      0: If not successful
 */
  printf("\nStarting Intgest Server...\n");
  unlink(SERVNAME);
  if ((sd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
  {
    perror("Erro a criar socket");
    exit(-1);
  }

  my_addr.sun_family = AF_UNIX;
  memset(my_addr.sun_path, 0, sizeof(my_addr.sun_path));
  strcpy(my_addr.sun_path, SERVNAME);
  addrlen = sizeof(my_addr.sun_family) + strlen(my_addr.sun_path);

  if (bind(sd, (struct sockaddr *)&my_addr, addrlen) < 0)
  {
    perror("Erro no bind");
    exit(-1);
  }
  printf("Done.\n\n");

  return 0;
}

int closeServer()
{
  /*
 * Function:  closeServer 
 * --------------------
 *  Closes program. 
 * 
 *  Returns:
 *      1: If successful
 *      0: If not successful
 */
  closeFileSystem();
  printf("\n\nStopping server...\n");
  closeQServer();
  close(sd);
  unlink(SERVNAME);
  printf("\nDone!\n");
  return 0;
}

message_t recieveMessage()
{
  /*
 * Function:  recieveMessage 
 * --------------------
 *  Receives message of type message_t using Datagram Sockets . 
 * 
 *  Returns:
 *      (message_t) message
 */
  message_t msg;

  if (recvfrom(sd, &msg, sizeof(message_t), 0, (struct sockaddr *)&from, &fromlen) < 0)
  {
    perror("Erro no recvfrom");
  }
  else
  {
    return msg;
  }
}

int sendMessage(message_t msg)
{
  /*
 * Function:  sendMessage 
 * --------------------
 *  Sends message of type message_t using Datagram Sockets . 
 * 
 *  Returns:
 *      1: If successful
 *      0: If not successful
 */
  if (sendto(sd, &msg, sizeof(message_t), 0, (struct sockaddr *)&from, fromlen) < 0)
  {

    printf("Send Error, please reset Intgest without closing this server!\n\n");
    return -1;
  }
  return 0;
}
