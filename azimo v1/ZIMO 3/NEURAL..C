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

    return 0;
}
