/*needed header files*/
#include "structs.h"

/*extern funcions*/
extern doorcomm_t receiveQMessage();
extern int sendQMessage(doorcomm_t inMsg);
extern int clientQinit();
extern int clientQClose();
extern int processMessage(doorcomm_t answer);
extern int checkCache(char id[NDIG + 1]);

/*global variables*/
pthread_t thread;
int threadID;
doorcomm_t msgIN;
doorcomm_t askDoor;
doorcomm_t doorAnswer;

/*function prototypes*/
void *thread_func(void *pi);
void splashscreen(char mode);