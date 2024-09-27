#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char numero[20];
    char data_ajuizamento[23];
    int id_classe;
    int id_assunto;
    int ano_eleicao;
} Processo;

typedef struct {
    char *id;
    char *numero;
    char *data_ajuizamento;
    char *id_classe;
    char *id_assunto;
    char *ano_eleicao;
} Titulo;

Titulo criar_titulo();
Processo criar_processo();
void imprimir_processos(Processo *processos, int num_processos);
void imprime_processo(FILE *fp);
int conta_linhas(FILE *fp);
void ler_processos(FILE *fp, Processo *processos, int num_processos);
void ordenar_por_id(Processo *processos, int num_processos);
void ordenar_por_data(Processo *processos, int num_processos);
int contar_processos_por_classe(Processo *processos, int num_processos, int id_classe);
int contar_assuntos_distintos(Processo *processos, int num_processos);
int calcular_dias_tramitacao(char *data_ajuizamento);
void salvar_processos_csv(Processo *processos, int num_processos, const char *nome_arquivo);

int main() {
    FILE *fp;
    
    fp = fopen("processo_043_202409032338.csv", "r");
    
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    
    int num_processos = conta_linhas(fp) - 1; // -1 para excluir o cabeçalho
    Processo *processos = (Processo *) malloc(num_processos * sizeof(Processo));
    
    if (processos == NULL) {
        printf("Erro ao alocar memória para os processos\n");
        fclose(fp);
        exit(1);
    }
    
    ler_processos(fp, processos, num_processos);
    imprimir_processos(processos, num_processos);
    
    // 1. Ordenar por ID e salvar
    ordenar_por_id(processos, num_processos);
    salvar_processos_csv(processos, num_processos, "processos_ordenados_id.csv");
    
    // 2. Ordenar por data de ajuizamento e salvar
    ordenar_por_data(processos, num_processos);
    salvar_processos_csv(processos, num_processos, "processos_ordenados_data.csv");
    
    // 3. Contar processos por classe (exemplo com id_classe = 12554)
    int id_classe_exemplo = 12554;
    int count_classe = contar_processos_por_classe(processos, num_processos, id_classe_exemplo);
    printf("Número de processos com id_classe %d: %d\n", id_classe_exemplo, count_classe);
    
    // 4. Contar assuntos distintos
    int num_assuntos = contar_assuntos_distintos(processos, num_processos);
    printf("Número de id_assuntos distintos: %d\n", num_assuntos);
    
    // 5. Calcular dias em tramitação (exemplo com o primeiro processo)
    int dias_tramitacao = calcular_dias_tramitacao(processos[0].data_ajuizamento);
    printf("Dias em tramitação do primeiro processo: %d\n", dias_tramitacao);
    
    free(processos);
    fclose(fp);
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
    Processo p;
    p.id = 0;
    memset(p.numero, 0, sizeof(p.numero));
    memset(p.data_ajuizamento, 0, sizeof(p.data_ajuizamento));
    p.id_classe = 0;
    p.id_assunto = 0;
    p.ano_eleicao = 0;
    return p;
}

int conta_linhas(FILE *fp) {
    int n;
    char linha[255];
    for(n = 0; fgets(linha, sizeof(linha), fp); n++);
    rewind(fp);
    return n;
}

void imprime_processo(FILE *fp) {
    int i, j;
    char linha[255];
    for(i = 0; fgets(linha, sizeof(linha), fp) != NULL; i++) {
        printf("%s", linha);
    }
}

void imprimir_processos(Processo *processos, int num_processos) {
    printf("ID\tNúmero\t\t\tData Ajuizamento\t\tID Classe\tID Assunto\tAno Eleição\n");
    printf("---------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < num_processos; i++) {
        printf("%d\t%s\t%s\t%d\t\t%d\t\t%d\n",
               processos[i].id,
               processos[i].numero,
               processos[i].data_ajuizamento,
               processos[i].id_classe,
               processos[i].id_assunto,
               processos[i].ano_eleicao);
    }
}

