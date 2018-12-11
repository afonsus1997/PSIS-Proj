
#include "structs.h"

extern int sendQMessage(doorcomm_t inMsg);
extern int clientQinit();
char doorMode = NORMAL;

int processMessage(doorcomm_t msgQIN){
    doorcomm_t msgQOUT;
    if(strcmp(msgQIN.header, "QUERY") == 0){
        //update cache
        updateCache(msgQIN);
        //verifica na cache
        checkCache(askDoor.id[0]);
        sem_post(&semMain);
        return 1;
    }
    else if(strcmp(msgQIN.header, "CEP") == 0){
        msgQOUT.porta = clientDoor;
        msgQOUT.state = doorMode;
        strcpy(msgQOUT.header, "CEPANS");
        //clientQinit();
        sendQMessage(msgQOUT);
        return 1;
    }
    else if(strcmp(msgQIN.header, "CEP0") == 0){
        msgQOUT.porta = clientDoor;
        msgQOUT.state = doorMode;
        strcpy(msgQOUT.header, "CEPANS0");
        //clientQinit();
        sendQMessage(msgQOUT);
        return 1;
    }
    else if(strcmp(msgQIN.header, "MEP") == 0){

    }
    else if(strcmp(msgQIN.header, "RIP") == 0){
        clearCache();
    }
}

int clearCache(){
    int i;
    for(i = 0; i < UMAX-1; i++){
        memset(usersCache[i], '\0', sizeof(char)*(NDIG+1));
    }
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
    id[NDIG] = '\0';
    int i;
    if(strcmp(id, IDX) == 0){
        printf("\n%sSuperUser detected, Access Granted!%s\n\n", KGRN, KWHT);
        return 1;

    }
        
    for(i=0 ; i < UMAX ; i++){
        if(strcmp(usersCache[i], id) == 0){
            printf("\n%sAccess Granted!%s\n\n", KGRN, KWHT);
            return 1;
        }
        
    }
    printf("\n%sAccess Denied!%s\n\n", KRED, KWHT);
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
