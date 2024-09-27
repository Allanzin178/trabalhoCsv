#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char numero[255];
    char data_ajuizamento[255];
    int id_classe[8];
    int id_assunto[8];
    int ano_eleicao;
} Processo;

Processo *criarProcesso(int numLinhas, int maxClassesAssuntos);
int contLinhas(FILE *fp);
void lerCsv(FILE *fp, Processo *p, int numLinhas);
void ordenarIdCsv(Processo *p, int n);
void ordenarDataCsv(Processo *p, int n);
int contClasse(Processo *p, int n, int id);
int idAssuntos(Processo *p, int n);

int main(){
    FILE *fp;
    
    system("cls");
    
    fp = fopen("processo_043_202409032338.csv", "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    int numLinhas = contLinhas(fp) - 1;
    Processo *p = criarProcesso(numLinhas, 8);

    // ------------------------------------------------------------------


    lerCsv(fp, p, numLinhas);

    // ordenarIdCsv(p, numLinhas);

    // for(int i = 0; i < numLinhas; i++){
    //     printf("ID: %d\n", 
    //            p[i].id);
    // }

    // ordenarDataCsv(p,numLinhas);

    // for(int i = 0; i < numLinhas; i++){
    //     printf("Data: %s\n", 
    //            p[i].data_ajuizamento);
    // }

    printf("Quantidade de processos com a classe %d: %d\n", 11533, contClasse(p,numLinhas,11533));
    printf("Quantidade de assuntos diferentes: %d", idAssuntos(p,numLinhas));

    free(p);
    fclose(fp);
}

Processo *criarProcesso(int numLinhas, int maxClassesAssuntos){
    Processo *p = (Processo*) malloc(numLinhas * sizeof(Processo));
    if(p == NULL){
        printf("Erro na alocação de memória (malloc)");
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

void lerCsv(FILE *fp, Processo *p, int numLinhas){
    int i, j, cont, virg[2] = {0, 0}, fChave = 0;
    char linha[255];
    char *rem;

    // Faz o L
    fgets(linha, sizeof(linha), fp);

    for(i = 0; i < numLinhas; i++){
        if(fgets(linha, sizeof(linha), fp) == NULL){
            break;
        };
        
        cont = 0;
        virg[0] = 0;
        virg[1] = 0;
        fChave = 0;

        // O CODIGO
        for(j = 0; j < strlen(linha); j++){
            if(linha[j] == '{'){
                int contagem = 0;
                for(int k = j + 1; linha[k] != '}'; k++){
                    if (linha[k] == ','){
                        contagem++;
                    }
                }
                if (fChave == 0) {
                    virg[0] = contagem;
                    fChave = 1;
                } else {
                    virg[1] = contagem;
                    break;
                }
            }
        }
        // O CODIGO

        rem = strtok(linha, ",\"{}");
        while(rem != NULL && cont < 6){
            switch(cont){
                case 0:
                    p[i].id = atoi(rem);
                    break;
                case 1:
                    strcpy(p[i].numero, rem);
                    break;
                case 2:
                    strcpy(p[i].data_ajuizamento, rem);
                    break;
                case 3:
                    for(j = 0; j <= virg[0] && j < 8; j++){
                        p[i].id_classe[j] = atoi(rem);
                        rem = strtok(NULL, ",\"{}");
                    }
                    cont++;
                    continue;
                case 4:
                    for(j = 0; j <= virg[1] && j < 8; j++){
                        p[i].id_assunto[j] = atoi(rem);
                        rem = strtok(NULL, ",\"{}");
                    }
                    cont++;
                    continue;
                case 5:
                    p[i].ano_eleicao = atoi(rem);
                    break;
            }
            rem = strtok(NULL, ",\"{}");
            cont++;
        }
    }
}

void ordenarIdCsv(Processo *p, int n){
        int i, j;
        Processo temp;
        //Ira ler termo por termo
        for (i = 0; i < n; i++) {
            //Ira comparar termo por termo
            for (j = 0; j < n-1; j++) {
                // Troca os elementos
                if (p[j].id > p[j + 1].id){
                    temp = p[j];
                    p[j] = p[j+1];
                    p[j+1] = temp;
                }
            }
        }
}

void ordenarDataCsv(Processo *p, int n){
        int i, j;
        Processo temp;
        //Ira ler termo por termo
        for (i = 0; i < n; i++) {
            //Ira comparar termo por termo
            for (j = 0; j < n-1; j++) {
                // Troca os elementos
                if (strcmp(p[j].data_ajuizamento, p[j + 1].data_ajuizamento) < 0){
                    temp = p[j];
                    p[j] = p[j+1];
                    p[j+1] = temp;
                }
            }
        }
}

int contClasse(Processo *p, int n, int id){
    int cont;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 8; j++){
            if(p[i].id_classe[j] == id){
                cont++;
            }
        }
    }
    return cont;
}

int idAssuntos(Processo *p, int n){
    int *dif = malloc(n * sizeof(int));
    int cont = 0;
    int novo = 1;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < cont; k++){
                if(dif[cont] == p[i].id_assunto[j]){
                    novo = 0;
                    break;
                }
            }
            printf("Teste! %d\n %d\n", i, p[i].id_assunto[j]);
        }
        if (novo == 1){
                printf("Teste! %d\n %d\n", i, p[i].id_assunto[i]);
                dif[cont] = p[i].id_assunto[i];
                cont++;
        }
        
    }
    free(dif);
    return cont;
}