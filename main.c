#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// Define color codes for terminal output
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_WELCOME "\x1b[38;5;82m"
#define COLOR_RESET "\x1b[0m"

// Define PI constant since M_PI might not be available
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function prototypes
void print_welcome(void);
void print_choices(void);
int get_choice(void);
void show_choice(int);
double add(double, double);
double subtract(double, double);
double multiply(double, double);
double divide(double, double);
double root(double, double);
double log_base10(double);
double natural_log(double);
double sine(double);
double cosine(double);
double tangent(double);
double power_function(double, double);
double degrees_to_radians(double);
void handle_choice(int);
double get_number(const char[]);
bool ask_continue(void);

int main(void) {
    int choice;

    while (true) {
        print_welcome();
        choice = get_choice();
        show_choice(choice);

        if (choice == 12) {
            printf("\n");
            break;
        }

        handle_choice(choice);

        printf("\n");
        if (!ask_continue()) break;
    }

    printf("--------------------------------------------------\n");
    printf(COLOR_RED "Exiting the calculator. Goodbye!\n" COLOR_RESET "\n");
    return 0;
}

void print_welcome(void) {
    printf("\x1b[2J\x1b[H");
    printf(COLOR_WELCOME "Welcome to the Looping Calculator!\n" COLOR_RESET);
    printf("--------------------------------------------------\n\n");
}

// MODIFIED: This function now prints in two columns.
void print_choices(void) {
    printf("Choose an operation:\n");
    printf("    1.  Addition          \t\t7.  Natural Log (ln)\n");
    printf("    2.  Subtraction       \t\t8.  Sine (sin)\n");
    printf("    3.  Multiplication    \t\t9.  Cosine (cos)\n");
    printf("    4.  Division          \t\t10. Tangent (tan)\n");
    printf("    5.  Root (nth root)   \t\t11. Power (x^y)\n");
    printf("    6.  Log (Base 10)     \t\t12. Exit\n");
}

int get_choice(void) {
    int choice = 0;
    char buffer[100];
    bool success = false;

    print_choices();

    while (!success) {
        printf("Enter your choice (1-12): ");
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;

        if (sscanf(buffer, "%d", &choice) == 1 && choice >= 1 && choice <= 12) {
            success = true;
        } else {
            // Clears the line with the invalid input
            printf("\x1b[1A\x1b[0J");
        }
    }
    // MODIFIED: The menu is now 7 lines high (1 title + 6 option lines).
    // This clears the menu from the screen after a choice is made.
    printf("\x1b[8A\x1b[0J");
    return choice;
}

void show_choice(int choice) {
    printf("You chose ");
    switch (choice) {
        case 1:
            printf("Addition");
            break;
        case 2:
            printf("Subtraction");
            break;
        case 3:
            printf("Multiplication");
            break;
        case 4:
            printf("Division");
            break;
        case 5:
            printf("Root (nth root)");
            break;
        case 6:
            printf("Log (Base 10)");
            break;
        case 7:
            printf("Natural Log (ln)");
            break;
        case 8:
            printf("Sine (sin)");
            break;
        case 9:
            printf("Cosine (cos)");
            break;
        case 10:
            printf("Tangent (tan)");
            break;
        case 11:
            printf("Power (x^y)");
            break;
        default:
            printf("to Exit the calculator");
    }
    printf(".\n");
}

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }

double divide(double a, double b) {
    if (b == 0) {
        printf(COLOR_RED "Error: Cannot divide by zero.\n" COLOR_RESET);
        return NAN;  // Return Not-a-Number for errors
    }
    return a / b;
}

double root(double number, double n) {
    if (number < 0 && fmod(n, 2) == 0) {  // Even root of negative
        printf(COLOR_YELLOW
               "Warning: Cannot calculate even root of a negative number "
               "(complex result).\n" COLOR_RESET);
        return NAN;
    }
    if (n == 0) {
        printf(COLOR_RED "Error: Root degree cannot be zero.\n" COLOR_RESET);
        return NAN;
    }
    return pow(number, 1.0 / n);
}

double log_base10(double a) {
    if (a <= 0) {
        printf(COLOR_RED
               "Error: Logarithm undefined for zero or negative "
               "numbers.\n" COLOR_RESET);
        return NAN;
    }
    return log10(a);
}

double natural_log(double a) {
    if (a <= 0) {
        printf(COLOR_RED
               "Error: Natural log undefined for zero or negative "
               "numbers.\n" COLOR_RESET);
        return NAN;
    }
    return log(a);
}

double sine(double a) { return sin(a); }
double cosine(double a) { return cos(a); }
double tangent(double a) { return tan(a); }

