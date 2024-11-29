#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PARTICIPANTS_PER_UNIT 7
#define MAX_UNITS 300
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50

typedef struct {
    char username[USERNAME_LENGTH];
    int login_count;
} LoggedInUser;

typedef struct {
    LoggedInUser users[MAX_UNITS];
    int user_count;
} LoginSecurityKernel;

// Função para autenticar o usuário
int authenticate_user(const char* username, const char* password) {
    // Lógica de autenticação - a ser implementada de acordo com requisitos específicos
    return 1;  // Simulação de autenticação bem-sucedida
}

// Função para fazer login
int login(LoginSecurityKernel* kernel, const char* username, const char* password) {
    if (authenticate_user(username, password)) {
        for (int i = 0; i < kernel->user_count; i++) {
            if (strcmp(kernel->users[i].username, username) == 0) {
                kernel->users[i].login_count++;
                return 1;  // Login bem-sucedido
            }
        }
        // Adiciona um novo usuário logado
        if (kernel->user_count < MAX_UNITS) {
            strcpy(kernel->users[kernel->user_count].username, username);
            kernel->users[kernel->user_count].login_count = 1;
            kernel->user_count++;
            return 1;  // Login bem-sucedido
        }
    }
    return 0;  // Falha no login
}

// Função para fazer logout
int logout(LoginSecurityKernel* kernel, const char* username) {
    for (int i = 0; i < kernel->user_count; i++) {
        if (strcmp(kernel->users[i].username, username) == 0) {
            kernel->users[i].login_count--;
            if (kernel->users[i].login_count == 0) {
                // Remove o usuário da lista
                kernel->users[i] = kernel->users[kernel->user_count - 1];  // Move o último usuário para a posição
                kernel->user_count--;
            }
            return 1;  // Logout bem-sucedido
        }
    }
    return 0;  // Falha no logout
}

// Verifica se o número de unidades ativas é menor ou igual a 300
int is_token_closed(LoginSecurityKernel* kernel) {
    return kernel->user_count <= MAX_UNITS;
}

// Verifica se o número de participantes na unidade atual é menor que 7
int can_join_unit(LoginSecurityKernel* kernel, const char* username) {
    for (int i = 0; i < kernel->user_count; i++) {
        if (strcmp(kernel->users[i].username, username) == 0) {
            return kernel->users[i].login_count < MAX_PARTICIPANTS_PER_UNIT;
        }
    }
    return 1;  // O usuário não está logado, pode se juntar
}

// Função principal para demonstrar o uso
int main() {
    LoginSecurityKernel kernel = {.user_count = 0};
    const char* username = "user123";
    const char* password = "password123";

    if (login(&kernel, username, password)) {
        printf("Login bem-sucedido\n");
        if (can_join_unit(&kernel, username)) {
            printf("O usuário pode se juntar à unidade\n");
        } else {
            printf("A unidade está cheia\n");
        }
    } else {
        printf("Falha no login\n");
    }

    // Simulação de logout
    logout(&kernel, username);

    // Verifica se o token está fechado
    if (is_token_closed(&kernel)) {
        printf("Token está fechado\n");
    } else {
        printf("Token ainda está aberto\n");
    }

    return 0;
}
