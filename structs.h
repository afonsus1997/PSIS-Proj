

typedef struct message{
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
	
	char *header; 
	char *utilizador;
	char *nome;
	char **portas;
	char *tempo;
	
}MESSAGE;