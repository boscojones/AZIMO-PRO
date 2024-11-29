import 'dart:math';

final int numInput = 10;
final int numHidden = 20;
final int numOutput = 3;
final int maxEpochs = 1000;
final double learningRate = 0.01;

// Função Sigmoid
double sigmoid(double x) {
  return 1.0 / (1.0 + exp(-x));
}

// Derivada da função Sigmoid
double sigmoidDerivative(double x) {
  return x * (1.0 - x);
}

// Inicializa pesos aleatórios
List<List<double>> initializeWeights(int rows, int cols) {
  Random random = Random();
  List<List<double>> weights = List.generate(rows, (i) => List.generate(cols, (j) => random.nextDouble() * 2 - 1));
  return weights;
}

// Feedforward
void feedforward(List<double> input, List<double> hidden, List<double> output, List<List<double>> weightsInputHidden, List<List<double>> weightsHiddenOutput) {
  for (int i = 0; i < numHidden; i++) {
    hidden[i] = 0.0;
    for (int j = 0; j < numInput; j++) {
      hidden[i] += input[j] * weightsInputHidden[j][i];
    }
    hidden[i] = sigmoid(hidden[i]);
  }

  for (int i = 0; i < numOutput; i++) {
    output[i] = 0.0;
    for (int j = 0; j < numHidden; j++) {
      output[i] += hidden[j] * weightsHiddenOutput[j][i];
    }
    output[i] = sigmoid(output[i]);
  }
}

// Função de treinamento
void train(List<List<double>> inputData, List<List<double>> outputData) {
  var weightsInputHidden = initializeWeights(numInput, numHidden);
  var weightsHiddenOutput = initializeWeights(numHidden, numOutput);
  List<double> hidden = List.filled(numHidden, 0.0);
  List<double> output = List.filled(numOutput, 0.0);

  for (int epoch = 0; epoch < maxEpochs; epoch++) {
    for (int i = 0; i < inputData.length; i++) {
      feedforward(inputData[i], hidden, output, weightsInputHidden, weightsHiddenOutput);

      // Backpropagation
      List<double> error = List.filled(numOutput, 0.0);
      List<double> outputDelta = List.filled(numOutput, 0.0);

      // Calculando o erro e delta para a saída
      for (int j = 0; j < numOutput; j++) {
        error[j] = outputData[i][j] - output[j];
        outputDelta[j] = error[j] * sigmoidDerivative(output[j]);
      }

      // Atualização de pesos hidden-output
      for (int j = 0; j < numHidden; j++) {
        for (int k = 0; k < numOutput; k++) {
          weightsHiddenOutput[j][k] += learningRate * hidden[j] * outputDelta[k];
        }
      }

      // Calculando o delta para as camadas ocultas
      List<double> hiddenDelta = List.filled(numHidden, 0.0);
      for (int j = 0; j < numHidden; j++) {
        hiddenDelta[j] = 0.0;
        for (int k = 0; k < numOutput; k++) {
          hiddenDelta[j] += outputDelta[k] * weightsHiddenOutput[j][k];
        }
        hiddenDelta[j] *= sigmoidDerivative(hidden[j]);
      }

      // Atualização de pesos input-hidden
      for (int j = 0; j < numInput; j++) {
        for (int k = 0; k < numHidden; k++) {
          weightsInputHidden[j][k] += learningRate * inputData[i][j] * hiddenDelta[k];
        }
      }
    }
  }
}

// Simulação de execução
void main() {
  var inputData = [
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
    [1, 1, 0, 0, 0, 0, 0, 0, 0, 0]
  ];

  var outputData = [
    [1, 0, 1],
    [0, 1, 0],
    [1, 1, 0]
  ];

  train(inputData, outputData);
  print("Treinamento concluído.");
}
