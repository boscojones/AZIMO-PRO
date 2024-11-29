import os

# Função para iniciar o processo SSP
def start_nbh_ssp_process():
    print("Iniciando o processo NBH SSP...")

    # Simulação de dados recebidos do POSH Shell
    nbh_data = "Dados do POSH Shell"
    print(f"Processando dados: {nbh_data}")

    # Caminho para o local seguro (simulação)
    secure_storage_path = "/tmp/nbh_ssp_storage.txt"

    # Armazenando os dados processados em um local seguro
    try:
        # Usando um gerenciador de contexto para garantir que o arquivo seja fechado corretamente
        with open(secure_storage_path, 'w') as secure_file:
            secure_file.write(nbh_data)
        print("Dados armazenados no SSP com sucesso.")
    except IOError as e:
        print(f"Erro ao armazenar dados: {str(e)}")

    # Verificando se os dados foram armazenados corretamente
    if os.path.exists(secure_storage_path):
        print(f"Verificação: O arquivo foi salvo em {secure_storage_path}.")
    else:
        print("Verificação: O arquivo não foi salvo.")

# Função principal
if __name__ == "__main__":
    start_nbh_ssp_process()
