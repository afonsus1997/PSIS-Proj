#include "structs.h"
pthread_t thread;
int threadID;

doorcomm_t msgIN;
doorcomm_t askDoor;
doorcomm_t doorAnswer;


extern doorcomm_t receiveQMessage();
extern sendQMessage(doorcomm_t inMsg);
extern int clientQinit();
extern int clientQClose();
extern int processMessage(doorcomm_t answer);

void *thread_func(void * pi)  //Door answer thread
{
    
    while(1){
        
        processMessage(receiveQMessage());

        
    }
}


int main(int argc, char *argv[])
{
    splashscreen();
    clientDoor = argv[1][0];
    printf("Porta %c\n", clientDoor);
    //if (sem_init(&semThread, 0, 0) != 0) {printf("Erro a inicializar semaforo da thread\n"); return -1;}
    //if (sem_init(&semMain, 0, 0) != 0) {printf("Erro a inicializar semaforo principal\n"); return -1;}

    sem_init(&semThread, 0, 0);
    sem_init(&semMain, 0, 0);

    ma.mq_flags = 0;
    ma.mq_maxmsg = 2;
    ma.mq_msgsize = sizeof(doorcomm_t);

    if(clientQinit() < 0){printf("Erro ao inicializar Queueeue\n");}
   

   if (pthread_create(&thread, NULL, thread_func, (void *)&threadID) != 0) {
        printf("Error Creating Door Thread\n");
   }


    while(1){
        printf("Introduza o identificador: "); // Pede o identificador ao utilizador
        fgets(readBuf, sizeof(readBuf), stdin);
        strcpy(askDoor.id[0], readBuf);

        askDoor.porta = clientDoor;
        strcpy(askDoor.cid, cliname);
        
        if(sendQMessage(askDoor) < 0 ){/*Sem ligacao ao server, verificar na cache*/}
        
        sem_post(&semThread);
        sem_wait(&semMain);
    }
    
    if(clientQClose() < 0){printf("Erro ao fechar Queueeue\n");}

  return 0;
}

void splashscreen(){

system("clear");
printf("\n\n%s", KGRN);
printf("-------------------------------------------------------\n");
printf("|      %s ______________    ____  ____  ____  ____ %s     |\n", KWHT, KGRN);
printf("|      %s/ ____/_  __/ /   / __ \\/ __ \\/ __ \\/ __ \\%s     |\n", KWHT, KGRN);
printf("|     %s/ /     / / / /   / / / / / / / / / / /_/ /%s     |\n", KWHT, KGRN);
printf("|    %s/ /___  / / / /___/ /_/ / /_/ / /_/ / _, _/ %s     |\n", KWHT, KGRN);
printf("|    %s\\____/ /_/ /_____/_____/\\____/\\____/_/ |_| %s      |\n", KWHT, KGRN);
printf("|      %sProgramacao de Sistemas Computacionais%s         |  \n", KWHT, KGRN);
printf("|  %sAfonso Muralha | Miguel Dias | Tomas Bettencourt%s   |  \n", KWHT, KGRN);
printf("|                                                     |  \n");
printf("-------------------------------------------------------");

printf("%s\n\n", KWHT);
}