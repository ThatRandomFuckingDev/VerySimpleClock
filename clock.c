
static gboolean update_clock(gpointer data) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char buffer[10];
    sprintf(buffer, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    char *escaped_markup = g_markup_printf_escaped("<big>%s</big>", buffer);

    gtk_label_set_markup(GTK_LABEL(clockLabel), escaped_markup);

    g_free(escaped_markup);

    return G_SOURCE_CONTINUE;

}


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Clock");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    clockLabel = gtk_label_new(NULL);
    gtk_label_set_markup (GTK_LABEL (clockLabel), "<big></big>");

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid), clockLabel, 0, 0, 1, 1);

    gtk_container_add(GTK_CONTAINER(window), grid);

    g_timeout_add_seconds(1, update_clock, NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
