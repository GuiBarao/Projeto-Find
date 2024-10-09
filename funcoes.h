#ifndef _FUNCOES
#define _FUNCOES

/*Constantes de validacao da entrada de find.*/
#define BUSCA_TEXTO 1
#define BUSCA_ARQ 2
#define INVALIDO 0

/**************************************************************************************
Descri��o: Separa a matriz de Strings de par�metros de find em 3 outras Strings.

Entradas -> String da entrada, ponteiro para a String do nome do diret�rio, 
ponteiro para a String do nome de arquivo e ponteiro para a String do texto
a ser buscado.

Sa�da -> Inteiro que representa a validacao da entrada.
***************************************************************************************/
int separa_entradas(char **, int, char **, char **,  char **);


/**************************************************************************************
Descri��o: Cria um diret�rio completo.

Entrada -> Ponteiro para a String do novo diretorio, String do diretorio, String do
arquivo ou pasta.

Sa�da -> Nenhuma.
***************************************************************************************/
void combina_diretorio(char **, char *, char *);


/**************************************************************************************
Descri��o: Verifica se uma sequ�ncia de caracteres est� presente em uma String.

Entrada -> String a ser verificada e String da sequ�ncia de caracteres.

Sa�da -> Inteiro que representa se a sequ�ncia est� presente na linha (0 ou 1).
***************************************************************************************/
int verifica_linha(char *, char *);


/**************************************************************************************
Descri��o: Busca um texto dentro de um arquivo.

Entrada -> String do nome do arquivo e String do texto a ser buscado.

Sa�da -> Nenhuma.
***************************************************************************************/
void buscar_texto(char *, char *);


/**************************************************************************************
Descri��o: Realiza a busca de arquivo ou texto, dependendo dos par�metros de find.

Entrada -> Strings de diret�rio, nome do arquivo e texto a ser buscado. Inteiro que
representa o modo da busca(BUSCA_ARQ ou BUSCA_TEXTO), 2 ponteiros para inteiros
que armazena a quantidade de arquivos e pastas analisados e 1 ponteiro para inteiro
que representa a informa��o se algum arquivo foi encontrado.

Sa�da -> Nenhuma.
***************************************************************************************/
void busca(char *, char *, char *, int , int *, int *, int *);


/**************************************************************************************
Descri��o: Recebe um nome de diretorio, arquivo e texto em uma �nica String. Busca
dentro do diretorio informado o arquivo. Se houver um texto a ser buscado tamb�m realiza
a busca dentro do arquivo.

Entrada -> Argumentos de find no terminal(argv) e contagem de argumentos (argc).

Sa�da -> Nenhuma.
***************************************************************************************/
void find(char **, int);


#endif