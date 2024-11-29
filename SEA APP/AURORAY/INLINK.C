#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definições de parâmetros do Holo7
#define NUM_INPUT 10
#define NUM_HIDDEN 20
#define NUM_OUTPUT 3
#define MAX_EPOCHS 1000
#define LEARNING_RATE 0.01

// Função Holo7 Sigmoid (com suporte para operações em larga escala)
double holo7_sigmoid(double x) {
    // Ajuste para simular eficiência em Holo7
    return 1.0 / (1.0 + exp(-x));
}

// Derivada da função Sigmoid no Holo7
double holo7_sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

// Inicializa pesos aleatórios otimizados para Holo7
void holo7_initialize_weights(double weights_input_hidden[NUM_INPUT][NUM_HIDDEN], double weights_hidden_output[NUM_HIDDEN][NUM_OUTPUT]) {
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

// Função Feedforward do Holo7
void holo7_feedforward(double input[NUM_INPUT], double hidden[NUM_HIDDEN], double output[NUM_OUTPUT], 
                       double weights_input_hidden[NUM_INPUT][NUM_HIDDEN], double weights_hidden_output[NUM_HIDDEN][NUM_OUTPUT]) {
    // Camada oculta
    for (int i = 0; i < NUM_HIDDEN; i++) {
        hidden[i] = 0.0;
        for (int j = 0; j < NUM_INPUT; j++) {
            hidden[i] += input[j] * weights_input_hidden[j][i];
        }
        hidden[i] = holo7_sigmoid(hidden[i]);  // Ativação Holo7 Sigmoid
    }

    // Camada de saída
    for (int i = 0; i < NUM_OUTPUT; i++) {
        output[i] = 0.0;
        for (int j = 0; j < NUM_HIDDEN; j++) {
            output[i] += hidden[j] * weights_hidden_output[j][i];
        }
        output[i] = holo7_sigmoid(output[i]);  // Ativação Holo7 Sigmoid
    }
}

// Treinamento adaptado para Holo7 com backpropagation otimizado
void holo7_train(double input_data[3][NUM_INPUT], double output_data[3][NUM_OUTPUT]) {
    double weights_input_hidden[NUM_INPUT][NUM_HIDDEN];
    double weights_hidden_output[NUM_HIDDEN][NUM_OUTPUT];
    double hidden[NUM_HIDDEN], output[NUM_OUTPUT];

    holo7_initialize_weights(weights_input_hidden, weights_hidden_output);

    for (int epoch = 0; epoch < MAX_EPOCHS; epoch++) {
        for (int i = 0; i < 3; i++) {
            holo7_feedforward(input_data[i], hidden, output, weights_input_hidden, weights_hidden_output);

            // Backpropagation otimizado Holo7
            double error[NUM_OUTPUT], output_delta[NUM_OUTPUT];
            for (int j = 0; j < NUM_OUTPUT; j++) {
                error[j] = output_data[i][j] - output[j];
                output_delta[j] = error[j] * holo7_sigmoid_derivative(output[j]);
            }

            // Atualização de pesos (hidden-output) em Holo7
            for (int j = 0; j < NUM_HIDDEN; j++) {
                for (int k = 0; k < NUM_OUTPUT; k++) {
                    weights_hidden_output[j][k] += LEARNING_RATE * hidden[j] * output_delta[k];
                }
            }

            // Atualização de pesos (input-hidden) em Holo7
            double hidden_delta[NUM_HIDDEN];
            for (int j = 0; j < NUM_HIDDEN; j++) {
                hidden_delta[j] = 0.0;
                for (int k = 0; k < NUM_OUTPUT; k++) {
                    hidden_delta[j] += output_delta[k] * weights_hidden_output[j][k];
                }
                hidden_delta[j] *= holo7_sigmoid_derivative(hidden[j]);
            }

            for (int j = 0; j < NUM_INPUT; j++) {
                for (int k = 0; k < NUM_HIDDEN; k++) {
                    weights_input_hidden[j][k] += LEARNING_RATE * input_data[i][j] * hidden_delta[k];
                }
            }
        }
    }
}

// Função Main - Holo7 NSC Inlink
int main() {
    // Dados de entrada (exemplo fictício para o Holo7)
    double input_data[3][NUM_INPUT] = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    // Dados de saída multi-label (Holo7 Output)
    double output_data[3][NUM_OUTPUT] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 1, 0}
    };

    // Treina a rede neural Holo7 com os dados de entrada e saída
    holo7_train(input_data, output_data);

    // Previsão para um novo dado no Holo7
    double new_input[NUM_INPUT] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double hidden[NUM_HIDDEN], output[NUM_OUTPUT];

    // Realiza a previsão com os pesos treinados
    holo7_feedforward(new_input, hidden, output, weights_input_hidden, weights_hidden_output);

    // Exibe a previsão Holo7
    printf("Previsão Holo7 para novo dado: ");
    for (int i = 0; i < NUM_OUTPUT; i++) {
        printf("%.2f ", output[i]);
    }
    printf("\n");

    return 0;
}
