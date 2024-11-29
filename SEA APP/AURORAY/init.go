package main

import (
	"fmt"
)

// Definição da estrutura NSCABC
type NSCABC struct {
	ModelName string
	Version   string
}

// Função para gerar saída baseada em uma string de entrada
func generate(model NSCABC, input string) {
	output := fmt.Sprintf("Generated output based on: %s", input)
	fmt.Println(output)
}

// Função para exibir o diálogo com o modelo
func dialog(model NSCABC) {
	fmt.Printf("Dialog with NSC_ABC model %s version %s\n", model.ModelName, model.Version)
}

// Função para inicializar o modelo NSC_ABC
func createNSCABC(modelName string, version string) NSCABC {
	return NSCABC{
		ModelName: modelName,
		Version:   version,
	}
}

// Função principal
func main() {
	// Inicializando o modelo NSC_ABC
	nscModel := createNSCABC("NSC-ABC", "1.0")

	// Exibindo o diálogo
	dialog(nscModel)

	// Gerando saída
	generate(nscModel, "Teste de entrada")
}
