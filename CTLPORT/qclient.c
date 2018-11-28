#include "structs.h"

char cliname[10];
struct mq_attr ma;
char message[NDIG+1];
char servmsg[30];
int mqids, mqidc;
int cliid;
doorcomm_t cache;
doorcomm_t askDoor;

int validacao(doorcomm_t cache, const char* message){
    int i,j,contador=0;

    for(i=0;i<UMAX;i++){
        for (j=0;j<NDIG+1;j++){
            if(message[j]==cache.id[i][j]){
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

int main()
{
    
    //strcpy(cache.porta,"/A");

    ma.mq_flags = 0;
    ma.mq_maxmsg = 2;
    ma.mq_msgsize = sizeof(doorcomm_t);
    printf("%d\n", sizeof(doorcomm_t));
    
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


    



    printf("Introduza o identificador:"); // Pede o identificador ao utilizador
    fgets(message, NDIG+1, stdin);


    //askDoor.porta = 'A';
    strcpy(askDoor.cid, cliname);
    if (mq_send(mqids, &askDoor, sizeof(doorcomm_t), 0) < 0) { //Envia a mensagem para o servidor
        perror("Controlador: erro a enviar mensagem");
    }
    if (mq_receive(mqidc, &cache, sizeof(cache), NULL) < 0) { // recebe os ids de todos os utilizadores
        perror("Controlador: erro a receber mensagem");
    }

    if (validacao(cache, message)){        // Faz a validacao
        //strcpy(servmsg,"Identificador valido");
        printf("Identificador valido\n");
    }
    else{
        //strcpy(servmsg,"identificador nao valido");
        printf("Identificador nao valido\n");
    }
    
    
    if (mq_unlink(cliname) < 0) {
    perror("Controlador: Erro a eliminar queue controlador");
    }

  return 0;
}
