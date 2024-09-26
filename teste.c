#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 1024

typedef struct {
    int id;
    char numero[20];
    char data_ajuizamento[20];
    int id_classe[10]; // Adaptar o tamanho conforme necessário
    int id_assunto;
    int ano_eleicao;
} Processo;

int compararPorId(const void *a, const void *b) {
    Processo *pa = (Processo*)a;
    Processo *pb = (Processo*)b;
    return pa->id - pb->id;
}

int main() {
    FILE *arquivo;
    char linha[MAX_LINHA];
    Processo processos[100]; // Ajuste o tamanho conforme necessário
    int num_processos = 0;

    // Abrir o arquivo CSV
    arquivo = fopen("./teste.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ler cada linha do arquivo
    while (fgets(linha, MAX_LINHA, arquivo)) {
        // ... (lógica para converter a linha em uma estrutura Processo e adicionar ao vetor)
        // Exemplo simplificado, adaptando para o seu formato de CSV:
        sscanf(linha, "%d,%[^,],%[^,],%d,%d,%d",
               &processos[num_processos].id,
               processos[num_processos].numero,
               processos[num_processos].data_ajuizamento,
               &processos[num_processos].id_classe[0], // Assumindo que id_classe tem apenas um elemento
               &processos[num_processos].id_assunto,
               &processos[num_processos].ano_eleicao);
        num_processos++;
    }

    // Fechar o arquivo
    fclose(arquivo);

    // Ordenar os processos por ID
    qsort(processos, num_processos, sizeof(Processo), compararPorId);

    // Imprimir os processos ordenados
    for (int i = 0; i < num_processos; i++) {
        printf("ID: %d, Numero: %s, Data: %s\n",
               processos[i].id, processos[i].numero, processos[i].data_ajuizamento);
    }

    return 0;
}