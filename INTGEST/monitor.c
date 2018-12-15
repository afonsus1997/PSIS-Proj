/***************************************************************************
| File: monitor.c
|
| Autor: Carlos Almeida (IST), from work by Jose Rufino (IST/INESC), 
|        from an original by Leendert Van Doorn
| Data:  Nov 2002
***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "monitor.h"
/*-------------------------------------------------------------------------+
| Headers of command functions
+--------------------------------------------------------------------------*/ 
extern void cmd_sair (int, char** );
extern void cmd_test (int, char** );
extern int nuti (int, char**);
extern int luti (int, char**);
extern int euti (int, char**);
extern int mpu (int, char**);
extern int lapu (int, char**);
extern int tserv (int, char**);
extern int cep (int , char**);
extern int mep (int, char**);
extern int rip (int, char**);
       void cmd_sos  (int, char** );

/*-------------------------------------------------------------------------+
| Variable and constants definition
+--------------------------------------------------------------------------*/ 
const char TitleMsg[] = "\n \n";
const char InvalMsg[] = "\nInvalid command!\nType sos for help\n";

struct 	command_d {
  int  (*cmd_fnct)(int, char**);
  char*	cmd_name;
  char*	cmd_help;
} const commands[] = {
  {cmd_sos,  "sos","                  help"},
  {cmd_sair, "sair","                 sair"},
  {nuti,     "nuti","                 Novo utilizador: id; nome; portas com acesso (ABC)"},
  {luti,     "luti","                 Listar utilizador u (0-todos) (id, nome, portas)"},
  {euti,     "euti","                 Eliminar utilizador u (0-todos)"},
  {mpu,      "mpu","                  Modificar portas utilizador u (0-todos), portas ABC"},
  {lapu,     "lapu","                 Listar acessos porta p (0-todas), utilizador u (0-todos), entre t1 (dd/mm/aaaa hh:mm:ss) e t2"},
  {tserv,    "tserv","                Consultar estado porta p (0-todas)." },
  {cep,    "cep","                  Consultar estado porta p (0-todas)" },
  {mep,    "mep","                Modificar estado porta p (0-todas) para e (AFN -abrir,fechar,normal)." },
  {rip,    "rip","                Reinicializar (apagar cache) identificadores porta p (0-todas)." }


};

#define NCOMMANDS  (sizeof(commands)/sizeof(struct command_d))
#define ARGVECSIZE 5
#define MAX_LINE   50
int errcode;
/*-------------------------------------------------------------------------+
| Function: cmd_sos - provides a rudimentary help
+--------------------------------------------------------------------------*/ 
void cmd_sos (int argc, char **argv)
{
  int i;

  printf("%s\n", TitleMsg);
  for (i=0; i<NCOMMANDS; i++)
    printf("%s %s\n", commands[i].cmd_name, commands[i].cmd_help);
}

/*-------------------------------------------------------------------------+
| Function: my_getline        (called from monitor) 
+--------------------------------------------------------------------------*/ 
int my_getline (char** argv, int argvsize)
{
  static char line[MAX_LINE];
  char *p;
  int argc;

  fgets(line, MAX_LINE, stdin);

  /* Break command line into an o.s. like argument vector,
     i.e. compliant with the (int argc, char **argv) specification --------*/

  for (argc=0,p=line; (*line != '\0') && (argc < argvsize); p=NULL,argc++) {
    p = strtok(p, " \t\n");
    argv[argc] = p;
    if (p == NULL) return argc;
  }
  argv[argc] = p;
  return argc;
}

/*-------------------------------------------------------------------------+
| Function: monitor        (called from main) 
+--------------------------------------------------------------------------*/ 
int monitor ()
{
  message_t outmesg;
  static char *argv[ARGVECSIZE+1], *p;
  int argc, i;

  //printf("%s \n", TitleMsg);
  for (;;) {
    printf("\n------------------------------\n");
    printf("\nCmd> ");
    /* Reading and parsing command line  ----------------------------------*/
    if ((argc = my_getline(argv, ARGVECSIZE)) > 0) {
      for (p=argv[0]; *p != '\0'; *p=tolower(*p), p++);
      for (i = 0; i < NCOMMANDS; i++) 
	      if (strcmp(argv[0], commands[i].cmd_name) == 0) 
	      break;
      /* Executing commands -----------------------------------------------*/
      if (i < NCOMMANDS)
	      errcode = commands[i].cmd_fnct (argc, argv);
        if(errcode == -1){
          printf("\nMissing Parameters!\n");
          errcode = 0;
          return -1;
        }
        else if(errcode == -2){
          errcode = 0;
          return -2;
        }
        
        }
      else  
	    printf("%s", InvalMsg);
      return 0;
    } /* if my_getline */
    
} /* forever */

  //return 0;

