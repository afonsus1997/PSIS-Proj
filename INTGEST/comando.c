#ifndef COMANDO_h
#define COMANDO_h

#include "structs.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#endif

extern int closeServer(void);
extern message_t recieveInfo();
extern int sendInfo(message_t *msg);
extern struct timespec stringToTimespec(char string[26]);


void printPorts(char ports[NPOR + 1])
{
  /*
 * Function:  printPorts 
 * --------------------
 *  Helper fucntion to print ports.
 * 
 *  Returns:
 *      (void)
 */
  int i;
  for (i = 0; i < NPOR; i++)
  {
    if (ports[i] == '1')
    {
      if (i == 0)
        printf(" %c", 'A');
      if (i == 1)
        printf(" %c", 'B');
      if (i == 2)
        printf(" %c", 'C');
    }
  }
}

int nuti(int argc, char **argv)
/*
 * Function:  nuti 
 * --------------------
 *  Handles the nuti command.
 * 
 *  Returns:
 *      -1: If missing parameters
 */
{
  message_t msgOut;
  message_t msgIn;
  if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
  {
    return -1;
  }
  strcpy(msgOut.header, "NUTI");
  strcpy(msgOut.reguti[0].id, argv[1]);
  strcpy(msgOut.reguti[0].nome, argv[2]);
  strcpy(msgOut.reguti[0].port, argv[3]);
  if(sendInfo(&msgOut))
    recieveInfo();
}

int luti(int argc, char **argv)
/*
 * Function:  luti 
 * --------------------
 *  Handles the luti command.
 * 
 *  Returns:
 *      -1: If missing parameters
 */
{
  message_t msgOut;
  message_t msgIn;

  if (argv[1] == NULL)
  {
    return -1;
  }

  strcpy(msgOut.header, "LUTI");
  strcpy(msgOut.reguti[0].id, argv[1]);
  sendInfo(&msgOut);
  msgIn = recieveInfo();
  //if(strcmp(msgIn.header, "DONE")==0){
  int i;
  if (strcmp(msgOut.reguti[0].id, "0") != 0 && strcmp(msgIn.header, "Done") == 0)
  {
    printf("Users:\n");
    printf("\tID: %s\n", msgIn.reguti[0].id);
    printf("\tNOME: %s\n", msgIn.reguti[0].nome);
    printf("\tPORTAs:");
    printPorts(msgIn.reguti[0].port);
    printf("\n\n");
  }
  else
  {
    for (i = 0; i < UMAX - 1; i++)
    {
      if (strcmp(msgIn.reguti[i].id, "\0") != 0 && strcmp(msgIn.header, "Done") == 0)
      {
        printf("Users:\n");
        printf("\tID: %s\n", msgIn.reguti[i].id);
        printf("\tNOME: %s\n", msgIn.reguti[i].nome);
        printf("\tPORTAs:");
        printPorts(msgIn.reguti[i].port);
        printf("\n\n");
      }
    }
  }
}

int euti(int argc, char **argv)
{
  /*
 * Function:  euti 
 * --------------------
 *  Handles the euti command.
 * 
 *  Returns:
 *      -1: If missing parameters
 */
  message_t msgOut;
  message_t msgIn;

  if (argv[1] == NULL)
  {
    return -1;
  }

  strcpy(msgOut.header, "EUTI");
  strcpy(msgOut.reguti[0].id, argv[1]);
  sendInfo(&msgOut);
  recieveInfo();
}

int mpu(int argc, char **argv)
/*
 * Function:  mpu 
 * --------------------
 *  Handles the mpu command.
 * 
 *  Returns:
 *      -1: If missing parameters
 */
{
  message_t msgOut;
  message_t msgIn;

  if (argv[1] == NULL || argv[2] == NULL)
  {
    return -1;
  }

  strcpy(msgOut.header, "MPU");
  strcpy(msgOut.reguti[0].id, argv[1]);
  strcpy(msgOut.reguti[0].port, "000");

  int i;
  for (i = 0; i < NPOR - 1; i++)
  {
    if (argv[2][i] == '\0')
      break;
    else
    {
      if (argv[2][i] == 'A')
        msgOut.reguti[0].port[0] = '1';
      else if (argv[2][i] == 'B')
        msgOut.reguti[0].port[1] = '1';
      else if (argv[2][i] == 'C')
        msgOut.reguti[0].port[2] = '1';
    }
  }

  sendInfo(&msgOut);
  recieveInfo();
}