double power_function(double base, double exponent) {
    if (base == 0 && exponent < 0) {
        printf(COLOR_RED
               "Error: Cannot raise zero to a negative power (division by "
               "zero).\n" COLOR_RESET);
        return NAN;
    }
    if (base < 0 && (exponent != floor(exponent))) {
        printf(COLOR_YELLOW
               "Warning: Cannot raise negative number to non-integer power "
               "(complex result).\n" COLOR_RESET);
        return NAN;
    }
    return pow(base, exponent);
}

double degrees_to_radians(double degrees) { return degrees * M_PI / 180.0; }

void handle_choice(int choice) {
    double num1 = 0, num2 = 0, result = 0;

    switch (choice) {
        case 1:
        case 2:
        case 3:
        case 4:
            num1 = get_number("Enter first number: ");
            printf("\x1b[1A\x1b[0J");
            num2 = get_number("Enter second number: ");
            printf("\x1b[1A\x1b[0J");
            break;
        case 5:
            num1 = get_number("Enter the desired number: ");
            printf("\x1b[1A\x1b[0J");
            num2 = get_number("Enter the root degree: ");
            printf("\x1b[1A\x1b[0J");
            break;
        case 6:
        case 7:
            num1 = get_number("Enter the desired number: ");
            printf("\x1b[1A\x1b[0J");
            break;
        case 8:
        case 9:
        case 10:
            num1 = get_number("Enter angle (in degrees): ");
            printf("\x1b[1A\x1b[0J");
            break;
        case 11:
            num1 = get_number("Enter the base number: ");
            printf("\x1b[1A\x1b[0J");
            num2 = get_number("Enter the exponent (power): ");
            printf("\x1b[1A\x1b[0J");
            break;
        default:
            return;
    }

    switch (choice) {
        case 1:
            result = add(num1, num2);
            break;
        case 2:
            result = subtract(num1, num2);
            break;
        case 3:
            result = multiply(num1, num2);
            break;
        case 4:
            result = divide(num1, num2);
            break;
        case 5:
            result = root(num1, num2);
            break;
        case 6:
            result = log_base10(num1);
            break;
        case 7:
            result = natural_log(num1);
            break;
        case 8:
            result = sine(degrees_to_radians(num1));
            break;
        case 9:
            result = cosine(degrees_to_radians(num1));
            break;
        case 10:
            result = tangent(degrees_to_radians(num1));
            break;
        case 11:
            result = power_function(num1, num2);
            break;
    }

    // Print result only if it's a valid number
    if (!isnan(result)) {
        printf(COLOR_GREEN);  // Set color to green
        switch (choice) {
            case 1:
                printf("The sum of %g and %g is: %g\n", num1, num2, result);
                break;
            case 2:
                printf("The result of %g - %g is: %g\n", num1, num2, result);
                break;
            case 3:
                printf("The product of %g and %g is: %g\n", num1, num2, result);
                break;
            case 4:
                printf("The quotient of %g and %g is: %g\n", num1, num2,
                       result);
                break;
            case 5:
                printf("The %g root of %g is: %g\n", num2, num1, result);
                break;
            case 6:
                printf("The logarithm base 10 of %g is: %g\n", num1, result);
                break;
            case 7:
                printf("The natural logarithm of %g is: %g\n", num1, result);
                break;
            case 8:
                printf("The sine of %g degrees is: %g\n", num1, result);
                break;
            case 9:
                printf("The cosine of %g degrees is: %g\n", num1, result);
                break;
            case 10:
                printf("The tangent of %g degrees is: %g\n", num1, result);
                break;
            case 11:
                printf("The result of %g raised to the power of %g is: %g\n",
                       num1, num2, result);
                break;
        }
        printf(COLOR_RESET);  // Reset color
    }
}

double get_number(const char prompt[]) {
    double number;
    char buffer[100];
    bool success = false;

    while (!success) {
        printf("\r\033[2K%s", prompt);
        fflush(stdout);
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;
        if (sscanf(buffer, "%lf", &number) == 1) {
            success = true;
        } else {
            printf("\x1b[1A\x1b[1K");
        }
    }
    return number;
}

bool ask_continue(void) {
    char buffer[100], ch;
    bool valid = false;
    while (!valid) {
        printf("Do you want to continue [y/n]: ");
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;
        if (sscanf(buffer, " %c", &ch) == 1) {
            if (ch == 'y' || ch == 'n' || ch == 'Y' || ch == 'N') {
                valid = true;
            } else {
                printf("\x1b[1A\x1b[0J");
            }
        }
    }
    if (ch == 'n' || ch == 'N') {
        printf("\x1b[1A\x1b[0J");
        return false;
    }
    return true;
}