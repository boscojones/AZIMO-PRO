#include <stdio.h>
#include <stdlib.h>

void createAwsConfigFile() {
    const char *awsConfig = 
    "# Configuração do SEAS com chaves SSH da AWS\n\n"
    "# Host para a instância AWS 1\n"
    "Host aws-instance-1\n"
    "    HostName ec2-XX-XXX-XXX-XX.compute-1.amazonaws.com\n"
    "    User ec2-user\n"
    "    IdentityFile ~/.ssh/aws_key_1.pem\n"
    "    ForwardAgent yes\n\n"
    "# Host para a instância AWS 2\n"
    "Host aws-instance-2\n"
    "    HostName ec2-YY-YYY-YYY-YY.compute-1.amazonaws.com\n"
    "    User ec2-user\n"
    "    IdentityFile ~/.ssh/aws_key_2.pem\n"
    "    ForwardAgent yes\n";

    FILE *file = fopen("config_aws", "w");
    if (file == NULL) {
        perror("Erro ao criar o arquivo de configuração AWS");
        return;
    }

    fputs(awsConfig, file);
    fclose(file);
    printf("Arquivo de configuração 'config_aws' criado com sucesso.\n");
}

void createAzureConfigFile() {
    const char *azureConfig = 
    "# Configuração do SEAS com chaves SSH da Azure\n\n"
    "# Host para a instância Azure 1\n"
    "Host azure-instance-1\n"
    "    HostName azure-XX-XXX-XXX-XX.cloudapp.net\n"
    "    User azureuser\n"
    "    IdentityFile ~/.ssh/azure_key_1.pem\n"
    "    ForwardAgent yes\n\n"
    "# Host para a instância Azure 2\n"
    "Host azure-instance-2\n"
    "    HostName azure-YY-YYY-YYY-YY.cloudapp.net\n"
    "    User azureuser\n"
    "    IdentityFile ~/.ssh/azure_key_2.pem\n"
    "    ForwardAgent yes\n";

    FILE *file = fopen("config_azure", "w");
    if (file == NULL) {
        perror("Erro ao criar o arquivo de configuração Azure");
        return;
    }

    fputs(azureConfig, file);
    fclose(file);
    printf("Arquivo de configuração 'config_azure' criado com sucesso.\n");
}

int main() {
    printf("Criando os arquivos de configuração do SEAS...\n");
    createAwsConfigFile(); // Cria o arquivo de configuração da AWS
    createAzureConfigFile(); // Cria o arquivo de configuração da Azure
    return 0;
}
