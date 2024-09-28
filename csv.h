#ifndef CSV_H
#define CSV_H

typedef struct {
    int id;
    char numero[255];
    char data_ajuizamento[255];
    int id_classe[8];
    int id_assunto[8];
    int ano_eleicao;
} Processo;

typedef struct{
    int ano;
    int mes;
    int dia;
} Data;

Processo *criarProcesso(int numLinhas, int maxClassesAssuntos);
int contLinhas(FILE *fp);
void lerCsv(FILE *fp, Processo *p, int numLinhas);
void ordenarIdCsv(Processo *p, int n);
void ordenarDataCsv(Processo *p, int n);
int contClasse(Processo *p, int n, int id);
int idAssuntos(Processo *p, int n);
int diasProcesso(Processo *p, int n, int id);
void salvarCsv(Processo *p, int n, char *nome_arquivo);

#endif