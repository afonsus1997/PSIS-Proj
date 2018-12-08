/*

***********************************************************************************
------------------------------------MANAGEMENT.c-----------------------------------

    -> Has all the functions needed for user and message processing

    -> management.h keeps necessary libraries and constants and function prototypes

    -> 
-----------------------------------------------------------------------------------
***********************************************************************************
*/
#include "management.h"

uti_t usersBuffer[UMAX];

int initFileSystem(){
    int i, mfdFUTI; 
    if ((mfdFUTI=open(FUTI, O_RDWR | O_CREAT, 0666 )) < 0) { /* abrir / criar ficheiro */
        perror("Erro a criar ficheiro"); exit(-1);
    }  
    else {
        if (ftruncate(mfdFUTI, sizeof(usersBuffer[UMAX])) < 0) { /* definir tamanho do ficheiro*/
            perror("Erro no ftruncate"); exit(-1);
                }
        }
 /* mapear ficheiro */
    if ((pa=mmap(NULL, sizeof(usersBuffer[UMAX]), PROT_READ|PROT_WRITE, MAP_SHARED, mfdFUTI, 0)) < (char *)0) {
        perror("Erro em mmap"); exit(-1);
    }
 /* aceder ao ficheiro através da memória */
    for (i=0; i<sizeof(usersBuffer[UMAX]); i++) pa[i]='A';
    munmap(pa, sizeof(usersBuffer[UMAX])); close(mfdFUTI);
    return 0;
}


int checkEmpty(int pos){

    int i;
    for(i = 0; i < NDIG; i++)
    {
        if(usersBuffer[pos].id[i] != '\0'){
            return 0;
        }
    }
    return 1;

}

int checkEmptyMsg(char string[NDIG+1]){
   int i;
    for(i = 0; i < NDIG; i++)
    {
        if(string[i] != '\0'){
            return 0;
        }
    }
    return 1; 
}

void printPorts(char ports[NPOR+1]){
    int i;
    for(i=0 ; i<NPOR ; i++){
        if(ports[i] == '1'){
            if(i==0) printf(" %c", 'A');
            if(i==1) printf(" %c", 'B');
            if(i==2) printf(" %c", 'C');
        }
    }
}

