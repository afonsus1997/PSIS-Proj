/*
***********************************************************************************
----------------------------------------QSERV.c-----------------------------------

    -> Has all the functions needed for the queue comm with the doors

    -> qserv.h keeps necessary libraries and contants and function prototypes

    -> 
-----------------------------------------------------------------------------------
***********************************************************************************
*/

#include "qserv.h"

struct mq_attr ma;

int initQueue()
{
  /*
 * Function:  initQueue 
 * --------------------
 *  Initializes Queues. 
 * 
 *  Returns:
 *      1: If successful
 *      0: If not successful
 */
  ma.mq_flags = 0;
  ma.mq_maxmsg = 2;
  ma.mq_msgsize = sizeof(doorcomm_t);
  printf("\nStarting Queue...\n");
  if ((mqids = mq_open(SERVNAME, O_RDWR | O_CREAT, 0666, &ma)) < 0)
  {
    perror("Servidor: Erro a criar queue servidor");
    exit(-1);
  }
  printf("Done.\n\n");

  printf("\nReady\n\n");
}

int sendQMessage(doorcomm_t inQMsg, doorcomm_t outQMsg)
{
  /*
 * Function:  sendQMessage 
 * --------------------
 *  Sends a message of type doorcomm_t using POSIX queues. 
 * 
 *  Returns:
 *      1: If successful
 *      0: If not successful
 */

  if ((mqidc = mq_open(inQMsg.cid, O_RDWR)) < 0)
  {
    perror("Servidor: Erro a associar a queue cliente");
  }
  if (mq_send(mqidc, &outQMsg, sizeof(doorcomm_t), 0) < 0)
  {
    perror("Servidor: erro a enviar mensagem");
  }
}

doorcomm_t recieveQMessage()
{
  /*
 * Function:  recieveQMessage 
 * --------------------
 *  Recieves a message of type doorcomm_t using POSIX queues. 
 * 
 *  Returns:
 *      (doorcomm_t) message
 */
  doorcomm_t inQMsg;
  if (mq_receive(mqids, &inQMsg, sizeof(doorcomm_t), NULL) < 0)
  {
    perror("Servidor: erro a receber mensagem");
  }
  return inQMsg;
}

int closeQServer()
{
  /*
 * Function:  closeQServer 
 * --------------------
 *  Unlinks POSIX Queue. 
 * 
 *  Returns:
 *      1:?
 *      0:?
 */
  mq_unlink(SERVNAME);
  //perror("Servidor: Erro a eliminar queue servidor");
}
