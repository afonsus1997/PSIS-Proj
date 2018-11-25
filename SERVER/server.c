#include "server.h"

pid_t mypid;
pid_t pid;

message_t msgIN;
message_t msgOUT;


int main()
{

    splashscreen();

    if ((pid = fork()) == 0) {
        /*-----------FILHO-----------*/
        mypid = getpid(); //get my pid
    }
    else{
        /*-------------PAI-----------*/
        mypid = getpid();

        //init intgest serv
        serverInit();
        initStruct();
        while(1){
            msgIN = recieveMessage();
            
            if(strcmp(msgIN.header, "TSERV") == 0){
            closeServer();
            break;                
            }
            
            sendMessage(intgestParser(msgIN));

        }
        

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

   
  
  
  
  
                                      