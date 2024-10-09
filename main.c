#include <io.h>	
#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

/*Compila��o: gcc main.c funcoes.c -o find.exe -Wall -pedantic -Wextra -Werror*/

int main(int argc, char *argv[])
{
	
	/*Impedir Warning na execu��o do c�digo.*/
	argc = argc;
	argv = argv;
	
	/*Execu��o de find.*/
	find(argv, argc);
	
	return 0;
}