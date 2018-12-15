#include "management.h"
//char doorMode = NORMAL;

int processMessage(doorcomm_t msgQIN)
{
    /*     
 * Function:  processMessage 
 * --------------------
 *  Processes the incoming queue message.
 *  This function works independently from the main thread. 
 * 
 *  Returns:
 *      1: If Successful
 *      0: If not Successful
 */
    doorcomm_t msgQOUT;
    if (strcmp(msgQIN.header, "QUERY") == 0)
    {
        //update cache
        updateCache(msgQIN);
        //verifica na cache
        checkCache(askDoor.id[0]);

        return 1;
    }
    else if (strcmp(msgQIN.header, "CEP") == 0)
    {
        msgQOUT.porta = clientDoor;
        msgQOUT.state = doorMode;
        strcpy(msgQOUT.header, "CEPANS");
        //clientQinit();
        sendQMessage(msgQOUT);
        return 1;
    }
    else if (strcmp(msgQIN.header, "CEP0") == 0)
    {
        msgQOUT.porta = clientDoor;
        msgQOUT.state = doorMode;
        strcpy(msgQOUT.cid, cliname);
        strcpy(msgQOUT.header, "CEPANS0");
        //clientQinit();
        sendQMessage(msgQOUT);
        return 1;
    }
    else if (strcmp(msgQIN.header, "MEP") == 0)
    {
        doorMode = msgQIN.state;
        splashscreen(doorMode);
    }
    else if (strcmp(msgQIN.header, "RIP") == 0)
    {
        clearCache();
        splashscreen('C');
    }
}

void clearCache()
{
    /*
 * Function:  clearCache 
 * --------------------
 *  Clears users cache.
 * 
 *  Returns:
 *      (void)
 */
    int i;
    for (i = 0; i < UMAX - 1; i++)
    {
        memset(usersCache[i], '\0', sizeof(char) * (NDIG + 1));
    }
}

void updateCache(doorcomm_t answer)
{
    /*
 * Function:  updateCache 
 * --------------------
 *  Updates users cache by overwriting ALL users, this ensures that the chache is up to date if the server goes offline.
 *  We are aware that the max number of ussers in cache, CMAX, is 3, but we still think this is a better approach. *Nao e por isso que o gato vai as filhoses*
 * 
 *  Returns:
 *      (void)
 */
    int i;
    for (i = 0; i < UMAX; i++)
    {
        if (strcmp(answer.id[i], "\000") == 0)
            memset(&usersCache[i], '\0', NDIG + 1);
        else
            strcpy(usersCache[i], answer.id[i]);
    }
}

int sendRegister(char id[NDIG + 1], char ac)
{
    /*
 * Function:  sendRegister 
 * --------------------
 *  Sends time register to server if there is a successfull entry attempt or if there are 3 failed attempts in a row with the same id.
 * 
 *  Returns:
 *      1: If Successful
 *      0: If not Successful
 */
    doorcomm_t regMsg;
    time_t currentTime;
    strcpy(regMsg.header, "REGUSR");
    strcpy(regMsg.reg.id, id);
    regMsg.reg.p = clientDoor;
    clock_gettime(CLOCK_REALTIME, &regMsg.reg.t);
    regMsg.reg.ac = ac;
    return sendQMessage(regMsg);
}

int checkCache(char id[NDIG + 1])
{
    id[NDIG] = '\0';
    int i;
    if (strcmp(id, IDX) == 0)
    {
        printf("\n%sSuperUser detected, Access Granted!%s\n\n", KGRN, KWHT);
        printf("Introduza o identificador: ");
        sem_post(&semMain);
        return 1;
    }

    for (i = 0; i < UMAX; i++)
    {
        if (strcmp(usersCache[i], id) == 0)
        {
            printf("\n%sAccess Granted!%s\n\n", KGRN, KWHT);
            //criar e enviar registo
            sendRegister(id, '1');
            printf("Introduza o identificador: ");
            sem_post(&semMain);
            return 1;
        }
    }
    printf("\n%sAccess Denied!%s\n\n", KRED, KWHT);

    if (strcmp(fails.id, id) == 0)
    {
        if (++fails.number == 3)
        {
            printf("%s3 failed attepts on id %s.%s\n", KRED, id, KWHT);
            printf("%sContacting server!%s\n\n", KRED, KWHT);

            sendRegister(id, '0');
        }
    }
    else
    {
        strcpy(fails.id, id);
        fails.number = 1;
    }
    printf("Introduza o identificador: ");
    sem_post(&semMain);
    return 0;
}
