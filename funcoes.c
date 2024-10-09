#include <io.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"                                                                                       

int separa_entradas(char **entrada, int lenEntrada, char **nomeDir, char **nomeArq,  char **texto)
{
	/*Tamanho das aloca��es*/
	int tamanhoString;
	
	
	/*Valida��o*/
	if(lenEntrada > 4 || lenEntrada < 3)
	{
		printf("Formato de par�metros inv�lido");
		return INVALIDO;
	}
	
	/*Aloca��o do nome do diret�rio.*/
	tamanhoString = strlen(entrada[1]) + 1;
	*nomeDir = (char*) malloc (tamanhoString * sizeof(char));
	if(*nomeDir == NULL)
	{
		printf("Erro em aloca��o.");
		exit(1);
	}
	
	/*Aloca��o do nome do arquivo*/
	tamanhoString = strlen(entrada[2]) + 1;
	*nomeArq = (char*) malloc (tamanhoString * sizeof(char));
	if(*nomeArq == NULL)
	{
		printf("Erro em aloca��o.");
		exit(1);
	}
	
	strcpy(*nomeDir, entrada[1]);
	strcpy(*nomeArq, entrada[2]);
	
	/*Se tiver um texto*/
	if(lenEntrada == 4)
	{
		/*Aloca��o do texto a ser buscado.*/
		tamanhoString = strlen(entrada[3]) + 1;
		*texto = (char*) malloc (tamanhoString * sizeof(char));
		if(*texto == NULL)
		{
			printf("Erro em aloca��o.");
			exit(1);
		}
		strcpy(*texto, entrada[3]);
		
		return BUSCA_TEXTO;
	}
	else
	{
		return BUSCA_ARQ;
	}
}

void combina_diretorio(char **subpasta, char *diretorio, char *nomePasta)
{
	/*Combina o nome do diretorio com o nome do arquivo para formar o caminho completo do arquivo.*/
	
	/*Aloca o espa�o para o nome do diretorio combinado.*/
	*subpasta = (char*) malloc ((strlen(nomePasta) + strlen(diretorio) + 2) * sizeof(char));
	if(*subpasta == NULL)
	{
		exit(1);
	}
	
	/*Copia o diretorio na string subpasta.*/
	strcpy((*subpasta), diretorio);
	
	/*Concatena com uma '/'*/
	strcat((*subpasta), "/");
	
	/*Concatena com o nome da pasta*/
	strcat((*subpasta), nomePasta);
	
}	

int verifica_linha(char *linha, char *texto)
{
	/*Indice da linha.*/
	int iLinha;
	
	/*Indice do texto sendo buscado.*/
	int iTexto;
	
	/*Parada da busca.*/
	int parada;
	
	/*Ultimo indice da String.*/
	parada = strlen(texto) - 1;
	
	iLinha = 0;
	iTexto = 0;
	
	/*Percorre a linha.*/
	while(linha[iLinha] != '\0')
	{
		/*Verifica se os caracteres de linha e texto s�o iguais.*/
		if(linha[iLinha] == texto[iTexto])
		{
			/*Avanca em texto.*/
			iTexto++;
			
			/*Se chegou no fim do texto.*/
			if(iTexto > parada)
			{
				return 1;
			}
		}
		else
		{
			/*Se os caracteres forem diferentes, volta a buscar o texto do inicio.*/
			iTexto = 0;
		}
		
		/*Avan�a na linha.*/
		iLinha++;
		
	}
	
	return 0;
	
}

void buscar_texto(char *nomeArq, char *texto)
{
	/*Ponteiro para arquivo.*/
	FILE *arq;
	
	/*Armazena os caracteres do arquivo.*/
	char caractere;
	
	/*Ponteiro para a aloca��o das linhas do arquivo.*/
	char *linha;
	
	/*Indice das linhas.*/
	int iLinha;
	
	/*Contagem das linhas.*/
	int contLinha;
	
	/*Parada do loop de leitura*/
	int fim_leitura;
	
	/*Abertura do arquivo no modo de leitura.*/
	arq = fopen(nomeArq, "r");
	
	/*Situa��o de erro na abertura do arquivo.*/
	if(arq == NULL)
	{
		exit(1);
	}
	
	/*Aloca��o inicial da linha.*/
	linha = (char *) malloc (1 * sizeof(char));
	if(linha == NULL)
	{
		exit(1);
	}
	
	iLinha = 0;
	contLinha = 0;
	fim_leitura = 0;
	
	/*Percorre o arquivo pegando seus caracteres.*/
	while(!fim_leitura)
	{
		(caractere = getc(arq));
		/*Se o caractere nao � '\n' (Fim da linha).*/
		if(caractere != '\n' && caractere != EOF)
		{
			/*Linha armazena o caractere.*/
			linha[iLinha] = caractere;
			
			/*Avan�a em linha.*/
			iLinha++;
			
			/*Aloca o espaco para o proximo caractere.*/
			linha = (char *) realloc (linha, (iLinha+1) * sizeof(char));
			if(linha == NULL)
			{
				exit(1);
			}
		}
		else
		{
			/*Ao encontrar o '\n'.*/
			
			/*Contabiliza a linha.*/
			contLinha++;
			
			/*Adiciona o '\0' no fim da String.*/
			linha[iLinha] = '\0';
			
			/*Verifica se a linha cont�m o texto buscado.*/
			if(verifica_linha(linha, texto))
			{
				printf("    Linha %d: %s\n", contLinha, linha);
			}
			
			/*Esvazia a String linha.*/
			linha = (char *) malloc (1 * sizeof(char));
			if(linha == NULL)
			{
				exit(1);
			}
			iLinha = 0;
			
			if(caractere == EOF)
			{
				fim_leitura = 1;
			}
			
		}
	}
	
	free(linha);
	
	/*Fechamento do arquivo.*/
	fclose(arq);
	
}

