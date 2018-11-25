#include "management.h"

uti_t usersBuffer[UMAX];

void initStruct(){

    int i;
        for(i = 0; i < UMAX; i++)
        {
            memset(&usersBuffer[i].id, 0, sizeof(usersBuffer[i].id));
        }

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
            if(usersBuffer[i].id[1] == '\0' && usersBuffer[i].id[1] == '\0' && usersBuffer[i].id[1] == '\0')
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
        for(i = 0; i < UMAX; i++)
        {
            if(usersBuffer[i].id != NULL){
                strcpy(msgOUT.reguti[i].id, usersBuffer[i].id);
                strcpy(msgOUT.reguti[i].nome, usersBuffer[i].nome);
                strcpy(msgOUT.reguti[i].port, usersBuffer[i].port);
            }
        }
        strcpy(msgOUT.header, "LUTIDONE");
        return msgOUT;
    }
    else if(strcmp(msgIN.header, "EUTI") == 0)
    {
        //delete user

        int i;
        for(i = 0; i < UMAX; i++)
        {
            if(usersBuffer[i].id == msgIN.reguti[0].id){
                memset(&usersBuffer[i], 0, sizeof(uti_t));
                break;
            }
        }

        strcpy(msgOUT.header, "EUTIDONE");
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