int lapu(int argc, char **argv)
/*
 * Function:  lapu 
 * --------------------
 *  Handles the lapu command.
 * 
 *  Returns:
 *      -1: If missing parameters
 */
{
  if (argv[1] == NULL || argv[2] == NULL)
  {
    return -1;
  }
  message_t msgOut;
  message_t msgIn;
  char timeTemp[26];
  char timeTemp2[26];
  memset(timeTemp, '\0', sizeof(timeTemp));
  memset(timeTemp2, '\0', sizeof(timeTemp));

  strcpy(msgOut.header, "LAPU");
  msgOut.reguti[0].port[0] = argv[1][0];
  strcpy(msgOut.reguti[0].id, argv[2]);
  if (argc == 5)
  {
    sprintf(timeTemp, "%s %s", argv[3], argv[4]);
    msgOut.regt[0].t = stringToTimespec(timeTemp);
    msgOut.regt[1].t.tv_sec = 0;
  }
  else if (argc == 7)
  {
    sprintf(timeTemp, "%s %s", argv[3], argv[4]);
    msgOut.regt[0].t = stringToTimespec(timeTemp);
    sprintf(timeTemp2, "%s %s", argv[5], argv[6]);
    msgOut.regt[1].t = stringToTimespec(timeTemp2);
  }
  else
  {
    msgOut.regt[0].t.tv_sec = 0;
    msgOut.regt[0].t.tv_nsec = 0;

    msgOut.regt[1].t.tv_nsec = 0;
    msgOut.regt[1].t.tv_sec = 0;
  }

  sendInfo(&msgOut);
  msgIn = recieveInfo();
  printf("\n");
  while (strcmp(msgIn.header, "LAPUDONE") != 0)
  {
    lapur(msgIn);
    msgIn = recieveInfo();
  }
}

int lapur(message_t msgIn)
/*
 * Function:  lapur 
 * --------------------
 *  Helper function for the lapu command.
 * 
 *  Returns:
 *      -1: If missing parameters
 */
{

  printf("%s", printTimespecString(msgIn.regt[0].t));
  printf("\tID: %s\n", msgIn.regt[0].id);
  printf("\tPORTA: %c\n", msgIn.regt[0].p);
  printf("\tACCESS: %c\n\n", msgIn.regt[0].ac);
}

int tserv(int argc, char **argv)
/*
 * Function:  tserv 
 * --------------------
 *  Handles the tserv command.
 * 
 *  Returns:
 *      -1: If missing parameters
 */
{
  message_t msgOut;
  message_t msgIn;
  strcpy(msgOut.header, "TSERV");
  sendInfo(&msgOut);
  recieveInfo();
  kill(getpid(), SIGINT);
}

int cep(int argc, char **argv)
{
  /*
 * Function:  cep 
 * --------------------
 *  Handles the cep command.
 * 
 *  Returns:
 *      -1: If missing parameters
 */
  if (argv[1] == NULL)
  {
    return -1;
  }
  message_t msgOut;
  message_t msgIn;
  char door;
  strcpy(msgOut.header, "CEP");
  strcpy(msgOut.reguti[0].port, argv[1]);
  door = msgOut.reguti[0].port[0];
  sendInfo(&msgOut);

  msgIn = recieveInfo();
  printf("\nDoor States:\n");
  if (argv[1][0] == '0')
  {
    printf("\tDoor A: %c\n", msgIn.reguti[0].port[0]);
    printf("\tDoor B: %c\n", msgIn.reguti[0].port[1]);
    printf("\tDoor C: %c\n\n", msgIn.reguti[0].port[2]);
  }
  else
  {
    printf("\tDoor %c state: %c\n\n", door, msgIn.reguti[0].port[0]);
  }
}

int mep(int argc, char **argv)
/*
 * Function:  mep 
 * --------------------
 *  Handles the mep command.
 * 
 *  Returns:
 *      -1: If missing parameters
 */
{
  if (argv[1] == NULL || argv[2] == NULL)
  {
    return -1;
  }
  message_t msgOut;
  message_t msgIn;

  if (argv[1] == NULL || argv[2] == NULL)
  {
    return -1;
  }

  strcpy(msgOut.header, "MEP");
  char buf[5];
  strcpy(buf, argv[1]);
  msgOut.reguti[0].port[0] = buf[0];
  strcpy(buf, argv[2]);
  msgOut.reguti[0].port[1] = buf[0];
  sendInfo(&msgOut);

  recieveInfo();
}

int rip(int argc, char **argv)
/*
 * Function:  rip 
 * --------------------
 *  Handles the rip command.
 * 
 *  Returns:
 *      -1: If missing parameters
 */
{
  if (argv[1] == NULL)
  {
    return -1;
  }
  message_t msgOut;
  message_t msgIn;
  strcpy(msgOut.header, "RIP");
  strcpy(msgOut.reguti[0].port, argv[1]);
  sendInfo(&msgOut);
  recieveInfo();
}

void cmd_sair(int argc, char **argv)
{
  closeServer();
  exit(0);
}
