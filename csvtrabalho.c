#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char numero[255];
    char data_ajuizamento[255];
    int *id_classe;
    int *id_assunto;
    int ano_eleicao;
} Processo;

Processo *criarProcesso();
int contLinhas();
void lerCsv();

int main(){
    FILE *fp;
    
    system("cls");
    fp = fopen("processo_043_202409032338.csv", "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    int numLinhas = contLinhas(fp);
    Processo *p = criarProcesso(numLinhas, 8);

    // ------------------------------------------------------------------

    lerCsv(fp, p);

    fclose(fp);
}

Processo *criarProcesso(int numLinhas, int maxClassesAssuntos){
    Processo *p = (Processo*) malloc(numLinhas * sizeof(Processo));
    p->id_classe = (int*) malloc(maxClassesAssuntos * sizeof(int));
    p->id_assunto = (int*) malloc(maxClassesAssuntos * sizeof(int));

    if(p == NULL || p->id_classe == NULL || p->id_assunto == NULL){
        printf("Erro na alocação de memória (malloc)");
        free(p);
        exit(1);
    }
    memset(p->numero, 0, sizeof(p->numero));
    memset(p->data_ajuizamento, 0, sizeof(p->data_ajuizamento));
    p->id = 0;
    p->ano_eleicao = 0;
    return p;
}

int contLinhas(FILE *fp){
    char linha[255];
    int i;
    for(i = 0; fgets(linha, sizeof(linha), fp) != NULL; i++);
    rewind(fp);
    return i;
}

void lerCsv(FILE *fp, Processo *p){
    int i, j, cont;
    char linha[255];
    char *rem = strtok(linha, ",");

    for(i = 0; fgets(linha, sizeof(linha), fp); i++){
        if(i == 0){
            continue;
        }
        sscanf(linha, "%d, %[^,], %[^,],{%d %d %d %d",
            &p->id, 
            p->numero,
            p->data_ajuizamento,
            &p->id_classe[0],
            &p->id_classe[1],
            &p->id_assunto[0],
            &p->ano_eleicao);

        printf("%d - %s - %s - %d - %d - %d - %d\n",
            p->id, 
            p->numero,
            p->data_ajuizamento,
            p->id_classe[0],
            p->id_classe[1],
            p->id_assunto[0],
            p->ano_eleicao);
    }
}