#include "structs.h"
pthread_t thread;
int threadID;

doorcomm_t msgIN;
doorcomm_t askDoor;
doorcomm_t doorAnswer;

extern doorcomm_t receiveQMessage();
extern sendQMessage(doorcomm_t inMsg);
extern int clientQinit();
extern int clientQClose();
extern int processMessage(doorcomm_t answer);
extern int checkCache(char id[NDIG + 1]);

void *thread_func(void *pi) //Door answer thread
{

    while (1)
    {

        processMessage(receiveQMessage());
        //sem_post(&semMain);
    }
}

int main(int argc, char *argv[])
{

    clientDoor = argv[1][0];
    doorMode = NORMAL;
    splashscreen('0');
    //if (sem_init(&semThread, 0, 0) != 0) {printf("Erro a inicializar semaforo da thread\n"); return -1;}
    if (sem_init(&semMain, 0, 0) != 0)
    {
        printf("Erro a inicializar semaforo principal\n");
        return -1;
    }

    ma.mq_flags = 0;
    ma.mq_maxmsg = 2;
    ma.mq_msgsize = sizeof(doorcomm_t);

    if (clientQinit() < 0)
    {
        printf("Erro ao inicializar Queueeue\n");
    }

    if (pthread_create(&thread, NULL, thread_func, (void *)&threadID) != 0)
    {
        printf("Error Creating Door Thread\n");
    }

    printf("Introduza o identificador: ");

    while (1)
    {
        // Pede o identificador ao utilizador

        fgets(readBuf, sizeof(readBuf), stdin);
        strcpy(askDoor.id[0], readBuf);

        askDoor.porta = clientDoor;
        strcpy(askDoor.cid, cliname);
        strcpy(askDoor.header, "QUERY");
        if (doorMode == 'F')
        {
            if (strcmp(readBuf, IDXn) == 0)
                printf("\n%sSuperUser detected, Access Granted!%s\n\n", KGRN, KWHT);
            else
                printf("\n%sAccess Denied!%s\n\n", KRED, KWHT);
            printf("Introduza o identificador especial: ");
            sem_post(&semMain);
        }
        else if (doorMode == 'N')
        {
            if (sendQMessage(askDoor) == 0)
            {
                /*Sem ligacao ao server, verificar na cache*/
                printf("\nCan't connect to server, validating locally...\n");
                checkCache(askDoor.id[0]);
            }
        }
        else if (doorMode == 'A')
        {
            printf("\n%sAccess Granted!%s\n\n", KGRN, KWHT);
            sendRegister(askDoor.id[0], '1');
            printf("Introduza o identificador: ");

            sem_post(&semMain);
        }
        sem_wait(&semMain);
    }

    if (clientQClose() < 0)
    {
        printf("Erro ao fechar Queueeue\n");
    }

    return 0;
}

void splashscreen(char mode)
{
    char buf[25];
    system("clear");
    printf("\n\n%s", KGRN);
    printf("-------------------------------------------------------\n");
    printf("|      %s ______________    ____  ____  ____  ____ %s     |\n", KWHT, KGRN);
    printf("|      %s/ ____/_  __/ /   / __ \\/ __ \\/ __ \\/ __ \\%s     |\n", KWHT, KGRN);
    printf("|     %s/ /     / / / /   / / / / / / / / / / /_/ /%s     |\n", KWHT, KGRN);
    printf("|    %s/ /___  / / / /___/ /_/ / /_/ / /_/ / _, _/ %s     |\n", KWHT, KGRN);
    printf("|    %s\\____/ /_/ /_____/_____/\\____/\\____/_/ |_| %s      |\n", KWHT, KGRN);
    printf("|      %sProgramacao de Sistemas Computacionais%s         |  \n", KWHT, KGRN);
    printf("|  %sAfonso Muralha | Miguel Dias | Tomas Bettencourt%s   |  \n", KWHT, KGRN);
    printf("|                                                     |  \n");
    printf("-------------------------------------------------------");

    printf("%s\n", KWHT);
    printf("\nPorta %c\n", clientDoor);

    if (mode == 'C')
    {
        printf("%s\nCache Reset!%s\n\n", KRED, KWHT);
        mode = doorMode;
    }

    printf("Door Mode: ");
    if (mode == 'N')
    {
        printf("Normal\n\n");
        //printf("Introduza o identificador: ");
        strcpy(buf, "Introduza o identificador: ");
        write(1, buf, strlen(buf));
    }
    else if (mode == 'A')
    {
        printf("%sOpen%s\n\n", KGRN, KWHT);
        //printf("Introduza o identificador?: ");
        strcpy(buf, "Introduza o identificador?: ");
        write(1, buf, strlen(buf));
    }
    else if ((mode == 'F'))
    {
        printf("%sClosed%s\n\n", KRED, KWHT);
        //printf("Introduza o identificador especial: ");
        strcpy(buf, "Introduza o identificador especial: ");
        write(1, buf, strlen(buf));
    }
    else
    {
        printf("Normal\n\n");
    }
}