void busca(char *diretorio, char *nomeArq, char *texto, int modo, int *contPastas, int *contArquivos, int *arquivoEncontrado)
{

	/*Identificador do resultado retornado pela busca por um nome de arquivo.*/
	long int id; 
	
	/*Estrutura que armazenar� o resultado retornado pela fun��o _findfirst.*/ 
	struct _finddata_t dados_diretorio; 
	
	/*String que armazena o diretorio que ser� buscado.*/
	char diretorioAdaptado[FILENAME_MAX];
	
	/*String do nome das subpastas encontradas.*/
	char *subpasta;
	
	/*Nome do arquivo com seu diret�rio completo.*/
	char *nomeArq_aux;
	
	/*Adicinado a String de diretorio para buscar dentro da pasta.*/
	char *adicional = "/*.*";
	
	/*�ndice de repeti��es.*/
	int i;
	
	/*Percorre a String do diretorio e substitue \ por /. ('\' � um caractere especial em C)*/
	i = 0;
	while(diretorio[i] != '\0')
	{
		if(diretorio[i] == '\\')
		{
			diretorio[i] = '/';
		}
		i++;
	}
	
	/*Copia o nome do diretorio em diretorioAdaptado e concatena o adicional.*/
	strcpy(diretorioAdaptado, diretorio);
	strcat(diretorioAdaptado,adicional);
	
	/*Buscar por todos os nomes existentes no diret�rio e armazenar o resultado da busca na variavel dados_diretorio.*/  
	id = _findfirst (diretorioAdaptado, &dados_diretorio);
	
	/*findfirst retorna -1 no caso de diret�rio n�o encontrado.*/
	if (id == -1)
	{
		printf("\nDiret�rio n�o encontrado.");
		exit(1);
	}
	
	/*Percorre por todos os arquivos e subpastas do diretorio.*/
	do
	{	
		/*Se o arquivo encontrado n�o � '.' ou '..'.*/
		if((strcmp(dados_diretorio.name, ".") == 1) && (strcmp(dados_diretorio.name, "..") == 1))
		{
			/*Se o arquivo � uma subpasta.*/
			if((dados_diretorio.attrib & _A_SUBDIR))
			{
				/*Contabiliza subpasta.*/
				(*contPastas)++;
				
				/*Cria o diretorio completo dessa subpasta.*/
				combina_diretorio(&subpasta, diretorio, dados_diretorio.name);
				
				printf("\nAnalisando %s <DIR>\n", subpasta);
				
				/*Chamada recursiva de busca para a subpasta.*/
				busca(subpasta, nomeArq, texto, modo, contPastas, contArquivos, arquivoEncontrado);
			}
			else
			{
				/*Se n�o for uma subpasta.*/
				
				/*Contabiliza Arquivo.*/
				(*contArquivos)++;
				
				/*Se o arquivo encontrado � o que esta sendo buscado.*/
				if((strcmp(dados_diretorio.name, nomeArq) == 0))
				{
					printf("\nEncontrado: %s/%s\n", diretorio,dados_diretorio.name);
					*arquivoEncontrado = 1;
					
					/*Se existe um texto a ser buscado.*/
					if(modo == BUSCA_TEXTO)
					{
						/*Cria o diretorio completo para esse arquivo.*/
						combina_diretorio(&nomeArq_aux, diretorio, dados_diretorio.name);
						
						/*Busca o texto nele.*/
						buscar_texto(nomeArq_aux, texto);
					}
				}
				else
				{
					/*Se o arquivo encontrado n�o for o que est� sendo buscado.*/
					printf("\nAnalisando: %s/%s\n", diretorio,dados_diretorio.name);
				}
			}
		}
		
	/*Vai para o pr�ximo nome localizado no diret�rio.*/	
	}while(!_findnext(id, &dados_diretorio));
	
	/*Libera os recursos alocados vinculados ao identificador da busca realizada */
	_findclose(id);
}	

void find(char **entrada, int lenEntrada)
{
	/*Nome do diretorio.*/
	char *nomeDir;
	
	/*Nome do arquivo.*/
	char *nomeArq;
	
	/*Texto a ser buscado.*/
	char *texto;
	
	/*0 ou 1 para indicar se a entrada de find � v�lida.*/
	int validacao_entrada;
	
	/*Contagem de quantos arquivos e sub-pastas o sistema encontrou.*/
	int contPastas;
	int	contArquivos;
	
	/*Retorna da fun��o de busca.*/
	int arquivoEncontrado;
	
	/*Separa a entrada em: nome do diretorio, nome do arquivo e texto a ser buscado.*/
	validacao_entrada = separa_entradas(entrada, lenEntrada, &nomeDir, &nomeArq, &texto);
	
	/*Se a validacao_entrada for diferente de INVALIDO.*/
	if(validacao_entrada != INVALIDO)
	{
		contPastas = 0;
		contArquivos = 0;
		
		arquivoEncontrado = 0;
		busca(nomeDir, nomeArq, texto, validacao_entrada, &contPastas, &contArquivos, &arquivoEncontrado);
		
		if(!arquivoEncontrado)
		{
			printf("\nArquivo %s n�o foi encontrado no diret�rio.\n", nomeArq);
		}
	
		printf("\nForam analisadas %d pastas e %d arquivos.\n", contPastas, contArquivos);
	}
	
	free(nomeDir);
	free(nomeArq);
	free(texto);
}