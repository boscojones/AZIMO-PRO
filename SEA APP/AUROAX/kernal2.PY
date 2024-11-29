import os

class ProfStakeKernel:
    # Inicializa o sistema de staking
    def init_stake_system(self) -> None:
        print("Inicializando o sistema PROF STAKE...")

    # Processa o staking de ativos NBH
    def process_stake(self, amount: float, asset: str) -> str:
        print("Processando staking de ativos NBH...")
        stake_confirmation = f"Staked {amount} units of {asset}"
        return stake_confirmation

    # Armazena os dados de staking processados em cache
    def cache_stake_data(self, stake_data: str) -> None:
        file_path = "/tmp/nbh_stake_cache.txt"
        try:
            with open(file_path, 'w') as cache_file:
                cache_file.write(stake_data)
            print("Dados de staking armazenados em cache com sucesso.")
            
            # Verificando se os dados foram armazenados corretamente
            if os.path.exists(file_path):
                print(f"Verificação: O arquivo de cache foi salvo em {file_path}.")
            else:
                print("Verificação: O arquivo de cache não foi salvo.")
                
        except IOError as e:
            print(f"Erro ao armazenar dados de staking: {str(e)}")

# Função principal
if __name__ == "__main__":
    # Instancia o kernel
    prof_stake_kernel = ProfStakeKernel()
    prof_stake_kernel.init_stake_system()

    # Processa o staking
    stake_confirmation = prof_stake_kernel.process_stake(1000.0, "NBHToken")

    # Cache dos dados de staking
    prof_stake_kernel.cache_stake_data(stake_data=stake_confirmation)
