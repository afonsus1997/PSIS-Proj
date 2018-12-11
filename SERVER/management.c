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

uti_t *usersBufferFile;
uti_t usersBuffer[UMAX];
char estadoPortas[3];
char cepTemp[3] = {'\0', '\0', '\0'};

int mfdFUTI;
int initFileSystem(){
 /*
 * Function:  initFileSystem 
 * --------------------
 *  Initializes file system and loads users to a buffer 
 *  We are aware that this is not the best way to do it, but changing it would require
 *  redo a big part of the project
 * 
 *  Returns:
 *      1: if completed successfuly
 *      0: if error
 */
    int i, mfdFUTI; 
    if ((mfdFUTI=open(FUTI, O_RDWR | O_CREAT, 0666 )) < 0) { /* abrir / criar ficheiro */
        perror("Erro a criar ficheiro"); exit(-1);
    }  
    else {
        if (ftruncate(mfdFUTI, sizeof(usersBuffer)) < 0) { /* definir tamanho do ficheiro*/
            perror("Erro no ftruncate"); exit(-1);
                }
        }
 /* mapear ficheiro */
    if ((usersBufferFile=(uti_t*)mmap(NULL, sizeof(usersBuffer), PROT_READ|PROT_WRITE, MAP_SHARED, mfdFUTI, 0)) < (uti_t *)0) {
        perror("Erro em mmap"); exit(-1);
    }
    
    clearBuffer();
    printf("Loading users from filesystem:\n\n");
    for(i=0; i<UMAX;i++){
        if(strcmp(usersBufferFile[i].id, "\0")!=0){
        printf("\tID: %s\n", usersBufferFile[i].id);
        printf("\tNOME: %s\n", usersBufferFile[i].nome);
        printf("\tPORTAs:"); printPorts(usersBufferFile[i].port); printf("\n\n");
        usersBuffer[i] = usersBufferFile[i];
        }
    }
    
    return 0;
}

int closeFileSystem(){
/*
 * Function:  closeFileSystem 
 * --------------------
 *  Closes file system and stores current users on local file 
 *  We are aware that this is not the best way to do it, but changing it would require
 *  redo a bit part of the project
 * 
 *  Returns:
 *      1: if completed successfuly
 *      0: if error
 */
    printf("Saving users to filesystem:\n\n");
    int i;
    for(i=0; i<UMAX;i++){
        if(strcmp(usersBuffer[i].id, "\0")!=0){
            usersBufferFile[i] = usersBuffer[i];
            printf("\tID: %s\n", usersBufferFile[i].id);
            printf("\tNOME: %s\n", usersBufferFile[i].nome);
            printf("\tPORTAs:"); printPorts(usersBufferFile[i].port); printf("\n\n");
            
        }
        else
            memset(&usersBufferFile[i], '\0', sizeof(char)*(NDIG+1));
        
    }
    munmap(usersBufferFile, sizeof(usersBuffer)); close(mfdFUTI);
    return 1;
}

int clearBuffer(){
/*
 * Function:  clearBuffer 
 * --------------------
 *  Clears users buffer. This has to be done to avoid sending garbadge to intgest
 * 
 *  Returns:
 *      1: if completed successfuly
 */
    int i;
    for(i = 0; i < UMAX-1; i++){
        memset(&usersBuffer[i], '\0', sizeof(char)*(NDIG+1));
    }
    return 1;
}

int checkEmpty(int pos){
    /*
 * Function:  checkEmpty 
 * --------------------
 *  Checks if users buffer is empty
 * 
 *  Returns:
 *      1: if users buffer is empty
 *      0: if users buffer is not empty
 */
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
   /*
 * Function:  checkEmpty 
 * --------------------
 *  Checks if message is empty
 * 
 *  Returns:
 *      1: if message is empty
 *      0: if message is not empty
 */
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
    /*
 * Function:  printPorts 
 * --------------------
 *  Helper function to print ports
 * 
 */
    int i;
    for(i=0 ; i<NPOR ; i++){
        if(ports[i] == '1'){
            if(i==0) printf(" %c", 'A');
            if(i==1) printf(" %c", 'B');
            if(i==2) printf(" %c", 'C');
        }
    }
}

