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
        //mutex?
        strcpy(usersBuffer[i].id, msgIN.reguti[0].id);
        strcpy(usersBuffer[i].nome, msgIN.reguti[0].nome);
        strcpy(usersBuffer[i].port, msgIN.reguti[0].port);

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
                
                memset(&usersBuffer[i], '\0', sizeof(uti_t));
                break;
            }
        }

        strcpy(msgOUT.header, "Deleted Specified user");
        return msgOUT;
    }
    else if(strcmp(msgIN.header, "MPU") == 0)
    {
        //modify access

        if(msgIN.reguti[0].id == '0'){
            int i;
            for(i = 0; i < UMAX; i++)
            {   
                strcpy(usersBuffer[i].port, msgIN.reguti[0].port);
            }
        }
        else{
            int i;
            for(i = 0; i < UMAX; i++)
            {
                if(usersBuffer[i].id == msgIN.reguti[0].id){
                    strcpy(usersBuffer[i].port, msgIN.reguti[0].port);
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



