import Foundation

let compileCommand = "gcc"  // Comando de compilação
let outputName = "output_program"  // Nome do programa final
let terminalCommand = "./"  // Comando para executar o programa

// Função para compilar todos os arquivos .c no diretório atual
func compileAllCFiles() {
    var compileCmd = "\(compileCommand) -o \(outputName) "  // Buffer para o comando de compilação

    // Obter o diretório atual
    let fileManager = FileManager.default
    do {
        let currentPath = fileManager.currentDirectoryPath
        let items = try fileManager.contentsOfDirectory(atPath: currentPath)

        // Listar todos os arquivos no diretório
        for item in items {
            // Verificar arquivos .c
            if item.hasSuffix(".c") {
                compileCmd += "\(item) "
            }
        }

        // Verificar se há arquivos para compilar
        if compileCmd == "\(compileCommand) -o \(outputName) " {
            print("Nenhum arquivo .c encontrado para compilar.")
            return
        }

        // Executar o comando de compilação
        print("Compilando com o comando: \(compileCmd)")
        let compileResult = system(compileCmd)

        if compileResult != 0 {
            print("Falha na compilação.")
            return
        }

        print("Compilação bem-sucedida!")
    } catch {
        print("Erro ao acessar o diretório: \(error)")
    }
}

// Função para executar o programa compilado
func runProgram() {
    let runCmd = "\(terminalCommand)\(outputName)"
    
    // Executar o programa
    print("Executando o programa: \(runCmd)")
    let runResult = system(runCmd)

    if runResult != 0 {
        print("Falha na execução do programa.")
    } else {
        print("Programa executado com sucesso.")
    }
}

// Função principal
func main() {
    compileAllCFiles()  // Compilar todos os arquivos .c
    runProgram()        // Executar o programa compilado
}

// Chamar a função principal
main()
