# include "structs.h"


int validacao(doorcomm_t cache, uti_t utilizador){
    int i,j,contador=0;
    
    for(i=0;i<UMAX;i++){
        for (j=0;j<NDIG+1;j++){
            if(utilizador.id[j]=cache.id[i][j]){
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