/*******************************************************************/
/** MAC 122 - Principios de Desenvolvimento de Algoritmos         **/
/** IME-USP - Segundo Semestre de 2009                            **/
/**                                                               **/
/** Quarto Exercicio-Programa -- Cadastro Academico               **/
/** Arquivo: cadastro.c                                           **/
/**                                                               **/
/** Henrique Gemignani Passos Lima    nº USP: ???????             **/
/**                                                               **/
/** 14/11/2009                                                    **/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  aluno             Aluno;
typedef struct  disciplina        Disciplina;
typedef struct  aluno_disciplina  Aluno_Disciplina;
typedef struct  aluno_disciplina* pAluno_Disciplina;
struct aluno_disciplina {
	int ind_aluno;
	int ind_disc;
	pAluno_Disciplina prox_aluno;
	pAluno_Disciplina prox_disc;
};
struct aluno {
	int               nusp;
	char              nome[64];
	pAluno_Disciplina inicio;
};
Aluno *vet_a;
int numAluno;

struct disciplina {
	char              sigla[8];
	char              nome[64];
	pAluno_Disciplina inicio;
};
Disciplina *vet_d;
int numDisciplina;

void masterError( char* str ) {
	printf("%s\n",str);
	exit(1);
}

/* Passado um ponteiro de arquivo, e o numero de linhas do arquivo, cria o vetor
 vet_a e transcreve os valores necessiaros. */
void criaVetorAluno( FILE *fp, int numLinha ) {
	char str[9] = "";
	int i;
	numAluno = numLinha;
	vet_a = malloc( numAluno * sizeof( Aluno ) );
	if( !vet_a ) masterError( "Impossivel reservar memoria para o vetor de alunos." );
	for( i = 0; i < numAluno; i++ ) {
		fgets( str, 8, fp );
		vet_a[i].nusp = atoi( str );
		fgetc( fp ); /* Espaco em Branco. */
		fgets( vet_a[i].nome, 64, fp );
		if( strlen( vet_a[i].nome ) < 64 )
			vet_a[i].nome[ strlen( vet_a[i].nome ) - 1 ] = '\0';
	}
}
/* Passado um ponteiro de arquivo, e o numero de linhas do arquivo, cria o vetor
 vet_d e transcreve os valores necessiaros. */
void criaVetorDisciplina( FILE *fp, int numLinha ) {
	int i;
	numDisciplina = numLinha;
	vet_d = malloc( numDisciplina * sizeof( Disciplina ) );
	if( !vet_d ) masterError( "Impossivel reservar memoria para o vetor de disciplinas." );
	for( i = 0; i < numDisciplina; i++ ) {
		fgets( vet_d[i].sigla, 8, fp );
		fgetc( fp ); /* Espaco em Branco. */
		fgets( vet_d[i].nome, 64, fp );
		if( strlen( vet_d[i].nome ) < 64 )
			vet_d[i].nome[ strlen( vet_d[i].nome ) - 1 ] = '\0';
	}
}
/* Abre o arquivo em 'caminho' para leitura e descobre o numero de linhas
 (informado na primeira linha). Depois passa o ponteiro e o numero de linhas
 para a funcao 'func'. */
void leArquivoParaVetor( char caminho[], void (*func)( FILE *, int ) ) {
	FILE *fp;
	char str[8] = "";
	if( (fp = fopen(caminho,"r")) == NULL ){
		fprintf( stderr, "Arquivo '%s' nao pode ser aberto.\n", caminho );
		exit(-1);
	}
	fgets( str, 8, fp );
	(*func)( fp, atoi( str ) );
	fclose( fp );
}

/* Procura, por busca binaria, no vetor vet_a por um struct que tem nusp 'nusp'.
 Devolve o indice de tal struct se existir, ou -1 caso contrario. */
int indiceAluno( int nusp ) {
	int left = 0, right = numAluno - 1, i;
	while( left <= right ) {
		i = (left + right) / 2;
		if( vet_a[i].nusp == nusp )
			return i;
		else if( vet_a[i].nusp > nusp ) {
			right = i - 1;
		} else {
			left = i + 1;
		}
	}
	return -1;
}
/* Procura, por busca binaria, no vetor vet_a por um struct que tem nusp 'nusp'.
 Devolve o indice de tal struct se existir, ou -1 caso contrario. */
