#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 255

// Função para compilar todos os arquivos .c no diretório atual
void compile_all_c_files() {
    char command[512];
    snprintf(command, sizeof(command), "gcc -o output_program ");

    // Obter o diretório atual
    FILE *fp;
    char path[MAX_FILENAME_LENGTH];

    // Lista de arquivos .c
    int file_count = 0;
    char *files[MAX_FILES];

    // Abrir o diretório e listar arquivos
    if ((fp = popen("ls", "r")) == NULL) {
        perror("popen");
        return;
    }

    while (fgets(path, sizeof(path), fp) != NULL) {
        path[strcspn(path, "\n")] = 0; // Remover nova linha
        if (strstr(path, ".c") != NULL) {
            files[file_count] = strdup(path);
            file_count++;
            if (file_count >= MAX_FILES) {
                break; // Limitar o número de arquivos
            }
        }
    }
    pclose(fp);

    // Adicionar arquivos .c ao comando de compilação
    for (int i = 0; i < file_count; i++) {
        strcat(command, files[i]);
        strcat(command, " ");
    }

    // Verificar se há arquivos para compilar
    if (file_count == 0) {
        printf("Nenhum arquivo .c encontrado para compilar.\n");
        return;
    }

    // Executar o comando de compilação
    printf("Compilando com o comando: %s\n", command);
    int compile_result = system(command);

    if (compile_result != 0) {
        printf("A compilação falhou.\n");
        return;
    }

    printf("Compilação bem-sucedida!\n");

    // Liberar memória alocada
    for (int i = 0; i < file_count; i++) {
        free(files[i]);
    }
}

// Função para executar o programa compilado
void run_program() {
    char run_command[] = "./output_program";
    
    // Executar o programa
    printf("Executando o programa: %s\n", run_command);
    int run_result = system(run_command);

    if (run_result != 0) {
        printf("A execução falhou.\n");
    } else {
        printf("Programa executado com sucesso.\n");
    }
}

// Função principal
int main() {
    compile_all_c_files(); // Compilar todos os arquivos .c
    run_program();         // Executar o programa compilado
    return 0;
}
