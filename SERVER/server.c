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
pthread_t thread;


void *thread_func(void * pi)  //Door answer thread
{
  doorcomm_t msgIN;
  initQueue();
  while(1){
      //printf("\n");
      answerDoor();
      
  }
}


int main()
{

    splashscreen(); //good stuff right here ;)
    
    initFileSystem();

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
printf("\n\n%s", KYEL);
printf("------------------------------------------------------\n");
printf("|          %s_____ __________ _    ____________ %s       |  \n", KWHT, KYEL);
printf("|         %s/ ___// ____/ __ \\ |  / / ____/ __ \\%s       | \n", KWHT, KYEL);
printf("|         %s\\__ \\/ __/ / /_/ / | / / __/ / /_/ /%s       |  \n", KWHT, KYEL);
printf("|        %s___/ / /___/ _, _/| |/ / /___/ _, _/%s        |  \n", KWHT, KYEL);
printf("|       %s/____/_____/_/ |_| |___/_____/_/ |_|%s         |  \n", KWHT, KYEL);
printf("|      %sProgramacao de Sistemas Computacionais %s       |  \n", KWHT, KYEL);
printf("|  %sAfonso Muralha | Miguel Dias | Tomas Bettencourt%s  |  \n", KWHT, KYEL);
printf("|                                                    |  \n");
printf("------------------------------------------------------");

printf("%s\n\n", KWHT);
}

   
  
  
  
  
                                      