/*needed header files*/
#include "structs.h"

/*extern funcions*/
extern int sendQMessage(doorcomm_t inMsg);
extern int clientQinit();
extern void splashscreen(char mode);

/*global variables*/
struct failCounter fails;

/*function prototypes*/
int processMessage(doorcomm_t msgQIN);
void clearCache();
void updateCache(doorcomm_t answer);
int sendRegister(char id[NDIG + 1], char ac);
int checkCache(char id[NDIG + 1]);

