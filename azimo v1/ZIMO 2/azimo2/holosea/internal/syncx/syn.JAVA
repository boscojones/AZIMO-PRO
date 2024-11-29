#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

// Definição da estrutura ClosableMutex
typedef struct {
    pthread_mutex_t mutex; // Mutex do pthread
    bool isClosed;         // Indica se o mutex foi fechado
} ClosableMutex;

// Função para criar um novo ClosableMutex
ClosableMutex* newClosableMutex() {
    ClosableMutex* cmutex = (ClosableMutex*)malloc(sizeof(ClosableMutex));
    pthread_mutex_init(&cmutex->mutex, NULL);
    cmutex->isClosed = false;
    return cmutex;
}

// Função para tentar bloquear o mutex
bool tryLock(ClosableMutex* cmutex) {
    if (cmutex->isClosed) {
        return false; // Mutex fechado
    }
    if (pthread_mutex_trylock(&cmutex->mutex) == 0) {
        return true; // Bloqueio bem-sucedido
    }
    return false; // Falha ao bloquear o mutex
}

// Função que deve bloquear o mutex ou lançar erro
void mustLock(ClosableMutex* cmutex) {
    if (cmutex->isClosed) {
        printf("Erro: mutex fechado.\n");
        exit(EXIT_FAILURE);
    }
    pthread_mutex_lock(&cmutex->mutex);
}

// Função para desbloquear o mutex
void unlock(ClosableMutex* cmutex) {
    if (cmutex->isClosed) {
        printf("Erro: tentando desbloquear um mutex já fechado.\n");
        exit(EXIT_FAILURE);
    }
    pthread_mutex_unlock(&cmutex->mutex);
}

// Função para fechar o mutex
void closeMutex(ClosableMutex* cmutex) {
    if (cmutex->isClosed) {
        printf("Erro: tentando fechar um mutex já fechado.\n");
        exit(EXIT_FAILURE);
    }
    cmutex->isClosed = true;
    pthread_mutex_destroy(&cmutex->mutex); // Destrói o mutex
    free(cmutex); // Libera a memória
}

int main() {
    // Exemplo de uso do ClosableMutex
    ClosableMutex* cmutex = newClosableMutex();

    if (tryLock(cmutex)) {
        printf("Mutex bloqueado com tryLock.\n");
    } else {
        printf("Falha ao tentar bloquear o mutex com tryLock.\n");
    }

    unlock(cmutex);
    closeMutex(cmutex);

    return 0;
}
