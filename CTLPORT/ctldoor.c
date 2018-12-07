#include "structs.h"

char cliname[10];
struct mq_attr ma;
char message[NDIG+1];
char servmsg[30];
int mqids, mqidc;
int cliid;
doorcomm_t msgIN;
doorcomm_t askDoor;

char clientDoor;
pthread_t thread;
int threadID;
sem_t semThread;
sem_t semMain;

int sendQMessage(doorcomm_t inMsg){
    if (mq_send(mqids, &inMsg, sizeof(doorcomm_t), 0) < 0) { //Envia a mensagem para o servidor
        perror("Controlador: erro a enviar mensagem");
        return -1;
    }
    return 0;
}

doorcomm_t receiveQMessage(){
    doorcomm_t outMsg;
    if (mq_receive(mqidc, &outMsg, sizeof(doorcomm_t), NULL) < 0) { // recebe os ids de todos os utilizadores
        perror("Controlador: erro a receber mensagem");
    }
    return outMsg;
    //timeout
}

int updateCache(doorcomm_t answer){
    int i;
    for(i = 0;i < UMAX; i++)
    {  
       if(strcmp(answer.id[i], "\000")==0)
           memset(&usersCache[i], '\0', NDIG+1);
       else
        strcpy(usersCache[i], answer.id[i]); 
    }
}

int checkCache(char id[NDIG+1]){
    int i;        
    for(i=0 ; i < UMAX ; i++){
        if(strcmp(usersCache[i], id) == 0)
        printf("\nAccess Granted!\n");
        return 1;
    }
    printf("\nAccess Denied!\n");
    return 0;        
}

void *thread_func(void * pi)  //Door answer thread
{
    doorcomm_t doorAnswer;
    sem_wait(&semThread);
    askDoor.porta = clientDoor;
    strcpy(askDoor.cid, cliname);
    
    if(sendQMessage(askDoor) < 0 ){/*Sem ligacao ao server, verificar na cache*/}
    else{
        //receber msg
        doorAnswer = receiveQMessage();
        //update cache
        updateCache(doorAnswer);
        //verifica na cache
        checkCache(askDoor.id);
        

    }

    

    
    


    sem_post(&semMain);
  
}

int clientQinit(){
    snprintf(cliname, sizeof(cliname), "/CL-%05d", getpid());
    mq_unlink(cliname);
    if ((mqidc=mq_open(&cliname, O_RDWR|O_CREAT, 0666, &ma)) < 0) {
        perror("Cliente: Erro a criar queue cliente");
        exit(-1);
    }

    if ((mqids=mq_open(SERVQ, O_RDWR), 0666, &ma) < 0) {
        perror("Cliente: Erro a associar a queue servidor");
        exit(-1);
    }
    return 1;
}



int clientQClose(){
    if (mq_unlink(cliname) < 0) {
    perror("Controlador: Erro a eliminar queue controlador");
    return -1;
    }
    return 0;
}

int validacao(doorcomm_t msgIN, char msgId[NDIG+1]){
    int i,j,contador=0;

    for(i=0;i<UMAX;i++){
        for (j=0;j<NDIG+1;j++){
            if(msgId[j]==msgIN.id[i][j]){
                contador ++;     //verifica se todos os 4 digitos do identificador sao iguais
            }
        }
    }
    if (contador ==4){
        return 1;
    }
    else{
        return 0;
    }
}

int main(int argc, char *argv[])
{
    splashscreen();
    clientDoor = argv[1][0];
    printf("Porta %c\n", clientDoor);
    if (sem_init(&semThread, 0, 0) != 0) {printf("Erro a inicializar semaforo da thread\n"); return -1;}
    if (sem_init(&semMain, 0, 0) != 0) {printf("Erro a inicializar semaforo principal\n"); return -1;}

    ma.mq_flags = 0;
    ma.mq_maxmsg = 2;
    ma.mq_msgsize = sizeof(doorcomm_t);


    if (pthread_create(&thread, NULL, thread_func, (void *)&threadID) != 0) {
        printf("Error Creating Door Thread\n");
    }

    if(clientQinit() < 0){printf("Erro ao inicializar Queueeue\n");}
    

    while(1){
        printf("Introduza o identificador: "); // Pede o identificador ao utilizador
        fgets(askDoor.id, NDIG+1, stdin);
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