int CEPHelper(char currDoor){
/*
 * Function:  CEPHelper 
 * --------------------
 *  Handles the communication with the doors for the CEP command.
 *  This function exists in order do reduce spaguetti code 
 * 
 *  Returns:
 *      (char) door state
 */
    doorcomm_t dummyMsg;
    doorcomm_t msgQOUT;
    message_t msgOUT;
    if(currDoor == 'A'){
        strcpy(dummyMsg.cid, CTLA);
        strcpy(msgQOUT.header, "CEP");
        sendQMessage(dummyMsg, msgQOUT);
        return 1;
    }
    else if(currDoor == 'B'){
        strcpy(dummyMsg.cid, CTLB);
        strcpy(msgQOUT.header, "CEP");
        sendQMessage(dummyMsg, msgQOUT);
        return 1;
    }
    else if(currDoor == 'C'){
        strcpy(dummyMsg.cid, CTLC);
        strcpy(msgQOUT.header, "CEP");
        sendQMessage(dummyMsg, msgQOUT);
        return 1;
    }
    else if(currDoor == '0')
    {
        strcpy(dummyMsg.cid, CTLA);
        strcpy(msgQOUT.header, "CEP0");
        sendQMessage(dummyMsg, msgQOUT);

        strcpy(dummyMsg.cid, CTLB);
        strcpy(msgQOUT.header, "CEP0");
        sendQMessage(dummyMsg, msgQOUT);

        strcpy(dummyMsg.cid, CTLC);
        strcpy(msgQOUT.header, "CEP0");
        sendQMessage(dummyMsg, msgQOUT);

        return 1;
    }

        return 0;
        //doorcomm_t msgQIN = recieveQMessage();
        //return msgQIN.state;        
        
}

int MEPHelper(char currDoor, char state){
/*
 * Function:  CEPHelper 
 * --------------------
 *  Handles the communication with the doors for the CEP command.
 *  This function exists in order do reduce spaguetti code 
 * 
 *  Returns:
 *      (char) door state
 */
    doorcomm_t dummyMsg;
    doorcomm_t msgQOUT;
    message_t msgOUT;
    if(currDoor == 'A'){
        strcpy(dummyMsg.cid, CTLA);
        strcpy(msgQOUT.header, "MEP");
        msgQOUT.state = state;
        sendQMessage(dummyMsg, msgQOUT);
        return 1;
    }
    else if(currDoor == 'B'){
        strcpy(dummyMsg.cid, CTLB);
        strcpy(msgQOUT.header, "MEP");
        msgQOUT.state = state;
        sendQMessage(dummyMsg, msgQOUT);
        return 1;
    }
    else if(currDoor == 'C'){
        strcpy(dummyMsg.cid, CTLC);
        strcpy(msgQOUT.header, "MEP");
        msgQOUT.state = state;
        sendQMessage(dummyMsg, msgQOUT);
        return 1;
    }
    else if(currDoor == '0')
    {
        strcpy(dummyMsg.cid, CTLA);
        strcpy(msgQOUT.header, "MEP0");
        msgQOUT.state = state;
        sendQMessage(dummyMsg, msgQOUT);

        strcpy(dummyMsg.cid, CTLB);
        strcpy(msgQOUT.header, "CEP0");
        msgQOUT.state = state;
        sendQMessage(dummyMsg, msgQOUT);

        strcpy(dummyMsg.cid, CTLC);
        strcpy(msgQOUT.header, "CEP0");
        msgQOUT.state = state;
        sendQMessage(dummyMsg, msgQOUT);

        return 1;
    }

        return 0;
        //doorcomm_t msgQIN = recieveQMessage();
        //return msgQIN.state;        
        
}

