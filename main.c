#include <gtk/gtk.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Define PI constant since M_PI might not be available
#define M_PI 3.14159265358979323846

typedef struct {
    GtkWidget *entry;
    GString *input;
} CalculatorState;

// function prototypes
void print_welcome(void);
void print_choices(void);
int get_choice(void);
void show_choice(int);
double add(double, double);
double substract(double, double);
double multiply(double, double);
double devide(double, double);
double root(double, double);
double log_base10(double);
double natural_log(double);
double sine(double);
double cosine(double);
double tangent(double);
double power_function(double, double);
double degrees_to_radians(double);
void handle_choice(int);
double get_number(char[]);
bool ask_continue(void);

// GTK function prototypes
static void on_activate(GtkApplication *app, gpointer user_data);
static void on_button_clicked(GtkWidget *widget, gpointer user_data);

// The main function
int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("test.gtk.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

// function to print the welcome message
void print_welcome(void) {
    // clearing the whole screen before initializing
    printf("\x1b[2J\x1b[H");

    // printing the welcome message.
    printf("\x1b[38;5;82mWelcome to the Looping Calculator!\x1b[0m\n");
    printf("--------------------------------------------------\n\n");
}

// function to print the choices of operations
void print_choices(void) {
    printf("Choose an operation : \n");
    printf("1.  Addition\n");
    printf("2.  Subtraction\n");
    printf("3.  Multiplication\n");
    printf("4.  Division\n");
    printf("5.  Root (nth root)\n");
    printf("6.  Log (Base 10)\n");
    printf("7.  Natural Log (ln)\n");
    printf("8.  Sine (sin)\n");
    printf("9.  Cosine (cos)\n");
    printf("10. Tangent (tan)\n");
    printf("11. Power (x^y)\n");
    printf("12. Exit\n");
}

// function to get the user's choice of operation
int get_choice(void) {
    int choice = 0;
    char buffer[100];
    bool success = false;

    // Printing and getting the choices of operations.
    print_choices();

    // looping until a valid choice is entered
    while (!success) {
        printf("Enter your choice (1-12): ");
        fgets(buffer, sizeof(buffer), stdin);

        // Try to parse an integer
        if (sscanf(buffer, "%d", &choice) == 1) {

            if (choice >= 1 && choice <= 12) {
                success = true;
            } else {
                // clearing the whole line
                printf("\x1b[1A\x1b[0J");
            }
        } else {
            // clearing the whole line
            printf("\x1b[1A\x1b[0J");
        }
    }

    printf("\x1b[14A\x1b[0J");
    return choice;
}

// function to display the user's choice of operation
void show_choice(int choice) {
    printf("You chose ");
    switch (choice) {
        case 1: {
            printf("Addition");
            break;
        }
        case 2: {
            printf("Subtraction");
            break;
        }
        case 3: {
            printf("Multiplication");
            break;
        }
        case 4: {
            printf("Division");
            break;
        }
        case 5: {
            printf("Root (nth root)");
            break;
        }
        case 6: {
            printf("Log (Base 10)");
            break;
        }
        case 7: {
            printf("Natural Log (ln)");
            break;
        }
        case 8: {
            printf("Sine (sin)");
            break;
        }
        case 9: {
            printf("Cosine (cos)");
            break;
        }
        case 10: {
            printf("Tangent (tan)");
            break;
        }
        case 11: {
            printf("Power (x^y)");
            break;
        }
        default: {
            printf("to Exit the calculator");
        }
    }
    printf(".\n");
}

// function to add two double numbers
double add(double a, double b) { return a + b; }

// function to find the difference between two numbers
double substract(double a, double b) { return a - b; }

// function to find the product of two numbers
double multiply(double a, double b) { return a * b; }

// function to find the quotient of two numbers
double devide(double a, double b) {
    if (b == 0) {
        printf("Error: Cannot divide by zero.\n");
        return 0;
    }

    return a / b;
}

// function to find the square root of a number
double root(double number, double n) {
    if (number < 0) {
        printf("Cannot calculate complex numbers.\n");
        return 0;
    }

    if (n == 0) {
        printf("Error: Root degree cannot be zero.\n");
        return 0;
    }

    return pow(number, 1.0 / n);
}

// function to calculate logarithm base 10 and natural logarithm
double log_base10(double a) {
    if (a <= 0) {
        printf("Error: Logarithm undefined for zero or negative numbers.\n");
        return 0;
    }
    return log10(a);
}

double natural_log(double a) {
    if (a <= 0) {
        printf("Error: Natural log undefined for zero or negative numbers.\n");
        return 0;
    }
    return log(a);
}

double sine(double a) { return sin(a); }

double cosine(double a) { return cos(a); }

double tangent(double a) { return tan(a); }

double power_function(double base, double exponent) {
    // Handle special cases
    if (base == 0 && exponent < 0) {
        printf(
            "Error: Cannot raise zero to a negative power (division by "
            "zero).\n");
        return 0;
    }

    if (base < 0 && (exponent != floor(exponent))) {
        printf(
            "Error: Cannot raise negative number to non-integer power (complex "
            "result).\n");
        return 0;
    }

    return pow(base, exponent);
}

//  function to convert degrees to radians
double degrees_to_radians(double degrees) { return degrees * M_PI / 180.0; }

void handle_choice(int choice) {
    // Taking input from the user.
    double num1, num2, r;

    // Prompting the user to enter two numbers.
    if (choice <= 4) {
        // Getting and then clear the line after first input
        num1 = get_number("Enter first number: ");
        printf("\x1b[1A\x1b[0J");

        // Getting and then clear the line after first input
        num2 = get_number("Enter second number: ");
        printf("\x1b[1A\x1b[0J");
    }

    if (choice == 5) {
        // Getting and then clear the line after first input
        num1 = get_number("Enter the desired number: ");
        printf("\x1b[1A\x1b[0J");

        // Getting and then clear the line after first input
        num2 = get_number("Enter the root degree: ");
        printf("\x1b[1A\x1b[0J");
    }

    if (choice == 6 && choice == 7) {
        // Getting and then clear the line after first input
        num1 = get_number("Enter the desired number: ");
        printf("\x1b[1A\x1b[0J");
    }

    if (choice >= 8 && choice <= 10) {
        // Getting and then clear the line after first input
        num1 = get_number("Enter angle (in degrees): ");
        printf("\x1b[1A\x1b[0J");
    }

    if (choice == 11) {
        // Getting and then clear the line after first input
        num1 = get_number("Enter the base number: ");
        printf("\x1b[1A\x1b[0J");

        // Getting and then clear the line after first input
        num2 = get_number("Enter the exponent (power): ");
        printf("\x1b[1A\x1b[0J");
    }

    switch (choice) {
        case 1: {
            r = add(num1, num2);
            printf("The sum of %g and %g is: %g\n", num1, num2, r);
            break;
        }

        case 2: {
            r = substract(num1, num2);
            printf("The result of %g - %g is: %g\n", num1, num2, r);
            break;
        }

        case 3: {
            r = multiply(num1, num2);
            printf("The product of %g and %g is: %g\n", num1, num2, r);
            break;
        }

        case 4: {
            r = devide(num1, num2);
            printf("The quotient of %g and %g is: %g\n", num1, num2, r);
            break;
        }

        case 5: {
            r = root(num1, num2);
            printf("The %g root of %g is: %g\n", num2, num1, r);
            break;
        }

        case 6: {
            r = log_base10(num1);
            printf("The logarithm base 10 of %g is: %g\n", num1, r);
            break;
        }

        case 7: {
            r = natural_log(num1);
            printf("The natural logarithm of %g is: %g\n", num1, r);
            break;
        }

        case 8: {
            r = sine(degrees_to_radians(num1));
            printf("The sine of %g degrees is: %g\n", num1, r);
            break;
        }

        case 9: {
            r = cosine(degrees_to_radians(num1));
            printf("The cosine of %g degrees is: %g\n", num1, r);
            break;
        }

        case 10: {
            r = tangent(degrees_to_radians(num1));
            printf("The tangent of %g degrees is: %g\n", num1, r);
            break;
        }

        case 11: {
            r = power_function(num1, num2);
            printf("The result of %g raised to the power of %g is: %g\n", num1,
                   num2, r);
            break;
        }
    }
}

// function to get a number from the user
double get_number(char prompt[]) {
    double number;
    char buffer[100];
    bool success = false;

    while (!success) {
        // Clear current line before printing prompt
        printf("\r\033[2K");  // move to start and clear line
        printf("%s", prompt);
        fflush(stdout);
        fgets(buffer, sizeof(buffer), stdin);

        // Try to parse a double
        if (sscanf(buffer, "%lf", &number) == 1) {
            success = true;
        } else {
            // clearing the whole line
            printf("\x1b[1A\x1b[1K");
        }
    }

    return number;
}

// function to ask the user whether to continue or not
bool ask_continue(void) {
    char buffer[100];
    char ch;
    bool valid = false;

    // Prompting the user to continue or not.
    while (!valid) {
        printf("Do you want to continue [y/n]: ");
        fgets(buffer, sizeof(buffer), stdin);

        // sscanf parses the first non-whitespace character
        if (sscanf(buffer, " %c", &ch) == 1) {
            if (ch == 'y' || ch == 'n' || ch == 'Y' || ch == 'N') {
                valid = true;
            } else {
                // Clear invalid line (optional)
                printf("\x1b[1A\x1b[0J");  // Move up and clear line
            }
        }
    }

    // Optional: clear this prompt line if answer is 'n'
    if (ch == 'n' || ch == 'N') {
        printf("\x1b[1A\x1b[0J");
        return false;
    }

    return true;
}

static void on_button_clicked(GtkWidget *widget, gpointer user_data) {
    CalculatorState *state = (CalculatorState *)user_data;
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));

    if (strcmp(label, "C") == 0) {
        g_string_set_size(state->input, 0);
    } else if (strcmp(label, "=") == 0) {
        double result = g_strtod(state->input->str, NULL);
        g_string_printf(state->input, "%g", result);
    } else {
        g_string_append(state->input, label);
    }

    gtk_entry_set_text(GTK_ENTRY(state->entry), state->input->str);
}

