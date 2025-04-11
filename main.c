#include "processo.h"

int main() {
    Processo processos[MAX_PROCESSOS];
    int qtd;

    lerArquivoCSV("processo_043_202409032338.csv", processos, &qtd);
    
    ordenarPorId(processos, qtd);
    printf("Processos ordenados por ID e salvos em CSV!\n");
    
    ordenarPorData(processos, qtd);
    printf("Processos ordenados por Data de Ajuizamento e salvos em CSV!\n");

    return 0;
}