
#include "structs.h"

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
    for(i=0 ; i < UMAX ; i++){
        if(strcmp(usersCache[i], id) == 0){
            printf("\nAccess Granted!\n\n");
            return 1;
        }
        
    }
    printf("\nAccess Denied!\n\n");
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
