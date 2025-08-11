#include <gtk/gtk.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ensure M_PI is defined for mathematical calculations
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    GtkWidget *entry;
    GString *input;
} CalculatorState;

/**
 * =======================================================================
 *             GUI EVENT HANDLERS AND INTERFACE FUNCTIONS
 * =======================================================================
 */

/**
 * Update the calculator display with new text
 */
static void update_display(CalculatorState *state, const char *text) {
    gtk_entry_set_text(GTK_ENTRY(state->entry), text);
}

/**
 * Main button click handler - processes all calculator button presses
 */
static void on_button_clicked(GtkWidget *widget, gpointer user_data) {
    CalculatorState *state = (CalculatorState *)user_data;
    const gchar *button_label = gtk_button_get_label(GTK_BUTTON(widget));

    // Clear button - reset calculator state
    if (strcmp(button_label, "C") == 0) {
        g_string_set_size(state->input, 0);
        update_display(state, "0");
        return;
    }

    // Equals button - evaluate current expression
    if (strcmp(button_label, "=") == 0) {
        double result = g_strtod(state->input->str, NULL);
        g_string_printf(state->input, "%g", result);
        update_display(state, state->input->str);
        return;
    }

    g_string_append(state->input, button_label);

    // Update display with current input
    update_display(state, state->input->str);
}

/**
 * Keyboard input handler - provides shortcuts for common operations
 */
static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event,
                             gpointer user_data) {
    CalculatorState *state = (CalculatorState *)user_data;
    guint key = event->keyval;

    // Enter key - same as equals button
    if (key == GDK_KEY_Return || key == GDK_KEY_KP_Enter) {
        // Create temporary button to reuse existing equals logic
        GtkWidget *equals_button = gtk_button_new_with_label("=");
        on_button_clicked(equals_button, user_data);
        g_object_ref_sink(equals_button);  // Clean up temporary widget
        g_object_unref(equals_button);
        return TRUE;  // Event handled
    }

    // Backspace key - same as backspace button
    if (key == GDK_KEY_BackSpace) {
        if (state->input->len > 0) {
            g_string_truncate(state->input, state->input->len - 1);
        }
        update_display(state, state->input->str);
        return TRUE;  // Event handled
    }

    return FALSE;  // Let default handler process other keys
}

/**
 * Create a button with label and connect to click handler
 */
static GtkWidget *create_button(const char *label, CalculatorState *state) {
    GtkWidget *button = gtk_button_new_with_label(label);
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), state);
    return button;
}

/**
 * Window destruction handler - clean up allocated memory
 */
static void on_window_destroy(GtkWidget *widget, gpointer user_data) {
    CalculatorState *state = (CalculatorState *)user_data;
    if (state) {
        if (state->input) {
            g_string_free(state->input, TRUE);
        }
        free(state);
    }
}

/**
 * =======================================================================
 *                      USER INTERFACE CONSTRUCTION
 * =======================================================================
 */

/**
 * Build the complete calculator user interface
 * Creates window, display, button grids, and connects all event handlers
 */
