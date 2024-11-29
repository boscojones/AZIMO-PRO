#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_LAKES 5
#define MAX_OBJECTS 100
#define OBJECT_NAME_LENGTH 50

typedef struct {
    char name[OBJECT_NAME_LENGTH];
    float attribute; // Um atributo que pode ser aprendido
} HoloFiObject;

typedef struct {
    HoloFiObject objects[MAX_OBJECTS];
    int object_count;
} Lake;

// Estrutura para passar dados entre threads
typedef struct {
    Lake* lake;
    int index;
} ThreadData;

// Função que simula o aprendizado de máquina
void learn(HoloFiObject* object) {
    // Simula o aprendizado adaptando o atributo do objeto
    object->attribute += 0.1f; // Simula um aumento no atributo
}

// Função que adapta objetos dentro de um lake
void* adapt_objects(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    Lake* lake = data->lake;

    for (int i = data->index; i < lake->object_count; i++) {
        learn(&lake->objects[i]);
        printf("Adaptado objeto %s com novo atributo: %.2f\n", 
               lake->objects[i].name, lake->objects[i].attribute);
    }

    return NULL;
}

// Função de busca que retorna objetos adaptados
void search_and_adapt(Lake* lake) {
    pthread_t threads[MAX_LAKES];
    ThreadData thread_data[MAX_LAKES];

    // Cria uma thread para cada objeto no lake
    for (int i = 0; i < lake->object_count; i++) {
        thread_data[i].lake = lake;
        thread_data[i].index = i;

        if (pthread_create(&threads[i], NULL, adapt_objects, (void*)&thread_data[i])) {
            fprintf(stderr, "Erro ao criar a thread para o objeto %s\n", lake->objects[i].name);
            exit(EXIT_FAILURE);
        }
    }

    // Aguarda a conclusão das threads
    for (int i = 0; i < lake->object_count; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    // Inicializa os lakes e objetos
    Lake lakes[MAX_LAKES];

    for (int i = 0; i < MAX_LAKES; i++) {
        lakes[i].object_count = 0; // Inicializa contagem de objetos

        for (int j = 0; j < MAX_OBJECTS; j++) {
            snprintf(lakes[i].objects[j].name, OBJECT_NAME_LENGTH, "Objeto %d do Lake %d", j + 1, i + 1);
            lakes[i].objects[j].attribute = rand() % 10; // Atributo inicial aleatório
            lakes[i].object_count++;
        }
    }

    // Exemplo de busca e adaptação em um lake
    for (int i = 0; i < MAX_LAKES; i++) {
        printf("Adaptando objetos no Lake %d...\n", i + 1);
        search_and_adapt(&lakes[i]);
    }

    return 0;
}
