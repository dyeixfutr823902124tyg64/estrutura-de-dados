#ifndef PROCESSO_H
#define PROCESSO_H

#define MAX_NUMERO 30
#define MAX_ASSUNTOS 10
#define MAX_LINHA 200
#define MAX_PROCESSOS 10000

typedef struct {
    int id;
    char numero[MAX_NUMERO];
    char data_ajuizamento[20];
    int id_classe;
    int id_assunto[MAX_ASSUNTOS];
    int qtd_assuntos;
    int ano_eleicao;
} Processo;

void lerArquivoCSV(const char *nomeArquivo, Processo processos[], int *qtd);
void salvarCSV(const char *nomeArquivo, Processo processos[], int qtd);
void ordenarPorId(Processo processos[], int qtd);
void ordenarPorData(Processo processos[], int qtd);

#endif