static void build_user_interface(GtkApplication *app, CalculatorState *state) {
    // Create and set title, size, and position of the main window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "C GUI Scientific Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 380, 550);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window),
                             FALSE);  // Fixed size for clean layout
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), state);

    // Create main vertical container to hold widgets (display, buttons, etc.)
    GtkWidget *main_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(main_container), 15);
    gtk_container_add(GTK_CONTAINER(window), main_container);

    // Create display (entry) to shows current input and results
    state->entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(state->entry), 1.0);  // Right-align
    gtk_editable_set_editable(GTK_EDITABLE(state->entry), FALSE);  // Read-only
    gtk_entry_set_text(GTK_ENTRY(state->entry), "0");
    gtk_widget_set_size_request(state->entry, -1, 50);  // Set minimum height
    gtk_box_pack_start(GTK_BOX(main_container), state->entry, FALSE, FALSE, 0);

    // Apply CSS styling for larger, more readable font
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(
        css_provider,
        "entry { font-size: 24px; font-weight: bold; padding: 8px; }", -1,
        NULL);
    GtkStyleContext *entry_context = gtk_widget_get_style_context(state->entry);
    gtk_style_context_add_provider(entry_context,
                                   GTK_STYLE_PROVIDER(css_provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(css_provider);

    // Create main button grid (numbers, basic operators, equals)
    GtkWidget *main_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(main_grid), 8);
    gtk_grid_set_column_spacing(GTK_GRID(main_grid), 8);
    // Equal row heights & column widths for the buttons
    gtk_grid_set_row_homogeneous(GTK_GRID(main_grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(main_grid), TRUE);
    gtk_box_pack_start(GTK_BOX(main_container), main_grid, TRUE, TRUE, 0);

    // Define button layout: 5 rows x 4 columns
    const char *main_button_layout[5][4] = {
        {"C", "(", ")", "/"},  // Row 0: Clear, parentheses, divide
        {"7", "8", "9", "*"},  // Row 1: Numbers 7-9, multiply
        {"4", "5", "6", "-"},  // Row 2: Numbers 4-6, subtract
        {"1", "2", "3", "+"},  // Row 3: Numbers 1-3, add
        {"0", ".", "^", "="}   // Row 4: Zero, decimal, power, equals
    };

    // Create and place main buttons
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 4; col++) {
            GtkWidget *button =
                create_button(main_button_layout[row][col], state);
            gtk_widget_set_size_request(button, 70,
                                        50);  // Consistent button size
            gtk_grid_attach(GTK_GRID(main_grid), button, col, row, 1, 1);
        }
    }

    // Create scientific function grid (functions like sin, cos, sqrt, etc.)
    GtkWidget *function_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(function_grid), 8);
    gtk_grid_set_column_spacing(GTK_GRID(function_grid), 8);
    gtk_grid_set_row_homogeneous(GTK_GRID(function_grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(function_grid), TRUE);
    gtk_box_pack_start(GTK_BOX(main_container), function_grid, FALSE, FALSE, 0);

    // Define scientific function button layout: 2 rows x 4 columns
    const char *function_button_layout[2][4] = {
        // Row 0: Square root, log base 10, natural log, backspace
        {"sqrt", "log", "ln", "⌫"},
        // Row 1: Trigonometric functions, percentage
        {"sin", "cos", "tan", "%"}};

    // Create and place function buttons
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 4; col++) {
            GtkWidget *button =
                create_button(function_button_layout[row][col], state);
            gtk_widget_set_size_request(button, 70, 40);
            gtk_grid_attach(GTK_GRID(function_grid), button, col, row, 1, 1);
        }
    }

    // Enable keyboard shortcuts for the entire window
    gtk_widget_set_can_focus(window, TRUE);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press),
                     state);

    // Show all widgets
    gtk_widget_show_all(window);
}

/**
 * =======================================================================
 *                          APPLICATION LIFECYCLE
 * =======================================================================
 */

/**
 * Application activation handler - called when app starts
 * Initializes calculator state and builds user interface
 */
static void on_application_activate(GtkApplication *app, gpointer user_data) {
    // Allocate and initialize calculator state
    CalculatorState *state =
        (CalculatorState *)calloc(1, sizeof(CalculatorState));

    // Checks if the allocation was successful
    if (!state) {
        g_error("Failed to allocate calculator state");
        return;
    }

    state->input = g_string_new("");

    // Build and show the user interface
    build_user_interface(app, state);
}

/**
 * Main entry point
 * Creates GTK application and runs main event loop
 */
int main(int argc, char **argv) {
    // Create GTK application with unique identifier
    GtkApplication *app = gtk_application_new("com.example.c-gui-calculator",
                                              G_APPLICATION_DEFAULT_FLAGS);

    // Connect activation signal to our setup function
    g_signal_connect(app, "activate", G_CALLBACK(on_application_activate),
                     NULL);

    // Run the application (blocks until all windows are closed)
    int exit_status = g_application_run(G_APPLICATION(app), argc, argv);

    // Clean up application object
    g_object_unref(app);

    return exit_status;
}