#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    sqlite3 *db;
} InvestmentManager;

// Inicializa o banco de dados
int initializeDatabase(InvestmentManager *manager) {
    const char *dbName = "investments.db";
    int rc = sqlite3_open(dbName, &(manager->db));

    if (rc) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(manager->db));
        return rc;
    }
    
    return 0;
}

// Cria as tabelas no banco de dados
void createTables(InvestmentManager *manager) {
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

    char *errMsg = 0;

    // Executa cada comando de criação de tabela
    if (sqlite3_exec(manager->db, createInvestorsTable, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela Investors: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    if (sqlite3_exec(manager->db, createAssetsTable, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela Assets: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    if (sqlite3_exec(manager->db, createInvestmentsTable, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela Investments: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

// Insere um novo investidor no banco de dados
void insertInvestor(InvestmentManager *manager, const char *name, const char *email, const char *phone_number) {
    const char *insertSQL = "INSERT INTO Investors (name, email, phone_number) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(manager->db, insertSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, phone_number, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Erro ao inserir investidor: %s\n", sqlite3_errmsg(manager->db));
        } else {
            printf("Investidor inserido com sucesso: %s\n", name);
        }
    } else {
        fprintf(stderr, "Erro ao preparar SQL: %s\n", sqlite3_errmsg(manager->db));
    }

    sqlite3_finalize(stmt);
}

// Insere um novo ativo no banco de dados
void insertAsset(InvestmentManager *manager, const char *assetName, const char *assetType, int totalSlots, double annualReturn) {
    const char *insertSQL = "INSERT INTO Assets (asset_name, asset_type, total_slots, annual_return) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(manager->db, insertSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, assetName, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, assetType, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, totalSlots);
        sqlite3_bind_double(stmt, 4, annualReturn);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Erro ao inserir ativo: %s\n", sqlite3_errmsg(manager->db));
        } else {
            printf("Ativo inserido com sucesso: %s\n", assetName);
        }
    } else {
        fprintf(stderr, "Erro ao preparar SQL: %s\n", sqlite3_errmsg(manager->db));
    }

    sqlite3_finalize(stmt);
}

// Insere um novo investimento no banco de dados
void insertInvestment(InvestmentManager *manager, int investor_id, int asset_id, double invested_amount) {
    const char *insertSQL = "INSERT INTO Investments (investor_id, asset_id, invested_amount) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(manager->db, insertSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, investor_id);
        sqlite3_bind_int(stmt, 2, asset_id);
        sqlite3_bind_double(stmt, 3, invested_amount);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Erro ao inserir investimento: %s\n", sqlite3_errmsg(manager->db));
        } else {
            printf("Investimento inserido com sucesso: Investidor ID %d, Ativo ID %d, Valor Investido %.2f\n", investor_id, asset_id, invested_amount);
        }
    } else {
        fprintf(stderr, "Erro ao preparar SQL: %s\n", sqlite3_errmsg(manager->db));
    }

    sqlite3_finalize(stmt);
}

// Fecha a conexão com o banco de dados
void closeConnection(InvestmentManager *manager) {
    sqlite3_close(manager->db);
    printf("Conexão com o banco de dados fechada.\n");
}

int main() {
    InvestmentManager investmentManager;

    if (initializeDatabase(&investmentManager) == 0) {
        createTables(&investmentManager);
        
        // Exemplo de inserções
        insertInvestor(&investmentManager, "Lucas Nascimento", "lucas@example.com", "+55 11 91234-5678");
        insertAsset(&investmentManager, "Ação XYZ", "Ação", 100, 12.0);
        insertInvestment(&investmentManager, 1, 1, 1000.00); // ID do investidor e ID do ativo
    }

    closeConnection(&investmentManager);
    return 0;
}
