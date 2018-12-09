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
printf("%s\n\n", KBLU);
printf("-------------------------------------------------------\n");
printf("|        %s _____   _______________________________ %s    |  \n", KWHT, KBLU);
printf("|       %s /  _/ | / /_  __/ ____/ ____/ ___/_  __/ %s    | \n",KWHT, KBLU);
printf("|       %s / //  |/ / / / / / __/ __/  \\__ \\ / / %s       |  \n",KWHT, KBLU);
printf("|     %s _/ // /|  / / / / /_/ / /___ ___/ // /  %s       |  \n",KWHT, KBLU);
printf("|    %s /___/_/ |_/ /_/  \\____/_____//____//_/ %s         |  \n",KWHT, KBLU);
printf("|   %s  Programacao de Sistemas Computacionais %s         |  \n",KWHT, KBLU);
printf("| %s Afonso Muralha | Miguel Dias | Tomas Bettencourt %s  |  \n",KWHT, KBLU);
printf("|                                                     |  \n");
printf("-------------------------------------------------------");

printf("%s\n\n", KWHT);
}