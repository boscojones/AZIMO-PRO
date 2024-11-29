#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLANS 100

// Estrutura para um plano de investimento
typedef struct {
    char plan_name[50];
    double initial_investment;
    double monthly_return;
    double annual_return;
    double net_annual_return;
    int slots;
} InvestmentPlan;

// Gerenciador de planos de investimento
typedef struct {
    InvestmentPlan plans[MAX_PLANS];
    int count;
} InvestmentPlanManager;

// Inicializa o gerenciador de planos
void init_manager(InvestmentPlanManager* manager) {
    manager->count = 0;
}

// Adiciona um plano de investimento
void add_investment_plan(InvestmentPlanManager* manager, const char* name, double initial, double monthly, double annual, double net_annual, int slots) {
    if (manager->count < MAX_PLANS) {
        InvestmentPlan* plan = &manager->plans[manager->count++];
        strcpy(plan->plan_name, name);
        plan->initial_investment = initial;
        plan->monthly_return = monthly;
        plan->annual_return = annual;
        plan->net_annual_return = net_annual;
        plan->slots = slots;
    } else {
        printf("Erro: Número máximo de planos atingido.\n");
    }
}

// Exibe os planos de investimento
void display_investment_plans(const InvestmentPlanManager* manager) {
    for (int i = 0; i < manager->count; i++) {
        const InvestmentPlan* plan = &manager->plans[i];
        printf("Plano: %s\n", plan->plan_name);
        printf("Investimento Inicial: %.2f\n", plan->initial_investment);
        printf("Retorno Mensal: %.2f\n", plan->monthly_return);
        printf("Retorno Anual: %.2f\n", plan->annual_return);
        printf("Retorno Anual Líquido: %.2f\n", plan->net_annual_return);
        printf("Slots: %d\n", plan->slots);
        printf("--------------\n");
    }
}

// Função para configurar o ambiente (local, AWS, Azure)
void setup_environment() {
    // Aqui você pode adicionar lógica para detectar e configurar o ambiente
    // Por exemplo, verificar variáveis de ambiente ou arquivos de configuração

    const char* env = getenv("INVESTMENT_ENV");
    if (env == NULL) {
        printf("Executando no ambiente local.\n");
    } else if (strcmp(env, "AWS") == 0) {
        printf("Executando no ambiente AWS.\n");
    } else if (strcmp(env, "AZURE") == 0) {
        printf("Executando no ambiente Azure.\n");
    } else {
        printf("Ambiente desconhecido. Executando localmente.\n");
    }
}

// Função principal
int main() {
    InvestmentPlanManager manager;
    init_manager(&manager);

    // Configurar o ambiente
    setup_environment();

    // Adicionar planos de investimento
    add_investment_plan(&manager, "Plano A", 1000, 100, 1200, 1000, 5);
    add_investment_plan(&manager, "Plano B", 2000, 200, 2400, 2000, 10);

    // Exibir os planos de investimento
    display_investment_plans(&manager);

    return 0;
}
