#include "intgest.h"
extern int monitor(void);
extern int closeServer();




void exitHandler(int sn){
  
  char ch;
  printf("\n\nDeseja terminar o cliente? (s/n)\n");
  ch=getchar();
  if(ch == 's'){
    closeServer();
    exit(0);
    
  }
  
}


int main()
{
  

  splashscreen();

  signal(SIGINT, exitHandler);

  if(clientInit() < 0){
    //ERROR
  }
  
  while(1){
    if(monitor() == -2){
      printf("Unhandled Exeption\n");
      break;
    }
  }
  

  return 0;
}


void splashscreen(){

system("clear");
printf("\n\n");
printf("-------------------------------------------------------\n");
printf("|         _____   _______________________________     |  \n");
printf("|        /  _/ | / /_  __/ ____/ ____/ ___/_  __/     | \n");
printf("|        / //  |/ / / / / / __/ __/  \\__ \\ / /        |  \n");
printf("|      _/ // /|  / / / / /_/ / /___ ___/ // /         |  \n");
printf("|     /___/_/ |_/ /_/  \\____/_____//____//_/          |  \n");
printf("|     Programacao de Sistemas Computacionais          |  \n");
printf("|  Afonso Muralha | Miguel Dias | Tomas Bettencourt   |  \n");
printf("|                                                     |  \n");
printf("-------------------------------------------------------");

printf("\n\n");
}