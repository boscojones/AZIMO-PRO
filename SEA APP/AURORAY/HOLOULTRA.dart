#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estrutura para armazenar dados de análise
typedef struct {
    int total;
    double average;
} AnalysisResult;

// Estrutura para passar dados para a thread
typedef struct {
    const char *thread_name;
    int *data;
    size_t size;
} ThreadData;

// Função para calcular total e média dos dados
AnalysisResult analyzeData(int *data, size_t size) {
    AnalysisResult result;
    result.total = 0;
    for (size_t i = 0; i < size; i++) {
        result.total += data[i];
    }
    result.average = (double)result.total / size;
    return result;
}

// Função que simula o processamento dos dados na thread
void* runProcessing(void* arg) {
    ThreadData *threadData = (ThreadData*)arg;
    printf("Iniciando o processamento no thread: %s\n", threadData->thread_name);

    for (size_t i = 0; i < threadData->size; i++) {
        // Simulação de processamento
        printf("Thread %s processando valor: %d\n", threadData->thread_name, threadData->data[i]);
    }

    printf("Processamento no thread %s finalizado.\n", threadData->thread_name);
    return NULL;
}

int main() {
    // Exemplo de dados a serem analisados e processados
    int data[] = {10, 20, 30, 40, 50};
    size_t dataSize = sizeof(data) / sizeof(data[0]);

    // Executar análise
    AnalysisResult results = analyzeData(data, dataSize);

    // Criação das threads
    pthread_t threads[3];
    ThreadData threadData[3];

    // Configurar e criar threads
    for (int i = 0; i < 3; i++) {
        threadData[i].thread_name = (i == 0) ? "Thread1" : (i == 1) ? "Thread2" : "Thread3";
        threadData[i].data = data;
        threadData[i].size = dataSize;

        if (pthread_create(&threads[i], NULL, runProcessing, (void*)&threadData[i])) {
            fprintf(stderr, "Erro ao criar thread %d\n", i + 1);
            return 1;
        }
    }

    // Espera as threads finalizarem
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // Relatório Final
    printf("Relatório Final:\n");
    printf("Total: %d\n", results.total);
    printf("Média: %.2f\n", results.average);

    return 0;
}
