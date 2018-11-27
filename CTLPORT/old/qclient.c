#include "structs.h"

char cliname[10];
struct mq_attr ma;
uti_t utilizador;
char message[12];

int main()
{
    int mqids, mqidc, i;
    int clipid;
    doorcomm_t cache;

    ma.mq_flags = 0;
    ma.mq_maxmsg = 2;
    ma.mq_msgsize = sizeof(cache);

    clipid = getpid();
    snprintf(cliname, sizeof(cliname), "/CL-%05d", clipid);


    if ((mqidc=mq_open(cliname, O_RDWR|O_CREAT, 0666, &ma)) < 0) {
        perror("Cliente: Erro a criar queue cliente");
        exit(-1);
    }


    if ((mqids=mq_open(SERVQ, O_RDWR)) < 0) {
        perror("Cliente: Erro a associar a queue servidor");
        exit(-1);
    }


    printf("Controlador vai receber\n");

    if (mq_receive(mqidc, (char *)&cache, sizeof(cache), NULL) < 0) { // recebe os ids de todos os utilizadores
        perror("Controlador: erro a receber mensagem");
    }


    else {
        if (validacao(cache, utilizador)==1){        // Faz a validacao
            strcpy(message,"Validado");
        }
        else{
            strcpy(message,"nao validado");
        }
    }
    printf("Controlador vai enviar\n");
    if (mq_send(mqids, (char *)&message, sizeof(message), 0) < 0) { //Envia a mensagem para o servidor
        perror("Controlador: erro a enviar mensagem");
    }
    if (mq_unlink(cliname) < 0) {
    perror("Controlador: Erro a eliminar queue controlador");
    }

  return 0;
}
