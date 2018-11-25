#include "management.h"


message_t intgestParser(uti_t usersBuffer[UMAX], message_t msgIN){
    uti_t user;
    message_t msgOUT;

    if(strcmp(msgIN.header, "NUTI") == 0){
        //add new user function
        int i = 0;
        for(i ; i<UMAX ; i++){
            if(usersBuffer[i].id != NULL)
            break;
        }
        //mutex?
        strcpy(usersBuffer[i].id, msgIN.reguti[0].id);
        strcpy(usersBuffer[i].nome, msgIN.reguti[0].nome);
        strcpy(usersBuffer[i].port, msgIN.reguti[0].port);

        strcpy(msgOUT.header, "NUTIDONE");
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

