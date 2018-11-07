/***************************************************************************
| File: comando.c  -  Concretizacao de comandos (exemplo)
|
| Autor: Carlos Almeida (IST)
| Data:  Nov 2002
***************************************************************************/


/*
	CMD LIST:
	NUTI - NEW USER
		u - ID
		nome - NOME
		portas[] - PORTAS COM ACESSO 
	

	LUIT - LISTAR UTILIZADOR
		u - UTILIZADOR (0 - todos) (id, nome, portas) 
	EUTI - ELIMINAR UTILIZADORES 
		u - UTILIZAODR (0 - todos)
	MPU - MODIFICAR PORTAS UTILIZADOR
		u - UTILIZADOR (0 - todos)
		portas - PORTAS ABC
	LAPU - LISTAR ACESSOS 
		p - PORTA p (0 - todas)
		u - UTILIZADOR (0 - todos)
		[t1, t2] - TEMPO entre t1 e t2
	TSERV 
	CEP 
		p
	MEP 
		p
		e
	RIP
		p
	
	*/



#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------------------------------------------+
| Function: cmd_sair - termina a aplicacao
+--------------------------------------------------------------------------*/ 
void nuti (int argc, char **argv)
{
  
    printf ("LEL\n");
}

/*-------------------------------------------------------------------------+
| Function: cmd_test - apenas como exemplo
+--------------------------------------------------------------------------*/ 
void luti (int argc, char** argv)
{
  int i;

  /* exemplo -- escreve argumentos */
  for (i=0; i<argc; i++)
    printf ("\nargv[%d] = %s", i, argv[i]);
}

void euti (int argc, char** argv)
{
  int i;

  /* exemplo -- escreve argumentos */
  for (i=0; i<argc; i++)
    printf ("\nargv[%d] = %s", i, argv[i]);
}

void mpu (int argc, char** argv)
{
  int i;

  /* exemplo -- escreve argumentos */
  for (i=0; i<argc; i++)
    printf ("\nargv[%d] = %s", i, argv[i]);
}

void lapu (int argc, char** argv)
{
  int i;

  /* exemplo -- escreve argumentos */
  for (i=0; i<argc; i++)
    printf ("\nargv[%d] = %s", i, argv[i]);
}

void tserv (int argc, char** argv)
{
  int i;

  /* exemplo -- escreve argumentos */
  for (i=0; i<argc; i++)
    printf ("\nargv[%d] = %s", i, argv[i]);
}

void cep (int argc, char** argv)
{
  int i;

  /* exemplo -- escreve argumentos */
  for (i=0; i<argc; i++)
    printf ("\nargv[%d] = %s", i, argv[i]);
}

void mep (int argc, char** argv)
{
  int i;

  /* exemplo -- escreve argumentos */
  for (i=0; i<argc; i++)
    printf ("\nargv[%d] = %s", i, argv[i]);
}

void rip (int argc, char** argv)
{
  int i;

  /* exemplo -- escreve argumentos */
  for (i=0; i<argc; i++)
    printf ("\nargv[%d] = %s", i, argv[i]);
}

void cmd_sair (int argc, char** argv)
{
  int i;

  /* exemplo -- escreve argumentos */
  for (i=0; i<argc; i++)
    printf ("\nargv[%d] = %s", i, argv[i]);
}

void cmd_test (int argc, char** argv)
{
  int i;

  /* exemplo -- escreve argumentos */
  for (i=0; i<argc; i++)
    printf ("\nargv[%d] = %s", i, argv[i]);
}