int indiceDisciplina( char disciplina[] ) {
	int left = 0, right = numDisciplina - 1, i, compara;
	while( left <= right ) {
		i = (left + right) / 2;
		compara = strcasecmp( disciplina, vet_d[ i ].sigla );
		if( compara == 0 )
			return i;
		else if( compara < 0 ) {
			right = i - 1;
		} else {
			left = i + 1;
		}
	}
	return -1;
}

/* Realiza a matricula do aluno com 'nusp' em 'disciplina', registrando o log em
 'fp_saida'. */
void matriculaAluno( int nusp, char disciplina[], FILE *fp_saida ) {
	int al = indiceAluno( nusp ), mid;
	pAluno_Disciplina p, prev = NULL, obj;
	if( al == -1 ) {
		fprintf( fp_saida, "\tErro: Aluno de nUSP '%d' nao existe.\n", nusp );
		return;
	}
	mid = indiceDisciplina( disciplina );
	if( mid == -1 ) {
		fprintf( fp_saida, "\tErro: Disciplina '%s' nao existe.\n", disciplina );
		return;
	}
	for( p = vet_a[al].inicio; p != NULL; p = p->prox_disc ) {
		if( p->ind_disc == mid ) {
			fprintf( fp_saida, "\tErro: Aluno de nUSP '%d' ja matriculado em '%s'.\n", nusp, disciplina );
			return;
		} else if( p->ind_disc > mid )
			break;
		prev = p;
	}
	obj = malloc( sizeof( Aluno_Disciplina ) );
	if( !obj ) masterError("Erro ao reservar memoria para Aluno_Disciplina.");
	obj->ind_aluno = al;
	obj->ind_disc = mid;
	obj->prox_disc = p;
	if( prev == NULL )
		vet_a[al].inicio = obj;
	else
		prev->prox_disc = obj;
	
	prev = NULL;
	for( p = vet_d[mid].inicio; p != NULL; p = p->prox_aluno ) {
		if( strcasecmp( vet_a[ al ].nome, vet_a[ p->ind_aluno ].nome ) < 0 )
			break;
		prev = p;
	}
	obj->prox_aluno = p;
	if( prev == NULL )
		vet_d[mid].inicio = obj;
	else
		prev->prox_aluno = obj;
	fprintf( fp_saida, "\tAluno de nUSP '%d' matriculado em '%s' com sucesso.\n", nusp, disciplina );
}
/* Cancela a matricula do aluno com 'nusp' em 'disciplina', registrando o log em
 'fp_saida'. */
void cancelaMatricula( int nusp, char disciplina[], FILE *fp_saida ) {
	int al = indiceAluno( nusp ), mid = indiceDisciplina( disciplina );
	pAluno_Disciplina p, prevAluno = NULL, prevDisc = NULL;
	if( al == -1 ) {
		fprintf( fp_saida, "\tErro: Aluno de nUSP '%d' nao existe.\n", nusp );
		return;
	}
	if( mid == -1 ) {
		fprintf( fp_saida, "\tErro: Disciplina '%s' nao existe.\n", disciplina );
		return;
	}
	
	for( p = vet_a[al].inicio; p != NULL; p = p->prox_disc ) {
		if( p->ind_disc == mid )
			break;
		prevAluno = p;
	}
	if( p == NULL ) {
		fprintf( fp_saida, "\tErro: Aluno de nUSP '%d' nao esta matriculado em '%s'.\n", nusp, disciplina );
		return;
	}
	for( p = vet_d[mid].inicio; p->ind_aluno != al; p = p->prox_aluno )
		prevDisc = p;
		
	if( prevAluno == NULL )
		vet_a[al].inicio = p->prox_disc;
	else
		prevAluno->prox_disc = p->prox_disc;
		
	if( prevDisc == NULL )
		vet_d[mid].inicio = p->prox_aluno;
	else
		prevDisc->prox_aluno = p->prox_aluno;
	
	free( p );
	fprintf( fp_saida, "\tMatricula de nUSP '%d' em '%s' cancelada com sucesso.\n", nusp, disciplina );
}
/* Lista em 'fp_saida' os alunos matriculados em 'disciplina'. */
void listaAlunosDaDisciplina( char disciplina[], FILE *fp_saida ) {
	int mid = indiceDisciplina( disciplina );
	pAluno_Disciplina p = NULL;
	if( mid == -1 ) {
		fprintf( fp_saida, "\tErro: Disciplina '%s' nao existe.\n", disciplina );
		return;
	}
	for( p = vet_d[mid].inicio; p != NULL; p = p->prox_aluno ) {
		fprintf( fp_saida, "\t%d %s\n", vet_a[p->ind_aluno].nusp, vet_a[p->ind_aluno].nome );
	}
}
/* Lista em 'fp_saida' as disciplinas em que o alunos 'nusp' está matriculado. */
void listaDisciplinasDoAluno( int nusp, FILE *fp_saida ) {
	int al = indiceAluno( nusp );
	pAluno_Disciplina p = NULL;
	if( al == -1 ) {
		fprintf( fp_saida, "\tErro: Aluno de nUSP '%d' nao existe.\n", nusp );
		return;
	}
	for( p = vet_a[al].inicio; p != NULL; p = p->prox_disc ) {
		fprintf( fp_saida, "\t%s %s\n", vet_d[p->ind_disc].sigla, vet_d[p->ind_disc].nome );
	}
}

