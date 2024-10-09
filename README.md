# Projeto Find #
**Este projeto foi desenvolvido como parte de um trabalho para o curso de Sistemas de Informação.**
## Descrição ##

Implementa a função "find" que recebe, via linha de comando, até 3 parâmetros: 
- Caminho de um diretório (D)
- Nome de um arquivo (A)
- Sequencia de caracteres (C)

Obrigatóriamente 'D' e 'A' devem ser informados. 

Se o parâmetro 'C' **não** for informado, o sistema irá buscar dentro do diretório 'D' o arquivo 'A'.

Se o parâmetro 'C' for informado, então o sistema deve buscar dentro do diretório 'D' o arquivo 'A' e em seguida buscar a sequencia de caracteres 'C' no arquivo 'A'.

## Requisitos ##
- Compilador GCC.

Para rodar entre no diretório do projeto e digite o seguinte comando para compilação:

**gcc main.c funcoes.c -o find.exe -Wall -pedantic -Wextra -Werror**

Após a compilação a função find pode ser executada. 

## Exemplos ##

### **find C:/Users/joao/anotacoes escola.txt ciências** ###
->> O sistema irá entrar em "C:/Users/joao/anotacoes", buscar por "escola.txt", entrar no arquivo e buscar por "ciências".

### **find C:/Users/joao/anotacoes tarefas.txt** ###
->> O sistema irá entrar em "C:/Users/joao/anotacoes" e buscar pelo arquivo "tarefas.txt".
