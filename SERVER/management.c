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


message_t intgestParser(message_t msgIN){
    uti_t user;
    message_t msgOUT;

    if(strcmp(msgIN.header, "NUTI") == 0){
        
        printf("New User:\n");
        printf("\tID: %s\n", msgIN.reguti[0].id);
        printf("\tNOME: %s\n", msgIN.reguti[0].nome);
        printf("\tPORTAs: %s\n\n", msgIN.reguti[0].port);

        //add new user function
        int i = 0;
        for(i ; i<UMAX-1 ; i++){

            if(checkEmpty(i))            
            break;

        }
        pthread_mutex_lock(&lockUsers);
        strcpy(usersBuffer[i].id, msgIN.reguti[0].id);
        strcpy(usersBuffer[i].nome, msgIN.reguti[0].nome);
        strcpy(usersBuffer[i].port, msgIN.reguti[0].port);
        pthread_mutex_unlock(&lockUsers);

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
                printf("\tPORTAs: %s\n\n", usersBuffer[i].port);
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
                printf("\tPORTAs: %s\n\n", usersBuffer[i].port);
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
                    printf("\tPORTAs: %s\n\n", usersBuffer[i].port);
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
    return (door == doors[0] || door == doors[1] || door == doors[2]);
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

