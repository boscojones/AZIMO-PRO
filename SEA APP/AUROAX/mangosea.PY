# Classe para o plano de investimento
class InvestmentPlan:
    def __init__(self, plan_name, initial_investment, monthly_return, annual_return, net_annual_return, slots):
        self.plan_name = plan_name
        self.initial_investment = initial_investment
        self.monthly_return = monthly_return
        self.annual_return = annual_return
        self.net_annual_return = net_annual_return
        self.slots = slots

    def __str__(self):
        return (f"Plano: {self.plan_name}\n"
                f"Investimento Inicial: {self.initial_investment}\n"
                f"Retorno Mensal: {self.monthly_return}\n"
                f"Retorno Anual: {self.annual_return}\n"
                f"Retorno Anual Líquido: {self.net_annual_return}\n"
                f"Slots: {self.slots}\n"
                "--------------")

# Gerenciador de planos de investimento
class InvestmentPlanManager:
    def __init__(self):
        self.plans = []

    # Função para adicionar um plano de investimento
    def add_investment_plan(self, plan_name, initial_investment, monthly_return, annual_return, net_annual_return, slots):
        # Validação dos dados de entrada
        if initial_investment <= 0 or monthly_return < 0 or annual_return < 0 or net_annual_return < 0 or slots <= 0:
            print("Erro: Valores de investimento e slots devem ser positivos.")
            return

        # Adiciona o novo plano
        new_plan = InvestmentPlan(plan_name, initial_investment, monthly_return, annual_return, net_annual_return, slots)
        self.plans.append(new_plan)  # Usa append para adicionar o novo plano

    # Função para exibir os planos de investimento
    def display_investment_plans(self):
        if not self.plans:
            print("Nenhum plano de investimento disponível.")
            return
            
        for plan in self.plans:
            print(plan)  # Chama o método __str__ da classe InvestmentPlan

# Função principal
def main():
    manager = InvestmentPlanManager()

    # Adicionando alguns planos de investimento como exemplo
    manager.add_investment_plan("Plano A", 1000, 100, 1200, 1000, 5)
    manager.add_investment_plan("Plano B", 2000, 200, 2400, 2000, 10)

    # Exibir os planos de investimento
    manager.display_investment_plans()

# Chamada da função principal
if __name__ == "__main__":
    main()