message_t intgestParser(message_t msgIN){
    uti_t user;
    message_t msgOUT;

    if(strcmp(msgIN.header, "NUTI") == 0){
        
        
        //add new user function
        int i = 0;
        for(i ; i<UMAX-1 ; i++){

            if(checkEmpty(i))            
            break;

        }
        pthread_mutex_lock(&lockUsers);
        strcpy(usersBuffer[i].id, msgIN.reguti[0].id);
        strcpy(usersBuffer[i].nome, msgIN.reguti[0].nome);
        int j;

        usersBuffer[i].port[0] = '0';    //
        usersBuffer[i].port[1] = '0';    //  DO THIS IN A BETTER WAY PLEEEASE
        usersBuffer[i].port[2] = '0';    //

        for(j=0 ; j<NPOR ; j++){
            if(msgIN.reguti[0].port[j] == 'A'){
                usersBuffer[i].port[0] = '1';    
            }
            else if(msgIN.reguti[0].port[j] == 'B'){
                usersBuffer[i].port[1] = '1';    
            }
            else if(msgIN.reguti[0].port[j] == 'C'){
                usersBuffer[i].port[2] = '1';    
            }
        }
        pthread_mutex_unlock(&lockUsers);

        printf("New User:\n");
        printf("\tID: %s\n", msgIN.reguti[0].id);
        printf("\tNOME: %s\n", msgIN.reguti[0].nome);
        printf("\tPORTAs:"); printPorts(usersBuffer[i].port); printf("\n\n");


        strcpy(msgOUT.header, "User created!");
        return msgOUT;
    }
    else if(strcmp(msgIN.header, "LUTI") == 0)
    {
        //get user list
        int i = 0;
        if(strcmp(msgIN.reguti[0].id, "0")==0){
            
            for(i = 0; i < UMAX; i++)
            {
                if(usersBuffer[i].id != NULL){
                    strcpy(msgOUT.reguti[i].id, usersBuffer[i].id);
                    strcpy(msgOUT.reguti[i].nome, usersBuffer[i].nome);
                    strcpy(msgOUT.reguti[i].port, usersBuffer[i].port);
                }
            }
        }
        else{
            for(i = 0; i < UMAX; i++)
            {
                if(strcmp(usersBuffer[i].id, msgIN.reguti[0].id) == 0){
                    strcpy(msgOUT.reguti[0].id, usersBuffer[i].id);
                    strcpy(msgOUT.reguti[0].nome, usersBuffer[i].nome);
                    strcpy(msgOUT.reguti[0].port, usersBuffer[i].port);
                }
            }
        }
        
        strcpy(msgOUT.header, "Done");
        return msgOUT;
    }
    else if(strcmp(msgIN.header, "EUTI") == 0)
    {
        //delete user

        int i;
        for(i = 0; i < UMAX-1; i++)
        {
            if(strcmp(usersBuffer[i].id, msgIN.reguti[0].id) == 0){
                
                printf("Deleted User:\n");
                printf("\tID: %s\n", usersBuffer[i].id);
                printf("\tNOME: %s\n", usersBuffer[i].nome);
                printf("\tPORTAs:"); printPorts(usersBuffer[i].port); printf("\n\n");
                pthread_mutex_lock(&lockUsers);
                memset(&usersBuffer[i], '\0', sizeof(uti_t));
                pthread_mutex_unlock(&lockUsers);
                

                break;
            }
        }

        strcpy(msgOUT.header, "Deleted Specified user");
        return msgOUT;
    }
    else if(strcmp(msgIN.header, "MPU") == 0)
    {
        //modify access

        if(strcmp(msgIN.reguti[0].id, "0")==0){
            int i;
            for(i = 0; i < UMAX-1; i++)
            {   
                if(strcmp(usersBuffer[i].id, "\000") != 0){
                pthread_mutex_lock(&lockUsers);
                strcpy(usersBuffer[i].port, msgIN.reguti[0].port);
                pthread_mutex_unlock(&lockUsers);
                printf("Modified User:\n");
                printf("\tID: %s\n", usersBuffer[i].id);
                printf("\tPORTAs:"); printPorts(usersBuffer[i].port); printf("\n\n");
                }
            }
        }
        else{
            int i;
            for(i = 0; i < UMAX-1; i++)
            {
                if(strcmp(usersBuffer[i].id, msgIN.reguti[0].id) ==0){
                    pthread_mutex_lock(&lockUsers);
                    strcpy(usersBuffer[i].port, msgIN.reguti[0].port);
                    pthread_mutex_unlock(&lockUsers);
                    printf("Modified User:\n");
                    printf("\tID: %s\n", usersBuffer[i].id);
                    printf("\tPORTAs:"); printPorts(usersBuffer[i].port); printf("\n\n");
                    break;
                }
            }
        }

        strcpy(msgOUT.header, "MPUDONE");
        return msgOUT;
    }
    else if(strcmp(msgIN.header, "LAPU") == 0)
    {
        //list acesses
        strcpy(msgOUT.header, "LAPUDONE");
        return msgOUT;   
    }
    else if(strcmp(msgIN.header, "CEP") == 0)
    {
        //consult door state
        strcpy(msgOUT.header, "CEPDONE");
        return msgOUT;   
    }
    else if(strcmp(msgIN.header, "MEP") == 0)
    {
        //edit door state
        strcpy(msgOUT.header, "MEPDONE");
        return msgOUT;   
    }
    else if(strcmp(msgIN.header, "RIP") == 0)
    {
        //RIPALL!!!
        strcpy(msgOUT.header, "RIPDONE");
        return msgOUT;   
    }
    else{
        strcpy(msgOUT.header, "INVALIDH");
        return msgOUT;   
    }

}





int checkAccess(char door, char doors[NPOR+1]){
    if(door == 'A')
    return doors[0] == '1';
    else if(door == 'B')
    return doors[1] == '1';
    else if(door == 'C')
    return doors[2] == '1';
    else return 0;
}

//----------QUEUES--------

int answerDoor(){
    doorcomm_t outQMsg;
    doorcomm_t inQMsg = recieveQMessage();
    printf("Recieved query ID from door : %c\n", inQMsg.porta);
    int i,j=0;
    for(i = 0;i < UMAX;i++)
    {
       if(checkAccess(inQMsg.porta, usersBuffer[i].port)){
           strcpy(outQMsg.id[j++], usersBuffer[i].id);
           //j++;
       } 
    }
    outQMsg.porta = inQMsg.porta;
    sendQMessage(inQMsg, outQMsg);


  
  
}

