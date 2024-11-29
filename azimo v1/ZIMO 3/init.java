// Definição da classe NSCABC
class NSCABC {
    // Atributos para o nome do modelo e versão
    private String modelName;
    private String version;

    // Método para inicializar o modelo
    public void initNSCABC(String name, String ver) {
        this.modelName = name;
        this.version = ver;
    }

    // Método para gerar saída baseada em uma string de entrada
    public void generateOutput(String input) {
        System.out.println("Generated output based on: " + input);
    }

    // Método para exibir o diálogo com o modelo
    public void dialog() {
        System.out.println("Dialog with NSC_ABC model " + this.modelName + " version " + this.version);
    }
}

// Classe principal com o método main
public class Main {
    public static void main(String[] args) {
        // Inicializando o modelo NSC_ABC
        NSCABC nscModel = new NSCABC();
        nscModel.initNSCABC("NSC-ABC", "1.0");

        // Exibindo o diálogo
        nscModel.dialog();

        // Gerando saída
        nscModel.generateOutput("Teste de entrada");
    }
}