/* Executa todas iteracoes listadas no arquivo 'caminho', colocando o log em 
 'fp_saida'. */
void executaIteracoes( char caminho[], FILE *fp_saida ) {
	FILE *fp_i;
	char str[8] = "", op;
	int num, i, nusp;
	if( (fp_i = fopen(caminho,"r")) == NULL ){
		fprintf( stderr, "Arquivo de instrucoes '%s' nao pode ser aberto.\n", caminho );
		exit(-1);
	}
	fgets( str, 8, fp_i );
	num = atoi( str );
	for( i = 0; i < num; i++ ) {
		op = fgetc( fp_i );
		fgetc( fp_i ); /* Espaco em branco. */
		switch( op ) {
			case 'M': /* Matricula um aluno NUM na materia SIGLA */
			case 'C': /* Cancela matricula de um aluno NUM na materia SIGLA */
				/* Numero USP*/
				fgets( str, 8, fp_i ); 
				nusp = atoi( str );
				
				/* Espaco em branco. */
				fgetc( fp_i );
				
				/* Sigla Materia */
				fgets( str, 8, fp_i );
				
				fprintf( fp_saida, "%c %d %s\n", op, nusp, str );
				if( op == 'M' )
					matriculaAluno( nusp, str, fp_saida );
				else
					cancelaMatricula( nusp, str, fp_saida );
				break;
			case 'A': /* Lista de alunos da materia SIGLA */
				/* Sigla Materia */
				fgets( str, 8, fp_i );
				
				fprintf( fp_saida, "%c %s\n", op, str );
				listaAlunosDaDisciplina( str, fp_saida );
				break;
			case 'D': /* Lista de materias do aluno NUM */
				/* Numero USP*/
				fgets( str, 8, fp_i ); 
				nusp = atoi( str );
				
				fprintf( fp_saida, "%c %d\n", op, nusp );
				listaDisciplinasDoAluno( nusp, fp_saida );
				break;
			default:
				fprintf( fp_saida, "Instrucao %d: Comando desconhecido '%c'\n", i + 1, op );
				break;
		}
		fprintf( fp_saida, "\n" );
		
		/* Removendo a quebra de linha para a proxima instrucao. */
		do {
			op = fgetc( fp_i );
		} while( op != '\n' );
	}
	fclose( fp_i );
}

	/* argc = numero de argumentos na linha de comando */
	/* argv = vetor de apontadores para strings contendo esses argumentos */
int main(int argc, char *argv[]) {
	FILE *fp_s; /* arquivo de saida */

	if( argc < 5 ){
		fprintf( stdout, "Uso: %s <arq_alunos> <arq_disc> <arq_instr> <arq_saida>\n", argv[0] );
		return -1;
	}
	
	leArquivoParaVetor( argv[1], criaVetorAluno );
	leArquivoParaVetor( argv[2], criaVetorDisciplina );


	if( (fp_s = fopen(argv[4],"w")) == NULL ){
		fprintf( stderr, "%s: arquivo de saida '%s' nao pode ser aberto.\n", argv[0], argv[4] );
		return -1;
	}
	executaIteracoes( argv[3], fp_s );
		
	fclose(fp_s);
	return 0;
}
