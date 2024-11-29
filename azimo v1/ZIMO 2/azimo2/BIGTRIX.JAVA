import java.util.Scanner;

public class BigTrickZ {

    // Constantes para autenticação
    private static final String VALID_USER = "admin";
    private static final String VALID_PASSWORD = "password123";

    // Função para autenticar o usuário
    public static boolean authenticateUser(String username, String password) {
        return username.equals(VALID_USER) && password.equals(VALID_PASSWORD);
    }

    // Função para inicializar a transmissão WPS-B
    public static void initializeWPSB() {
        System.out.println("Transmissão WPS-B inicializada no BigTrick-Z.");
    }

    // Função para transmitir dados via WPS-B
    public static void transmitData(String data) {
        System.out.println("Transmitindo dados via WPS-B: " + data);
    }

    // Função para transmitir dados utilizando Two-PiX Key
    public static void transmitDataWithTwoPix(String data) {
        System.out.println("Transmitindo com Two-PiX Key: " + data);
    }

    // Função principal
    public static void main(String[] args) {
        // Inicializa a transmissão WPS-B
        initializeWPSB();

        // Scanner para ler entradas do usuário
        Scanner scanner = new Scanner(System.in);

        // Dados do usuário para autenticação
        System.out.print("Digite o nome de usuário: ");
        String username = scanner.nextLine();

        System.out.print("Digite a senha: ");
        String password = scanner.nextLine();

        // Autenticar o usuário
        if (authenticateUser(username, password)) {
            System.out.println("Autenticação bem-sucedida!");

            // Dados a serem transmitidos
            String dataToTransmit = "Hello, HoloNet 7G!";

            // Transmitir dados usando WPS-B
            transmitData(dataToTransmit);

            // Transmitir dados usando Two-PiX Key
            transmitDataWithTwoPix(dataToTransmit);
        } else {
            System.out.println("Falha na autenticação. Verifique seu nome de usuário e senha.");
        }

        scanner.close();
    }
}
