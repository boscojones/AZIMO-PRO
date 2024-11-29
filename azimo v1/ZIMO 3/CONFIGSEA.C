#include <stdio.h>
#include <stdlib.h>

void createConfigFile() {
    FILE *file = fopen("config", "w"); // Abre o arquivo para escrita
    if (file == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo de configuração.\n");
        exit(1);
    }

    // Escreve a configuração das instâncias AWS
    fprintf(file, "# Configuração do SEAS com chaves SSH da AWS\n\n");

    // Host para a instância AWS 1
    fprintf(file, "# Host para a instância AWS 1\n");
    fprintf(file, "Host aws-instance-1\n");
    fprintf(file, "    HostName ec2-XX-XXX-XXX-XX.compute-1.amazonaws.com\n");
    fprintf(file, "    User ec2-user\n");
    fprintf(file, "    IdentityFile ~/.ssh/aws_key_1.pem\n");
    fprintf(file, "    ForwardAgent yes\n\n");

    // Host para a instância AWS 2
    fprintf(file, "# Host para a instância AWS 2\n");
    fprintf(file, "Host aws-instance-2\n");
    fprintf(file, "    HostName ec2-YY-YYY-YYY-YY.compute-1.amazonaws.com\n");
    fprintf(file, "    User ec2-user\n");
    fprintf(file, "    IdentityFile ~/.ssh/aws_key_2.pem\n");
    fprintf(file, "    ForwardAgent yes\n");

    fclose(file); // Fecha o arquivo
    printf("Arquivo de configuração 'config' criado com sucesso.\n");
}

int main() {
    printf("Criando o arquivo de configuração do SEAS...\n");
    createConfigFile(); // Chama a função para criar o arquivo
    return 0;
}
