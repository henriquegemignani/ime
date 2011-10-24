Aluno: Henrique Gemignani Passos Lima
Numero Usp: ???????

Relatorio sobre Ep2

Estruturas usadas:
- BST com void*
- STACK com void*
- LL com void*
- ITEM (2 ints)
- WORD (char* + LL)
- FILEMANAGER (FM)
- BOOKDATABASE (BD)

Comentarios:

1. Void*
Utilizando void*, eh possivel que uma unica estrutura aceite mais de um tipo.
Por exemplo, eu utilizei 2 BST: uma para o indice invertido, e uma para armazenar
os FILEMANAGER.

2. BOOKDATABASE
Esse modulo/estrutura eh quem gerencia o indice invertido e os FILEMANAGERs.
Todas as buscas, insercoes e remocoes no indice sao realizados nesse modulo, assim como
criacao, manipulacao e remocao de novos FILEMANAGER.
Responsavel tambem para imprimir uma lista de ocorrencias.

3. FILEMANAGER
Responsavel pela leitura de livros (arquivos). Armazena informacoes sobre os livros
que permitem/facilitam a impressao de determinadas linhas.
Possui um indice (unico) para uso interno, chamado de bookRef. Com isso, eh possivel
fazer referncia a um arquivo usando apenas um inteiro e nao um vetor de caracteres.

4. ITEM
Na pratica, o seguinte par ordenado de inteiros: (bookRef, linha)

5. WORD
Possui uma string (a palavra em si) e uma lista ligada de ITEM, que seriam as
ocorrencias da palavra. Devido `a forma no qual se insere mais elementos na LL,
ela eh sempre ordenada de maneira decrescente.

6. Funcionamento
Ao inicializar, manda o BOOKDATABASE (BD) abrir todos os livros passados por parametro.
Feito isso, exibe o prompt ao usuario e aguarda uma instrução.
Interpreta a instrucao e realiza o que for necessario:
- Se for uma busca, manda o BD realizar a busca e a empilha.
- Se for uma operacao do RPN, envia o pedido ao modulo do RPN.
- Se for abertura/fechamento de algum arquivo, envia o pedido adequado ao RPN.
- Se for algum outro comando mais simples, realiza no ato (desempilhar/contar/sair)

Nota: ao mandar o BD abrir algum arquivo, ele mesmo se responsabiliza de atualizar o
indice invertido (mais precisamente, o FILEMANAGER).
