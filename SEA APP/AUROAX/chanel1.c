package holocore.ssp;

// Classe representando o canal dual
class DualChannel {
    private String name;

    public DualChannel(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}

// Classe representando o canal hiper
class HyperChannel {
    private String name;

    public HyperChannel(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}

// Classe principal que gerencia os canais
public class HoloCore {
    private DualChannel dualChannel1;
    private DualChannel dualChannel2;
    private HyperChannel hyperChannel;

    public HoloCore() {
        // Inicializa os canais
        dualChannel1 = new DualChannel("Dual Channel 1");
        dualChannel2 = new DualChannel("Dual Channel 2");
        hyperChannel = new HyperChannel("Hyper Channel");
    }

    // Método para iniciar o processamento
    public void startProcessing() {
        HolocoreStage1 stage1 = new HolocoreStage1(dualChannel1.getName(), dualChannel2.getName());
        stage1.startProcessing();
    }

    public static void main(String[] args) {
        HoloCore holoCore = new HoloCore();
        holoCore.startProcessing();
    }
}

// Classe para gerenciar o processamento nos canais
class HolocoreStage1 {
    private String dualChannel1;
    private String dualChannel2;

    // Construtor para inicializar os canais
    public HolocoreStage1(String dualChannel1, String dualChannel2) {
        this.dualChannel1 = dualChannel1;
        this.dualChannel2 = dualChannel2;
    }

    // Método para iniciar o processamento nos canais
    public void startProcessing() {
        System.out.println("Iniciando processamento no Dual Channel 1: " + dualChannel1);
        processChannel(dualChannel1);

        System.out.println("Iniciando processamento no Dual Channel 2: " + dualChannel2);
        processChannel(dualChannel2);
    }

    // Método de processamento simulado para cada canal
    private void processChannel(String channel) {
        System.out.println("Processando dados no canal: " + channel);
        // Simulação de processamento de dados
        try {
            Thread.sleep(2000); // Simula o tempo de processamento
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Processamento finalizado para o canal: " + channel);
    }
}
