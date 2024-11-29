#include <gtk/gtk.h>

// Função de callback chamada quando o botão é clicado
void on_button_clicked(GtkWidget *widget, gpointer data) {
    g_print("IonControlView button clicked!\n");
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv); // Inicializa o GTK

    // Cria uma nova janela
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Tesla5001App");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Conecta o sinal de destruir a janela para encerrar o programa
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Cria um botão e conecta o sinal de clique
    GtkWidget *button = gtk_button_new_with_label("Click me!");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    
    // Adiciona o botão à janela
    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show_all(window); // Exibe todos os widgets na janela
    gtk_main(); // Entra no loop principal do GTK

    return 0;
}
