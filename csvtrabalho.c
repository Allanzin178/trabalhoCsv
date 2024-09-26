#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//	O que deve ser feito:
//	O programa a ser construído deve ler dados de cada processo, identificando cada um dos atributos acima para, a seguir, realizar as seguintes operações:
//	
//	Ordenar, em ordem crescente, o conjunto de dados a partir do atributo “id”;
//	Ordenar, em ordem decrescente, o conjunto de dados a partir do atributo “data_ajuizamento”;
//	Contar quantos processos estão vinculados a um determinado “id_classe”;
//	Identificar quantos “id_assuntos” constam nos processos presentes na base de dados; e
//	Indicar a quantos dias um processo está em tramitação na justiça.
//
//	Observações:
//	Os dados devem ser organizados em vetores de structs.
//	As respostas dos itens 1 e 2 devem ser armazenados em arquivo “cvs”, mantendo cabeçalho.
//	Deve ser implementada 1 (uma) função para resolver cada item indicado acima.
//	O código-fonte deve ser modularizado em três arquivos, conforme indicado nas aulas de agosto/2024.
//	Este trabalho prático pode ser desenvolvido em grupos de até 4 integrantes e vale 3 pontos.
//	Caso seja entregue com atraso, o valor total será reduzidao à taxa de 10% por dia de atraso.
//	O código-fonte deve ser enviado pelo AVA e disponibilizado no Git.
//	Trabalhos iguais ou com seções iguais/parecidos terão nota 0.
//	Na biblioteca string.h existem funções para manipulação de strings que podem ser úteis.

typedef struct{

	int id;
	char numero[20];
	char data_ajuizamento[23];
	int id_classe;
	int id_assunto;
	int ano_eleicao;
	
} Processo;

typedef struct{
	
	char *id;
	char *numero;
	char *data_ajuizamento;
	char *id_classe;
	char *id_assunto;
	char *ano_eleicao;
	
} Titulo;

Titulo criar_titulo();
Processo criar_processo();
int conta_linhas();

int main() {
    FILE *fp;
    int i;
    char linha[255];
	
	Titulo t = criar_titulo();
    Processo processo[100];
    
    // Abre o arquivo para leitura
    fp = fopen("processo_043_202409032338.csv", "r");
    
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    printf("Tamanho do char: %d\n",sizeof(char));
    printf("Arquivo aberto com sucesso!\n");
    
    printf("%d", conta_linhas(fp));
    
//    for(i = 0; fgets(linha, sizeof(linha), fp) != NULL; i++){
//    	if(i == 0){
//    		fscanf(fp, "%[^,] %[^,] %[^,] %[^,] %[^,] %[^,]", 
//				t.id, 
//				t.numero, 
//				t.data_ajuizamento, 
//				t.id_classe, 
//				t.id_assunto, 
//				t.ano_eleicao);
//	    		printf("%s", linha);
//    		continue;
//		}
//		fscanf(fp, "%d %[^,] %[^,] {%d} {%d} %d", 
//			&processo[i - 1].id, 
//			processo[i - 1].numero, 
//			processo[i - 1].data_ajuizamento,
//			&processo[i - 1].id_classe,
//			&processo[i - 1].id_assunto,
//			&processo[i - 1].ano_eleicao);
//			printf("%s", linha);
//	}
    
    return 0;
}

Titulo criar_titulo() {
    Titulo t;
    t.id = (char *)malloc(70); 
    t.numero = (char *)malloc(70);
    t.data_ajuizamento = (char *)malloc(70);
    t.id_classe = (char *)malloc(70);
    t.id_assunto = (char *)malloc(70);
    t.ano_eleicao = (char *)malloc(70);

    
    if (!t.id || !t.numero || !t.data_ajuizamento || !t.id_classe || !t.id_assunto || !t.ano_eleicao) {
        printf("Erro ao alocar memória!");
    }

    return t;
}

Processo criar_processo() {
	
}

int conta_linhas(FILE *fp){
	int n;
	char linha[255];
	for(n = 0; fgets(linha, sizeof(linha), fp); n++);
	return n;
}