int intgestParser(message_t msgIN){
/*
 * Function:  intgestParser 
 * --------------------
 *  Checks if message is empty
 * 
 *  Returns:
 *      1: If successful
 *      0: If not successful
 */
    uti_t user;
    message_t msgOUT;
    doorcomm_t msgQOUT;
    doorcomm_t msgQIN;

    if(strcmp(msgIN.header, "NUTI") == 0){
        
        
        //add new user function
        int i;
        for(i = 0; i<UMAX-1; i++){
            if(strcmp(msgIN.reguti[0].id, usersBuffer[i].id) == 0){
                strcpy(msgOUT.header, "User already exists!");
                printf("Error: User already exists\n");
                sendMessage(msgOUT);
                return 1;
            }
        }
        
        for(i = 0 ; i<UMAX-1 ; i++){

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
        sendMessage(msgOUT);
        return 1;
    }
    else if(strcmp(msgIN.header, "LUTI") == 0)
    {
        //get user list
        int j = 0;
        int i = 0;
        if(strcmp(msgIN.reguti[0].id, "0")==0){
            
            for(i = 0; i < UMAX; i++)
            {
                if(strcmp(usersBuffer[i].id, "\0") != 0){
                    strcpy(msgOUT.reguti[i].id, usersBuffer[i].id);
                    strcpy(msgOUT.reguti[i].nome, usersBuffer[i].nome);
                    strcpy(msgOUT.reguti[i].port, usersBuffer[i].port);
                    j++;
                }
                else{
                    memset(&msgOUT.reguti[i].id, '\0', sizeof(char)*(NDIG+1));
                }
            }
            if(j==UMAX-1)
            strcpy(msgOUT.header, "User List Empty");
            else
            strcpy(msgOUT.header, "Done");
            sendMessage(msgOUT);
            return 1;
        }
        else{
            for(i = 0; i < UMAX; i++)
            {
                if(strcmp(usersBuffer[i].id, msgIN.reguti[0].id) == 0){
                    strcpy(msgOUT.reguti[0].id, usersBuffer[i].id);
                    strcpy(msgOUT.reguti[0].nome, usersBuffer[i].nome);
                    strcpy(msgOUT.reguti[0].port, usersBuffer[i].port);
                    strcpy(msgOUT.header, "Done");
                    sendMessage(msgOUT);
                    return 1;
                }
            }
            strcpy(msgOUT.header, "User Not Found");
            sendMessage(msgOUT);
            return 1;
        }
    }
    else if(strcmp(msgIN.header, "EUTI") == 0)
    {
        
        int i;
        if(strcmp(msgIN.reguti[0].id, "0")==0){
            for(i = 0; i < UMAX-1; i++)
            {
                if(strcmp(usersBuffer[i].id, "\0") != 0){
                    printf("Deleted User:\n");
                    printf("\tID: %s\n", usersBuffer[i].id);
                    printf("\tNOME: %s\n", usersBuffer[i].nome);
                    printf("\tPORTAs:"); printPorts(usersBuffer[i].port); printf("\n\n");
                    pthread_mutex_lock(&lockUsers);
                    memset(&usersBuffer[i], '\0', sizeof(uti_t));
                    pthread_mutex_unlock(&lockUsers);
                }
            }
        }
        else{
            
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
        }
        strcpy(msgOUT.header, "Deleted Specified user");
        sendMessage(msgOUT);
        return 1;
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
        sendMessage(msgOUT);
        return 1;
    }
    else if(strcmp(msgIN.header, "LAPU") == 0)
    {
        //list acesses
        strcpy(msgOUT.header, "LAPUDONE");
        sendMessage(msgOUT);
        return 1;   
    }
    else if(strcmp(msgIN.header, "CEP") == 0)
    {
        //consult door state
        doorcomm_t dummyMsg;
        char currDoor = msgIN.reguti[0].port[0];
        char currDoorState;        
        if(currDoor == '0'){
            CEPHelper('0');
        }
        else{
            CEPHelper(currDoor);
        }
           
    }

    else if(strcmp(msgIN.header, "MEP") == 0)
    {
        //edit door state
        strcpy(msgQOUT.header, "MEP");
        if(msgIN.reguti[0].port[0] == '0')
            MEPHelper(msgIN.reguti[0].port[0], msgIN.reguti[0].port[1]); //
        else                                                             // THIS IS STUPID
            MEPHelper(msgIN.reguti[0].port[0], msgIN.reguti[0].port[1]);//


        strcpy(msgOUT.header, "MEPDONE");
        sendMessage(msgOUT);
        return 1;  
    }
    
    

    else if(strcmp(msgIN.header, "RIP") == 0)
    {
        //RIPALL!!!
        strcpy(msgOUT.header, "RIPDONE");
        sendMessage(msgOUT);
        return 1;   
    }
    else{
        strcpy(msgOUT.header, "INVALIDH");
        sendMessage(msgOUT);
        return 1;  
    }

}


int checkAccess(char door, char doors[NPOR+1]){
/*
 * Function:  checkAccess 
 * --------------------
 *  Checks access
 * 
 *  Returns:
 *      1: If has access
 *      0: If it doesent have access
 */
    if(door == 'A')
        return doors[0] == '1';
    else if(door == 'B')
        return doors[1] == '1';
    else if(door == 'C')
        return doors[2] == '1';
    else return 0;
}

//----------QUEUES--------

int answerQuery(doorcomm_t inQMsg){
 /*
 * Function:  answerQuery 
 * --------------------
 *  Answers to user access query on ctldoor 
 * 
 *  Returns:
 *      1
 *      0
 */   
    doorcomm_t outQMsg;
    
    int i,j=0;
    for(i = 0;i < UMAX;i++)
    {
       if(checkAccess(inQMsg.porta, usersBuffer[i].port)){
           strcpy(outQMsg.id[j++], usersBuffer[i].id);
           //j++;
       } 
    }
    outQMsg.porta = inQMsg.porta;
    strcpy(outQMsg.header, "QUERY");
    sendQMessage(inQMsg, outQMsg);
  
}

int processMessage(doorcomm_t msgQIN){
    /*
 * Function:  processMessage 
 * --------------------
 *  Processes Queue message 
 * 
 *  Returns:
 *      1
 *      0
 */ 
    message_t msgOUT;
    printf("Recieved query from door : %c\n\n", msgQIN.porta);
    if(strcmp(msgQIN.header, "QUERY") == 0){
        answerQuery(msgQIN);
    }
    else if(strcmp(msgQIN.header, "CEPANS0") == 0){
        if(strcmp(msgQIN.cid, CTLA) == 0 ){
            cepTemp[0] = msgQIN.state;
        }
        else if(strcmp(msgQIN.cid, CTLB) == 0 ){
            cepTemp[1] = msgQIN.state;
        }
        else if(strcmp(msgQIN.cid, CTLC) == 0 ){
            cepTemp[2] = msgQIN.state;
        }
        
        if(cepTemp[0] != '\0' && cepTemp[1] != '\0' && cepTemp[2] != '\0'){
            msgOUT.reguti[0].port[0] = cepTemp[0];
            msgOUT.reguti[0].port[1] = cepTemp[1];
            msgOUT.reguti[0].port[2] = cepTemp[2];
            strcpy(msgOUT.header, "CEP DONE");
            sendMessage(msgOUT);
            cepTemp[0] = '\0'; cepTemp[1] = '\0'; cepTemp[2] = '\0';
        }
        
    }
    else if(strcmp(msgQIN.header, "CEPANS") == 0){
        
        msgOUT.reguti[0].port[0] = msgQIN.state;
        msgOUT.reguti[0].port[1] = '\0';
        strcpy(msgOUT.header, "CEP DONE");
        sendMessage(msgOUT);
    }
    
    
}


