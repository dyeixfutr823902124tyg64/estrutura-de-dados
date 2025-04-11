#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processo.h"

void lerArquivoCSV(const char *nomeArquivo, Processo processos[], int *qtd) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[MAX_LINHA];
    fgets(linha, MAX_LINHA, arquivo);
    *qtd = 0;

    while (fgets(linha, MAX_LINHA, arquivo) && *qtd < MAX_PROCESSOS) {
        Processo p;
        p.qtd_assuntos = 0;

        char *token = strtok(linha, ",");
        p.id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(p.numero, token + 1);
        p.numero[strlen(p.numero) - 1] = '\0';

        token = strtok(NULL, ",");
        strcpy(p.data_ajuizamento, token);

        token = strtok(NULL, "{} ");
        p.id_classe = atoi(token);

        token = strtok(NULL, "{} ");
        while (token) {
            p.id_assunto[p.qtd_assuntos++] = atoi(token);
            token = strtok(NULL, "{} ");
        }

        token = strtok(NULL, ",");
        p.ano_eleicao = atoi(token);

        processos[(*qtd)++] = p;
    }
    fclose(arquivo);
}

void salvarCSV(const char *nomeArquivo, Processo processos[], int qtd) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        printf("Erro ao criar arquivo %s\n", nomeArquivo);
        return;
    }
    fprintf(arquivo, "id,numero,data_ajuizamento,id_classe,id_assunto,ano_eleicao\n");
    for (int i = 0; i < qtd; i++) {
        fprintf(arquivo, "%d,%s,%s,%d,{%d},%d\n",
                processos[i].id,
                processos[i].numero,
                processos[i].data_ajuizamento,
                processos[i].id_classe,
                processos[i].id_assunto[0],
                processos[i].ano_eleicao);
    }
    fclose(arquivo);
}

void ordenarPorId(Processo processos[], int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        int min = i;
        for (int j = i + 1; j < qtd; j++) {
            if (processos[j].id < processos[min].id) {
                min = j;
            }
        }
        Processo temp = processos[i];
        processos[i] = processos[min];
        processos[min] = temp;
    }
    salvarCSV("ordenado_por_id.csv", processos, qtd);
}

void ordenarPorData(Processo processos[], int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (strcmp(processos[j].data_ajuizamento, processos[j + 1].data_ajuizamento) < 0) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
    salvarCSV("ordenado_por_data.csv", processos, qtd);
}