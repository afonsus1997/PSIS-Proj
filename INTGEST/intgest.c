#include "intgest.h"
extern void monitor(void);

MESSAGE msgOut;

int main()
{
  
  if(serverInit() < 0){
    //ERROR
  }
  else{
    monitor();
    sendInfo(&msgOut);
  }
  
  if(closeServer()<0){
    //ERRO
  }
  
  return 0;
}
