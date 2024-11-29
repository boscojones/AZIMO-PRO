#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#define DB_NAME "investments.db"
#define CSV_FILE "investors_data.csv"
#define MAX_LINE_LENGTH 256
#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 100
#define MAX_PHONE_LENGTH 20

// Prototipos de funções
void initializeDatabase();
void readCSVData(const char *filePath);
void insertInvestor(const char *name, const char *email, const char *phone);
int executeSQL(const char *sql);
int openDatabase(sqlite3 **db);
void closeDatabase(sqlite3 *db);

int main() {
    initializeDatabase();
    readCSVData(CSV_FILE);
    return 0;
}

// Função para inicializar o banco de dados e criar as tabelas necessárias
void initializeDatabase() {
    const char *createInvestorsTable = 
        "CREATE TABLE IF NOT EXISTS Investors ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "email TEXT NOT NULL, "
        "phone_number TEXT NOT NULL);";

    const char *createAssetsTable = 
        "CREATE TABLE IF NOT EXISTS Assets ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "asset_name TEXT NOT NULL, "
        "asset_type TEXT NOT NULL, "
        "total_slots INTEGER NOT NULL, "
        "annual_return REAL NOT NULL);";

    const char *createInvestmentsTable = 
        "CREATE TABLE IF NOT EXISTS Investments ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "investor_id INTEGER, "
        "asset_id INTEGER, "
        "invested_amount REAL, "
        "FOREIGN KEY(investor_id) REFERENCES Investors(id), "
        "FOREIGN KEY(asset_id) REFERENCES Assets(id));";

    // Executa as consultas SQL
    executeSQL(createInvestorsTable);
    executeSQL(createAssetsTable);
    executeSQL(createInvestmentsTable);
}

// Função para abrir o banco de dados
int openDatabase(sqlite3 **db) {
    int rc = sqlite3_open(DB_NAME, db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(*db));
        return rc;
    }
    return SQLITE_OK;
}

// Função para fechar o banco de dados
void closeDatabase(sqlite3 *db) {
    sqlite3_close(db);
}

// Função para executar comandos SQL
int executeSQL(const char *sql) {
    sqlite3 *db;
    char *errorMessage = 0;

    if (openDatabase(&db) != SQLITE_OK) {
        return 1;
    }

    // Executa a consulta SQL
    int rc = sqlite3_exec(db, sql, 0, 0, &errorMessage);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro de SQL: %s\n", errorMessage);
        sqlite3_free(errorMessage);
    } else {
        printf("SQL executado com sucesso: %s\n", sql);
    }

    // Fecha o banco de dados
    closeDatabase(db);
    return rc;
}

// Função para ler dados de um arquivo CSV e inserir no banco de dados
void readCSVData(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("Não foi possível abrir o arquivo");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char name[MAX_NAME_LENGTH], email[MAX_EMAIL_LENGTH], phone[MAX_PHONE_LENGTH];
        // Usa sscanf para analisar a linha do CSV
        if (sscanf(line, "%99[^,],%99[^,],%19[^\n]", name, email, phone) == 3) {
            printf("Nome: %s, Email: %s, Telefone: %s\n", name, email, phone);
            insertInvestor(name, email, phone); // Insere os dados no banco de dados
        } else {
            fprintf(stderr, "Linha inválida no CSV: %s\n", line);
        }
    }

    fclose(file);
}

// Função para inserir dados de investidores no banco de dados
void insertInvestor(const char *name, const char *email, const char *phone) {
    sqlite3 *db;
    sqlite3_stmt *stmt;

    if (openDatabase(&db) != SQLITE_OK) {
        return;
    }

    const char *insertInvestorSQL = "INSERT INTO Investors (name, email, phone_number) VALUES (?, ?, ?)";
    
    // Prepara a consulta SQL
    int rc = sqlite3_prepare_v2(db, insertInvestorSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Falha ao preparar a instrução: %s\n", sqlite3_errmsg(db));
    } else {
        // Associa os valores
        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, phone, -1, SQLITE_STATIC);

        // Executa a instrução
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Falha na execução: %s\n", sqlite3_errmsg(db));
        } else {
            printf("Investidor inserido com sucesso: %s\n", name);
        }
    }

    // Finaliza e fecha a instrução e o banco de dados
    sqlite3_finalize(stmt);
    closeDatabase(db);
}
