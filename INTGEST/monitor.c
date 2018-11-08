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
extern MESSAGE nuti (int, char**);
extern MESSAGE luti (int, char**);
extern MESSAGE euti (int, char**);
extern MESSAGE mpu (int, char**);
extern MESSAGE lapu (int, char**);
extern MESSAGE tserv (int, char**);
extern MESSAGE cep (int, char**);
extern MESSAGE mep (int, char**);
extern MESSAGE rip (int, char**);
       void cmd_sos  (int, char** );

/*-------------------------------------------------------------------------+
| Variable and constants definition
+--------------------------------------------------------------------------*/ 
const char TitleMsg[] = "\n \n";
const char InvalMsg[] = "\nInvalid command!\nType sos for help\n";

struct 	command_d {
  MESSAGE  (*cmd_fnct)(int, char**);
  char*	cmd_name;
  char*	cmd_help;
} const commands[] = {
  {cmd_sos,  "sos","                  help"},
  {cmd_sair, "sair","                 sair"},
  {cmd_test, "teste","<arg1> <arg2>   comando de teste"},
  {nuti,     "nuti","                 novo utilizador: id; nome; portas com acesso (ABC"},
  {luti,     "luti","                 listar utilizador u (0-todos) (id, nome, portas)"},
  {euti,     "euti","                 eliminar utilizador u (0-todos)"},
  {mpu,      "mpu","                  modificar portas utilizador u (0-todos), portas ABC"},
  {lapu,     "lapu","                 listar acessos porta p (0-todas), utilizador u (0-todos), entre t1 (dd/mm/aaaa hh:mm:ss) e t2"},

};

#define NCOMMANDS  (sizeof(commands)/sizeof(struct command_d))
#define ARGVECSIZE 3
#define MAX_LINE   50

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
MESSAGE monitor ()
{
  MESSAGE outmesg;
  static char *argv[ARGVECSIZE+1], *p;
  int argc, i;

  //printf("%s \n", TitleMsg);
  for (;;) {
    printf("\nCmd> ");
    /* Reading and parsing command line  ----------------------------------*/
    if ((argc = my_getline(argv, ARGVECSIZE)) > 0) {
      for (p=argv[0]; *p != '\0'; *p=tolower(*p), p++);
      for (i = 0; i < NCOMMANDS; i++) 
	      if (strcmp(argv[0], commands[i].cmd_name) == 0) 
	      break;
      /* Executing commands -----------------------------------------------*/
      if (i < NCOMMANDS)
	      return commands[i].cmd_fnct (argc, argv);
      else  
	printf("%s", InvalMsg);
    } /* if my_getline */
  } /* forever */

  return outmesg;

}