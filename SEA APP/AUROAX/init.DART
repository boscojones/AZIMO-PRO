// Definição da classe NSCABC
class NSCABC {
  final String modelName;
  final String version;

  // Construtor para inicializar o modelo
  NSCABC(this.modelName, this.version);

  // Método para gerar saída baseada em uma string de entrada
  void generate(String input) {
    String output = 'Generated output based on: $input';
    print(output);
  }

  // Método para exibir o diálogo com o modelo
  void dialog() {
    print('Dialog with NSC_ABC model $modelName version $version');
  }
}

// Método principal para executar o código
void main() {
  // Inicializando o modelo NSC_ABC
  NSCABC nscModel = NSCABC('NSC-ABC', '1.0');

  // Exibindo o diálogo
  nscModel.dialog();

  // Gerando saída
  nscModel.generate('Teste de entrada');
}
