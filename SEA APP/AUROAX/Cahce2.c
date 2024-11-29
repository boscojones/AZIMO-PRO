#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Constants
#define NUM_INPUT 10
#define NUM_HIDDEN 20
#define NUM_OUTPUT 1
#define MAX_EPOCHS 1000
#define ERROR_THRESHOLD 0.01

// Structure for Neural Network
typedef struct {
    double weightsInputHidden[NUM_INPUT][NUM_HIDDEN];
    double weightsHiddenOutput[NUM_HIDDEN][NUM_OUTPUT];
    double hiddenLayer[NUM_HIDDEN];
    double outputLayer[NUM_OUTPUT];
    double learningRate;
} NeuralNetwork;

// Sigmoid function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Derivative of sigmoid function
double sigmoidDerivative(double x) {
    return x * (1.0 - x);
}

// Initialize weights randomly
void initializeNetwork(NeuralNetwork *nn) {
    srand(time(NULL)); // Seed for randomness
    for (int i = 0; i < NUM_INPUT; i++) {
        for (int j = 0; j < NUM_HIDDEN; j++) {
            nn->weightsInputHidden[i][j] = ((double)rand() / RAND_MAX) * 2 - 1; // Random values between -1 and 1
        }
    }
    for (int j = 0; j < NUM_HIDDEN; j++) {
        for (int k = 0; k < NUM_OUTPUT; k++) {
            nn->weightsHiddenOutput[j][k] = ((double)rand() / RAND_MAX) * 2 - 1; // Random values between -1 and 1
        }
    }
}

// Training function
void train(NeuralNetwork *nn, double input[][NUM_INPUT], double output[][NUM_OUTPUT], int numSamples) {
    for (int epoch = 0; epoch < MAX_EPOCHS; epoch++) {
        double totalError = 0.0;
        for (int s = 0; s < numSamples; s++) {
            // Feedforward
            for (int j = 0; j < NUM_HIDDEN; j++) {
                double activation = 0.0;
                for (int i = 0; i < NUM_INPUT; i++) {
                    activation += input[s][i] * nn->weightsInputHidden[i][j];
                }
                nn->hiddenLayer[j] = sigmoid(activation);
            }

            for (int k = 0; k < NUM_OUTPUT; k++) {
                double activation = 0.0;
                for (int j = 0; j < NUM_HIDDEN; j++) {
                    activation += nn->hiddenLayer[j] * nn->weightsHiddenOutput[j][k];
                }
                nn->outputLayer[k] = sigmoid(activation);
            }

            // Calculate error
            double error = output[s][0] - nn->outputLayer[0];
            totalError += error * error;

            // Backpropagation
            double outputDelta = error * sigmoidDerivative(nn->outputLayer[0]);
            for (int j = 0; j < NUM_HIDDEN; j++) {
                nn->weightsHiddenOutput[j][0] += nn->learningRate * outputDelta * nn->hiddenLayer[j];
            }

            for (int j = 0; j < NUM_HIDDEN; j++) {
                double hiddenDelta = outputDelta * nn->weightsHiddenOutput[j][0] * sigmoidDerivative(nn->hiddenLayer[j]);
                for (int i = 0; i < NUM_INPUT; i++) {
                    nn->weightsInputHidden[i][j] += nn->learningRate * hiddenDelta * input[s][i];
                }
            }
        }

        totalError /= numSamples;
        if (totalError < ERROR_THRESHOLD) {
            printf("Training stopped early at epoch %d\n", epoch);
            break;
        }
    }
}

// Prediction function
void predict(NeuralNetwork *nn, double input[]) {
    for (int j = 0; j < NUM_HIDDEN; j++) {
        double activation = 0.0;
        for (int i = 0; i < NUM_INPUT; i++) {
            activation += input[i] * nn->weightsInputHidden[i][j];
        }
        nn->hiddenLayer[j] = sigmoid(activation);
    }

    for (int k = 0; k < NUM_OUTPUT; k++) {
        double activation = 0.0;
        for (int j = 0; j < NUM_HIDDEN; j++) {
            activation += nn->hiddenLayer[j] * nn->weightsHiddenOutput[j][k];
        }
        nn->outputLayer[k] = sigmoid(activation);
    }

    printf("Prediction: %f\n", nn->outputLayer[0]);
}

// Example usage
int main() {
    NeuralNetwork nn;
    nn.learningRate = 0.01;

    initializeNetwork(&nn);

    // Sample training data
    double inputData[2][NUM_INPUT] = {
        {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
    };
    double outputData[2][NUM_OUTPUT] = {
        {1.0},
        {1.0}
    };

    // Training the neural network
    train(&nn, inputData, outputData, 2);

    // Making a prediction
    double newInput[NUM_INPUT] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    predict(&nn, newInput);

    return 0;
}