// A function to activate the program
static void on_activate(GtkApplication *app, gpointer user_data) {
    CalculatorState *state = g_new0(CalculatorState, 1);
    state->input = g_string_new("");

    // Create and set title, size, and position of the main window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "C GUI Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Create a container (box) to hold widgets (display, buttons, etc.)
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Create and set alignment, state, and txt of the main diplay area (Output)
    state->entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(state->entry), 1.0);  // right-align
    gtk_editable_set_editable(GTK_EDITABLE(state->entry), FALSE);
    gtk_entry_set_text(GTK_ENTRY(state->entry), "");
    gtk_widget_set_hexpand(state->entry, TRUE);
    gtk_widget_set_vexpand(state->entry, FALSE);  // No vertical expansion
    gtk_box_pack_start(GTK_BOX(box), state->entry, TRUE, TRUE, 0);

    // Set the font size
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, "entry { font-size: 24px; }", -1,
                                    NULL);

    GtkStyleContext *context = gtk_widget_get_style_context(state->entry);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Create and set buttons for the button grid
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    const gchar *buttons[5][4] = {{"C", " ", "%", "/"},
                                  {"7", "8", "9", "*"},
                                  {"4", "5", "6", "-"},
                                  {"1", "2", "3", "+"},
                                  {" ", "0", ".", "="}};

    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 4; col++) {
            const gchar *label = buttons[row][col];
            if (strlen(label) == 0) continue;

            GtkWidget *button = gtk_button_new_with_label(label);
            gtk_widget_set_hexpand(button, TRUE);
            gtk_widget_set_vexpand(button, TRUE);
            gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked),
                             state);
        }
    }
    gtk_box_pack_start(GTK_BOX(box), grid, TRUE, TRUE, 0);

    // Showing all the widgets
    gtk_widget_show_all(window);
}
