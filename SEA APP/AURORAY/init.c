#include <stdio.h>
#include <string.h>

// Definição da estrutura NSCABC
typedef struct {
    char modelName[20];
    char version[10];
} NSCABC;

// Função para inicializar o modelo
void initNSCABC(NSCABC *model, const char *name, const char *ver) {
    strcpy(model->modelName, name);
    strcpy(model->version, ver);
}

// Função para gerar saída baseada em uma string de entrada
void generateOutput(const char *input) {
    printf("Generated output based on: %s\n", input);
}

// Função para exibir o diálogo com o modelo
void dialog(const NSCABC *model) {
    printf("Dialog with NSC_ABC model %s version %s\n", model->modelName, model->version);
}

// Função principal
int main() {
    // Inicializando o modelo NSC_ABC
    NSCABC nscModel;
    initNSCABC(&nscModel, "NSC-ABC", "1.0");

    // Exibindo o diálogo
    dialog(&nscModel);

    // Gerando saída
    generateOutput("Teste de entrada");

    return 0;
}