void ler_processos(FILE *fp, Processo *processos, int num_processos) {
    char linha[255];
    int i = 0;
    
    // Pula a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), fp);
    
    while (fgets(linha, sizeof(linha), fp) != NULL && i < num_processos) {
        char *token;
        int campo = 0;
        
        // Usamos vírgulas, aspas duplas e chaves como delimitadores
        token = strtok(linha, ",\"{}");
        while (token != NULL && campo < 6) {
            switch(campo) {
                case 0:
                    processos[i].id = atoi(token);
                    break;
                case 1:
                    strncpy(processos[i].numero, token, sizeof(processos[i].numero) - 1);
                    processos[i].numero[sizeof(processos[i].numero) - 1] = '\0';
                    break;
                case 2:
                    strncpy(processos[i].data_ajuizamento, token, sizeof(processos[i].data_ajuizamento) - 1);
                    processos[i].data_ajuizamento[sizeof(processos[i].data_ajuizamento) - 1] = '\0';
                    break;
                case 3:
                    processos[i].id_classe = atoi(token);
                    break;
                case 4:
                    processos[i].id_assunto = atoi(token);
                    break;
                case 5:
                    processos[i].ano_eleicao = atoi(token);
                    break;
            }
            token = strtok(NULL, ",\"{}");
            campo++;
        }
        i++;
    }
}

void ordenar_por_id(Processo *processos, int num_processos) {
    for (int i = 0; i < num_processos - 1; i++) {
        for (int j = 0; j < num_processos - i - 1; j++) {
            if (processos[j].id > processos[j + 1].id) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
}

void ordenar_por_data(Processo *processos, int num_processos) {
    for (int i = 0; i < num_processos - 1; i++) {
        for (int j = 0; j < num_processos - i - 1; j++) {
            if (strcmp(processos[j].data_ajuizamento, processos[j + 1].data_ajuizamento) < 0) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
}

int contar_processos_por_classe(Processo *processos, int num_processos, int id_classe) {
    int count = 0;
    for (int i = 0; i < num_processos; i++) {
        if (processos[i].id_classe == id_classe) {
            count++;
        }
    }
    return count;
}

int contar_assuntos_distintos(Processo *processos, int num_processos) {
    int *assuntos = malloc(num_processos * sizeof(int));
    int count = 0;
    
    for (int i = 0; i < num_processos; i++) {
        int is_new = 1;
        for (int j = 0; j < count; j++) {
            if (assuntos[j] == processos[i].id_assunto) {
                is_new = 0;
                break;
            }
        }
        if (is_new) {
            assuntos[count] = processos[i].id_assunto;
            count++;
        }
    }
    
    free(assuntos);
    return count;
}

int calcular_dias_tramitacao(char *data_ajuizamento) {
    struct tm tm_ajuizamento = {0};
    sscanf(data_ajuizamento, "%d-%d-%d", &tm_ajuizamento.tm_year, &tm_ajuizamento.tm_mon, &tm_ajuizamento.tm_mday);
    tm_ajuizamento.tm_year -= 1900;
    tm_ajuizamento.tm_mon -= 1;
    
    time_t t_ajuizamento = mktime(&tm_ajuizamento);
    time_t t_atual = time(NULL);
    
    return (int)difftime(t_atual, t_ajuizamento) / (60 * 60 * 24);
}

void salvar_processos_csv(Processo *processos, int num_processos, const char *nome_arquivo) {
    FILE *fp = fopen(nome_arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao criar arquivo %s\n", nome_arquivo);
        return;
    }
    
    fprintf(fp, "id,numero,data_ajuizamento,id_classe,id_assunto,ano_eleicao\n");
    
    for (int i = 0; i < num_processos; i++) {
        fprintf(fp, "%d,\"%s\",%s,{%d},{%d},%d\n",
                processos[i].id,
                processos[i].numero,
                processos[i].data_ajuizamento,
                processos[i].id_classe,
                processos[i].id_assunto,
                processos[i].ano_eleicao);
    }
    
    fclose(fp);
}