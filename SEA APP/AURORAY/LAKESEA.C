#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_INPUT 10
#define NUM_HIDDEN 20
#define NUM_OUTPUT 3
#define MAX_EPOCHS 1000
#define LEARNING_RATE 0.01

// Função Sigmoid
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Derivada da função Sigmoid
double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

// Inicializa pesos aleatórios
void initialize_weights(double weights_input_hidden[NUM_INPUT][NUM_HIDDEN], double weights_hidden_output[NUM_HIDDEN][NUM_OUTPUT]) {
    for (int i = 0; i < NUM_INPUT; i++) {
        for (int j = 0; j < NUM_HIDDEN; j++) {
            weights_input_hidden[i][j] = ((double) rand() / RAND_MAX) * 2.0 - 1.0;
        }
    }
    for (int i = 0; i < NUM_HIDDEN; i++) {
        for (int j = 0; j < NUM_OUTPUT; j++) {
            weights_hidden_output[i][j] = ((double) rand() / RAND_MAX) * 2.0 - 1.0;
        }
    }
}

// Feedforward
void feedforward(double input[NUM_INPUT], double hidden[NUM_HIDDEN], double output[NUM_OUTPUT], 
                 double weights_input_hidden[NUM_INPUT][NUM_HIDDEN], double weights_hidden_output[NUM_HIDDEN][NUM_OUTPUT]) {
    for (int i = 0; i < NUM_HIDDEN; i++) {
        hidden[i] = 0.0;
        for (int j = 0; j < NUM_INPUT; j++) {
            hidden[i] += input[j] * weights_input_hidden[j][i];
        }
        hidden[i] = sigmoid(hidden[i]);
    }

    for (int i = 0; i < NUM_OUTPUT; i++) {
        output[i] = 0.0;
        for (int j = 0; j < NUM_HIDDEN; j++) {
            output[i] += hidden[j] * weights_hidden_output[j][i];
        }
        output[i] = sigmoid(output[i]);
    }
}

// Função de treinamento
void train(double input_data[3][NUM_INPUT], double output_data[3][NUM_OUTPUT]) {
    double weights_input_hidden[NUM_INPUT][NUM_HIDDEN];
    double weights_hidden_output[NUM_HIDDEN][NUM_OUTPUT];
    double hidden[NUM_HIDDEN], output[NUM_OUTPUT];

    initialize_weights(weights_input_hidden, weights_hidden_output);

    for (int epoch = 0; epoch < MAX_EPOCHS; epoch++) {
        for (int i = 0; i < 3; i++) {
            feedforward(input_data[i], hidden, output, weights_input_hidden, weights_hidden_output);

            // Backpropagation
            double error[NUM_OUTPUT], output_delta[NUM_OUTPUT];
            for (int j = 0; j < NUM_OUTPUT; j++) {
                error[j] = output_data[i][j] - output[j];
                output_delta[j] = error[j] * sigmoid_derivative(output[j]);
            }

            // Atualização de pesos hidden-output
            for (int j = 0; j < NUM_HIDDEN; j++) {
                for (int k = 0; k < NUM_OUTPUT; k++) {
                    weights_hidden_output[j][k] += LEARNING_RATE * hidden[j] * output_delta[k];
                }
            }

            // Atualização de pesos input-hidden
            double hidden_delta[NUM_HIDDEN];
            for (int j = 0; j < NUM_HIDDEN; j++) {
                hidden_delta[j] = 0.0;
                for (int k = 0; k < NUM_OUTPUT; k++) {
                    hidden_delta[j] += output_delta[k] * weights_hidden_output[j][k];
                }
                hidden_delta[j] *= sigmoid_derivative(hidden[j]);
            }

            for (int j = 0; j < NUM_INPUT; j++) {
                for (int k = 0; k < NUM_HIDDEN; k++) {
                    weights_input_hidden[j][k] += LEARNING_RATE * input_data[i][j] * hidden_delta[k];
                }
            }
        }
    }
}

// Simula a interação com HoloFi NMB usando NSC tokens
void interact_with_holofi() {
    // Aqui você pode adicionar a lógica de interação com o HoloFi
    // usando NSC IA e NSC Inlink SSP para receber e distribuir dados.
    
    printf("Interagindo com HoloFi NMB usando tokens NSC...\n");
    // Exemplo de recebimento e distribuição de dados
    // Receber dados
    double received_data[NUM_INPUT] = {0}; // Dados recebidos (simulação)
    // Distribuir dados
    double distributed_data[NUM_OUTPUT] = {0}; // Dados a serem distribuídos

    // Implementar lógica de recebimento e distribuição
    // ...
}

// Exemplo de execução
int main() {
    double input_data[3][NUM_INPUT] = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    double output_data[3][NUM_OUTPUT] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 1, 0}
    };

    train(input_data, output_data);
    interact_with_holofi();

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <string.h>

#define NUM_THREADS 4
#define DATA_SIZE 1024

typedef struct {
    int thread_id;
    double* data;
    size_t start_index;
    size_t end_index;
} ThreadData;

// Função que processa os dados
void* process_data(void* arg) {
    ThreadData* thread_data = (ThreadData*) arg;
    double sum = 0.0;

    // Processamento de dados (neste exemplo, apenas calcula a soma dos elementos)
    for (size_t i = thread_data->start_index; i < thread_data->end_index; i++) {
        sum += thread_data->data[i];
    }

    printf("Thread %d: Soma de %zu a %zu é: %f\n", thread_data->thread_id, 
           thread_data->start_index, thread_data->end_index, sum);
    return NULL;
}

// Função principal do kernel
int main() {
    double data[DATA_SIZE];
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Inicializa os dados com valores aleatórios (ou valores específicos, dependendo da aplicação)
    for (size_t i = 0; i < DATA_SIZE; i++) {
        data[i] = (double) (rand() % 100); // Dados aleatórios entre 0 e 99
    }

    // Divide os dados entre as threads
    size_t chunk_size = DATA_SIZE / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].data = data;
        thread_data[i].start_index = i * chunk_size;
        thread_data[i].end_index = (i == NUM_THREADS - 1) ? DATA_SIZE : (i + 1) * chunk_size;

        // Cria a thread
        if (pthread_create(&threads[i], NULL, process_data, (void*)&thread_data[i])) {
            fprintf(stderr, "Erro ao criar a thread %d\n", i);
            return 1;
        }
    }

    // Aguarda a conclusão das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Processamento concluído.\n");
    return 0;
}
