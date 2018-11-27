#include "server.h"


message_t msgIN;
message_t msgOUT;
int threadID;
pthread_t  thread;

void *thread_func(void * pi)
{
  initQueue();
  while(1){
      //check msg?
  }
}


int main()
{

    splashscreen();


        if (pthread_create(&thread, NULL, thread_func, (void *)&threadID) != 0) {
            printf("Error Creating Door Thread\n");
        }
    

        //init intgest serv
        serverInit();
        while(1){
            msgIN = recieveMessage();
            
            if(strcmp(msgIN.header, "TSERV") == 0){
            closeServer();
            break;                
            }
            
            sendMessage(intgestParser(msgIN));

        }
        

     




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

   
  
  
  
  
                                      