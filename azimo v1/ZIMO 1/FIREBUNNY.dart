// Importando bibliotecas necessárias
import 'dart:async';

// Definição das funções principais para simular a geração de respostas
void main() async {
  // Parâmetros para a geração
  String ckptDir = "caminho/para/ckpt"; // Defina o caminho correto
  String tokenizerPath = "caminho/para/tokenizer"; // Defina o caminho correto
  double temperature = 0.6;
  double topP = 0.9;
  int maxSeqLen = 512;
  int maxBatchSize = 4;
  int? maxGenLen = null;

  // Executar a geração com múltiplos kernels
  await multiKernelSSP(
    ckptDir,
    tokenizerPath,
    temperature,
    topP,
    maxSeqLen,
    maxBatchSize,
    maxGenLen,
  );
}

// Função que simula o processamento de múltiplos kernels para geração de resposta
Future<void> multiKernelSSP(
  String ckptDir,
  String tokenizerPath,
  double temperature,
  double topP,
  int maxSeqLen,
  int maxBatchSize,
  int? maxGenLen,
) async {
  // Simulação de interações do usuário e do assistente
  List<Dialog> dialogs = [
    Dialog('user', 'qual é a receita de maionese?'),
    Dialog('user', 'Estou indo para Paris, o que devo ver?'),
    Dialog('assistant', 'Paris, a capital da França, é conhecida por sua arquitetura deslumbrante...'),
    Dialog('user', 'O que é tão especial no #1?'),
  ];

  // Iniciar múltiplos kernels para geração de respostas simultâneas (simulação de multi-tarefas)
  List<Future<void>> kernelTasks = dialogs.map((dialog) async {
    await simulateResponse(dialog);
  }).toList();

  // Esperar todas as respostas serem geradas
  await Future.wait(kernelTasks);

  print("> assistant: A Torre Eiffel é um ícone que representa Paris, oferecendo vistas incríveis da cidade.\n");
}

// Função que simula o processamento e geração de uma resposta
Future<void> simulateResponse(Dialog dialog) async {
  await Future.delayed(Duration(seconds: 1)); // Simula o tempo de processamento
  print("${dialog.role}: ${dialog.content}");
}

// Classe para representar um diálogo
class Dialog {
  String role;
  String content;

  Dialog(this.role, this.content);
}
