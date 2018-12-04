/*

***********************************************************************************
----------------------------------------SERVER.c-----------------------------------

    -> Main program .c file. In charge of stating the comms and answering messages

    -> server.h keeps necesary libraries and contants and function prototypes

    -> 
-----------------------------------------------------------------------------------
***********************************************************************************
*/


#include "server.h"


message_t msgIN;
message_t msgOUT;
int threadID;
pthread_t  thread;

void *thread_func(void * pi)  //Door answer thread
{
  doorcomm_t msgIN;
  initQueue();
  while(1){
      //printf("\n");
      msgIN=recieveQMessage();
      printf("Recieved query ID: %s\n", msgIN.id[0]);
  }
}


int main()
{

    splashscreen(); //good stuff right here ;)

    if (pthread_mutex_init(&lockUsers, NULL) != 0) //user array mutex initialization
    {
        printf("\n mutex init failed\n");
        return 1;
    }


    serverInit();


    if (pthread_create(&thread, NULL, thread_func, (void *)&threadID) != 0) {
        printf("Error Creating Door Thread\n");
    }
        
        while(1){                                  // main server (socket) loop 
            msgIN = recieveMessage();
            
            if(strcmp(msgIN.header, "TSERV") == 0){
            closeServer();
            break;                
            }
            
            sendMessage(intgestParser(msgIN));

        }
        

     



    pthread_mutex_destroy(&lockUsers);
    return 0;
}




void splashscreen(){

system("clear");
printf("\n\n");
printf("-------------------------------------------------------\n");
printf("|         _____ __________ _    ____________          |  \n");
printf("|        / ___// ____/ __ \\ |  / / ____/ __ \\         | \n");
printf("|        \\__ \\/ __/ / /_/ / | / / __/ / /_/ /         |  \n");
printf("|       ___/ / /___/ _, _/| |/ / /___/ _, _/          |  \n");
printf("|      /____/_____/_/ |_| |___/_____/_/ |_|           |  \n");
printf("|      Programacao de Sistemas Computacionais         |  \n");
printf("|  Afonso Muralha | Miguel Dias | Tomas Bettencourt   |  \n");
printf("|                                                     |  \n");
printf("-------------------------------------------------------");

printf("\n\n");
}

   
  
  
  
  
                                      