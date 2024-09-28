#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"
#include <time.h>

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

    printf("Quantidade de processos com a classe %d: %d\n", 11533, contClasse(p,numLinhas,11533));
    printf("Quantidade de assuntos diferentes: %d\n", idAssuntos(p,numLinhas));

    printf("Dias do processo em tramitação até 27/09/2024: %d \n",diasProcesso(p,numLinhas,405280783));

    ordenarIdCsv(p, numLinhas);
    salvarCsv(p, numLinhas, "ordenandoID.csv");


    ordenarDataCsv(p, numLinhas);
    salvarCsv(p, numLinhas, "ordenandoDATA.csv");

    free(p);
    fclose(fp);
}

    