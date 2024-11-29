import java.util.Scanner;

public class FireBunny {
    private final String validUser = "admin";
    private final String validPassword = "password123";

    public void initializeWPSB() {
        System.out.println("Transmissão WPS-B inicializada.");
    }

    public void transmitData(String data) {
        System.out.println("Transmitindo dados via WPS-B: " + data);
    }

    public void transmitDataWithTwoPix(String data) {
        System.out.println("Transmitindo com Two-PiX Key: " + data);
    }

    public boolean authenticateUser(String username, String password) {
        return username.equals(validUser) && password.equals(validPassword);
    }

    public static void main(String[] args) {
        FireBunny auth = new FireBunny();
        auth.initializeWPSB();

        // Solicita os dados do usuário
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o nome de usuário: ");
        String username = scanner.nextLine();
        System.out.print("Digite a senha: ");
        String password = scanner.nextLine();

        // Autentica o usuário
        if (auth.authenticateUser(username, password)) {
            System.out.println("Autenticação bem-sucedida!");

            // Dados a serem transmitidos
            String dataToTransmit = "Hello, HoloNet 7G!";

            // Transmitir dados usando WPS-B
            auth.transmitData(dataToTransmit);

            // Transmitir dados usando Two-PiX Key
            auth.transmitDataWithTwoPix(dataToTransmit);
        } else {
            System.out.println("Falha na autenticação. Verifique seu nome de usuário e senha.");
        }
        scanner.close();
    }
}
