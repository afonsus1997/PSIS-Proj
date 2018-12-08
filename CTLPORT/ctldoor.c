#include "structs.h"
pthread_t thread;
int threadID;
sem_t semThread;
sem_t semMain;
doorcomm_t msgIN;
doorcomm_t askDoor;

char clientDoor;

extern doorcomm_t receiveQMessage();
extern sendQMessage(doorcomm_t inMsg);
extern int clientQinit();
extern int clientQClose();


void *thread_func(void * pi)  //Door answer thread
{
    doorcomm_t doorAnswer;
    while(1){
        //printf("thread waiting\n");
        sem_wait(&semThread);
        //printf("thread going\n");
        askDoor.porta = clientDoor;
        strcpy(askDoor.cid, cliname);
        
        if(sendQMessage(askDoor) < 0 ){/*Sem ligacao ao server, verificar na cache*/}
        else{
            //receber msg
            doorAnswer = receiveQMessage();
            //update cache
            updateCache(doorAnswer);
            //verifica na cache
            checkCache(&askDoor.id[0][0]);
        }
        sem_post(&semMain);
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

    if (pthread_create(&thread, NULL, thread_func, (void *)&threadID) != 0) {
        printf("Error Creating Door Thread\n");
    }

    if(clientQinit() < 0){printf("Erro ao inicializar Queueeue\n");}

    while(1){
        printf("Introduza o identificador: "); // Pede o identificador ao utilizador
        fgets(readBuf, sizeof(readBuf), stdin);
        strcpy(askDoor.id[0], readBuf);
        sem_post(&semThread);
        sem_wait(&semMain);
    }
    
    if(clientQClose() < 0){printf("Erro ao fechar Queueeue\n");}

  return 0;
}

void splashscreen(){

system("clear");
printf("\n\n");
printf("-------------------------------------------------------\n");
printf("|       ______________    ____  ____  ____  ____      |\n");
printf("|      / ____/_  __/ /   / __ \\/ __ \\/ __ \\/ __ \\     |\n");
printf("|     / /     / / / /   / / / / / / / / / / /_/ /     |\n");
printf("|    / /___  / / / /___/ /_/ / /_/ / /_/ / _, _/      |\n");
printf("|    \\____/ /_/ /_____/_____/\\____/\\____/_/ |_|       |\n");
printf("|      Programacao de Sistemas Computacionais         |  \n");
printf("|  Afonso Muralha | Miguel Dias | Tomas Bettencourt   |  \n");
printf("|                                                     |  \n");
printf("-------------------------------------------------------");

printf("\n\n");
}