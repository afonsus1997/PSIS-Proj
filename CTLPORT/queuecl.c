#include "structs.h"



int sendQMessage(doorcomm_t inMsg){
    
    //clientQClose();
    if ((mqids=mq_open(SERVQ, O_RDWR), 0666, &ma) < 0) {
        perror("Cliente: Erro a associar a queue servidor");
    }

    if (mq_send(mqids, &inMsg, sizeof(doorcomm_t), 0) == -1) { //Envia a mensagem para o servidor
        //perror("");
        return 0;
    }
    return 1; 
}

doorcomm_t receiveQMessage(){
    doorcomm_t outMsg;
    if (mq_receive(mqidc, &outMsg, sizeof(doorcomm_t), NULL) < 0) { // recebe os ids de todos os utilizadores
        //perror("Controlador: erro a receber mensagem");
    }
    return outMsg;
    //timeout
}

int clientQinit(){
    if(clientDoor == 'A'){
        strcpy(cliname, CTLA);
    }
    else if(clientDoor == 'B'){
        strcpy(cliname, CTLB);
    }
    else if(clientDoor == 'C'){
        strcpy(cliname, CTLC);
    }
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
