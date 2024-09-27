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

void lerCsv(FILE *fp, Processo *p){
    int i, j, k, cont, virg[2] = {0, 0}, fChave = 0;
    char linha[255];
    char *rem;

    for(i = 0; fgets(linha, sizeof(linha), fp); i++){
        cont = 0;
        if(i == 0){
            continue;
        }
        // NAO TOCA NO MEU CODIGO :<
            for(i = 30; i < sizeof(linha); i++){
                if(linha[i] == '{'){  
                    for(j = i; linha[j] != '}' && fChave == 0; j++){
                        if (linha[j] == ','){
                            virg[0] = virg[0] + 1;
                        }
                        if (linha[j + 1] == '}'){
                            fChave++;
                        }
                    }
                    if(linha[i-3] == '}'){
                        for(j = i; linha[j] != '}' && fChave > 0; j++){
                            if (linha[j] == ','){
                                virg[1] = virg[1] + 1;
                            }
                            if (linha[j + 1] == '}'){
                                fChave++;
                            }
                        }
                    }
                    
                }
            }

        // NAO TOCA NO MEU CODIGO :<

        rem = strtok(linha, ",\"{}");
        // Armazenando
        while(rem != NULL && cont < 6){
            // Inicio do switch
            switch(cont){
                case 0:
                    p[i - 1].id = atoi(rem);
                    printf("%d ", p[i - 1].id);
                    rem = strtok(NULL, ",\"{}");
                    break;
                
                case 1:
                    strcpy(p[i-1].numero, rem);
                    printf("%s ", p[i - 1].numero);
                    rem = strtok(NULL, ",\"{}");
                    break;
                case 2:
                    strcpy(p[i-1].data_ajuizamento, rem);
                    printf("%s ", p[i - 1].data_ajuizamento);
                    rem = strtok(NULL, ",\"{}");
                    break;
                case 3:
                    printf(" | ");
                    printf("virg: %d ",virg[0]);
                    for(j = 0; j <= virg[0]; j++){
                        p[i-1].id_classe[j] = atoi(rem);
                        printf("%d ", p[i - 1].id_classe[j]);
                        rem = strtok(NULL, ",\"{}");
                    }
                    printf(" | ");
                    break;
                case 4:
                    printf("virg1: %d ",virg[1]);
                    for(j = 0; j <= virg[1]; j++){
                        p[i-1].id_assunto[j] = atoi(rem);
                        printf("%d ", p[i - 1].id_assunto[j]);
                        rem = strtok(NULL, ",\"{}");
                    }
                    printf("\n");
                    break;
            }
            
            cont++;
            
        }
        virg[0] = 0;
        virg[1] = 0;
        fChave = 0;
    }
}