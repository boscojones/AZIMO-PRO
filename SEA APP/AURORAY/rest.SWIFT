dependencies: [
    .package(url: "https://github.com/Kitura/PostgresClientKit.git", from: "1.0.0")
]
import Foundation
import PostgresClientKit

// Estrutura para representar uma planilha
struct Planilha {
    let id: Int
    let nome: String
    let dataCriacao: Date
    let dados: String  // Armazena os dados em formato JSON
}

// Classe para gerenciar chamadas ao Data Lake
class DataLakeKernel {
    private var connection: Connection
    
    init(host: String, port: Int, database: String, username: String, password: String) {
        let connectionString = "host=\(host) port=\(port) dbname=\(database) user=\(username) password=\(password)"
        self.connection = Connection(connectionString: connectionString)
    }
    
    // Função para abrir a conexão
    func openConnection() throws {
        try connection.open()
    }
    
    // Função para fechar a conexão
    func closeConnection() {
        connection.close()
    }
    
    // Função para recuperar todas as planilhas
    func getAllPlanilhas() throws -> [Planilha] {
        var planilhas: [Planilha] = []
        
        let query = "SELECT * FROM planilhas ORDER BY data_criacao DESC;"
        
        let statement = try connection.prepareStatement(text: query)
        let cursor = try statement.execute()
        
        for row in cursor {
            let id = try row.get("id") as Int
            let nome = try row.get("nome") as String
            let dataCriacao = try row.get("data_criacao") as Date
            let dados = try row.get("dados") as String
            
            let planilha = Planilha(id: id, nome: nome, dataCriacao: dataCriacao, dados: dados)
            planilhas.append(planilha)
        }
        
        return planilhas
    }
    
    // Função para buscar uma planilha pelo nome
    func getPlanilhaByName(nome: String) throws -> Planilha? {
        let query = "SELECT * FROM planilhas WHERE nome = $1;"
        let statement = try connection.prepareStatement(text: query)
        let cursor = try statement.execute(parameter: nome)
        
        if let row = cursor.first {
            let id = try row.get("id") as Int
            let nome = try row.get("nome") as String
            let dataCriacao = try row.get("data_criacao") as Date
            let dados = try row.get("dados") as String
            
            return Planilha(id: id, nome: nome, dataCriacao: dataCriacao, dados: dados)
        }
        
        return nil
    }
}

// Exemplo de uso
do {
    let dataLake = DataLakeKernel(host: "localhost", port: 5432, database: "seu_banco", username: "seu_usuario", password: "sua_senha")
    
    try dataLake.openConnection()
    
    let planilhas = try dataLake.getAllPlanilhas()
    for planilha in planilhas {
        print("Planilha: \(planilha.nome), Criada em: \(planilha.dataCriacao)")
    }
    
    if let vendasPlanilha = try dataLake.getPlanilhaByName(nome: "Vendas Q1") {
        print("Planilha encontrada: \(vendasPlanilha.nome)")
    } else {
        print("Planilha não encontrada.")
    }
    
    dataLake.closeConnection()
} catch {
    print("Erro: \(error)")
}
