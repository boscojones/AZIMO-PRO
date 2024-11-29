#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    sqlite3 *db;
    const char *db_name;
} InvestmentManager;

// Function prototypes
void initialize_database(InvestmentManager *manager);
void create_tables(InvestmentManager *manager);
void execute_sql(InvestmentManager *manager, const char *sql);
void initialize_assets(InvestmentManager *manager);
void insert_asset(InvestmentManager *manager, const char *asset_name, const char *asset_type, int total_slots, double annual_return);
void close_database(InvestmentManager *manager);

int main() {
    InvestmentManager manager;
    manager.db_name = "investments.db";

    // Initialize the database
    initialize_database(&manager);

    // Close the database connection on exit
    atexit(() => close_database(&manager));
    return 0;
}

void initialize_database(InvestmentManager *manager) {
    int rc = sqlite3_open(manager->db_name, &manager->db);
    if (rc) {
        fprintf(stderr, "Error opening database: %s\n", sqlite3_errmsg(manager->db));
        exit(EXIT_FAILURE);
    }
    printf("Connected to database: %s\n", manager->db_name);
    
    // Create tables
    create_tables(manager);
    // Initialize assets
    initialize_assets(manager);
}

void create_tables(InvestmentManager *manager) {
    const char *queries[] = {
        "CREATE TABLE IF NOT EXISTS Investors (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, email TEXT NOT NULL, phone_number TEXT NOT NULL);",
        "CREATE TABLE IF NOT EXISTS Assets (id INTEGER PRIMARY KEY AUTOINCREMENT, asset_name TEXT NOT NULL, asset_type TEXT NOT NULL, total_slots INTEGER NOT NULL, annual_return REAL NOT NULL);",
        "CREATE TABLE IF NOT EXISTS Investments (id INTEGER PRIMARY KEY AUTOINCREMENT, investor_id INTEGER, asset_id INTEGER, invested_amount REAL, FOREIGN KEY(investor_id) REFERENCES Investors(id), FOREIGN KEY(asset_id) REFERENCES Assets(id));"
    };
    
    for (int i = 0; i < sizeof(queries) / sizeof(queries[0]); i++) {
        execute_sql(manager, queries[i]);
    }
}

void execute_sql(InvestmentManager *manager, const char *sql) {
    char *err_msg = 0;
    int rc = sqlite3_exec(manager->db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("SQL executed successfully: %s\n", sql);
    }
}

void initialize_assets(InvestmentManager *manager) {
    insert_asset(manager, "Ação XYZ", "Ação", 100, 12.0);
    insert_asset(manager, "Fundo Imobiliário ABC", "Fundo", 50, 8.0);
}

void insert_asset(InvestmentManager *manager, const char *asset_name, const char *asset_type, int total_slots, double annual_return) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO Assets (asset_name, asset_type, total_slots, annual_return) VALUES ('%s', '%s', %d, %f);", asset_name, asset_type, total_slots, annual_return);
    
    execute_sql(manager, sql);
    printf("Asset inserted successfully: %s\n", asset_name);
}

void close_database(InvestmentManager *manager) {
    if (manager->db) {
        sqlite3_close(manager->db);
        printf("Database connection closed: %s\n", manager->db_name);
    }
}
