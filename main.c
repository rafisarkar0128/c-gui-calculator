#include <math.h>
#include <stdbool.h>
#include <stdio.h>

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
    printf("\x1b[31mExiting the calculator. Goodbye!\n\x1b[0m\n");
    return 0;
}

void print_welcome(void) {
    printf("\x1b[2J\x1b[H");
    printf("\x1b[38;5;82mWelcome to the Looping Calculator!\x1b[0m\n");
    printf("--------------------------------------------------\n\n");
}

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
            printf("\x1b[1A\x1b[0J");
        }
    }
    printf("\x1b[14A\x1b[0J");
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
        printf("Error: Cannot divide by zero.\n");
        return 0;
    }
    return a / b;
}
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
double degrees_to_radians(double degrees) { return degrees * M_PI / 180.0; }

void handle_choice(int choice) {
    double num1 = 0, num2 = 0, result = 0;

    switch (choice) {
        case 1:  // Addition
        case 2:  // Subtraction
        case 3:  // Multiplication
        case 4:  // Division
            num1 = get_number("Enter first number: ");
            printf("\x1b[1A\x1b[0J");
            num2 = get_number("Enter second number: ");
            printf("\x1b[1A\x1b[0J");
            break;
        case 5:  // Root
            num1 = get_number("Enter the desired number: ");
            printf("\x1b[1A\x1b[0J");
            num2 = get_number("Enter the root degree: ");
            printf("\x1b[1A\x1b[0J");
            break;
        case 6:  // Log base 10
        case 7:  // Natural log
            num1 = get_number("Enter the desired number: ");
            printf("\x1b[1A\x1b[0J");
            break;
        case 8:   // Sine
        case 9:   // Cosine
        case 10:  // Tangent
            num1 = get_number("Enter angle (in degrees): ");
            printf("\x1b[1A\x1b[0J");
            break;
        case 11:  // Power
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
            printf("The sum of %g and %g is: %g\n", num1, num2, result);
            break;
        case 2:
            result = subtract(num1, num2);
            printf("The result of %g - %g is: %g\n", num1, num2, result);
            break;
        case 3:
            result = multiply(num1, num2);
            printf("The product of %g and %g is: %g\n", num1, num2, result);
            break;
        case 4:
            result = divide(num1, num2);
            printf("The quotient of %g and %g is: %g\n", num1, num2, result);
            break;
        case 5:
            result = root(num1, num2);
            printf("The %g root of %g is: %g\n", num2, num1, result);
            break;
        case 6:
            result = log_base10(num1);
            printf("The logarithm base 10 of %g is: %g\n", num1, result);
            break;
        case 7:
            result = natural_log(num1);
            printf("The natural logarithm of %g is: %g\n", num1, result);
            break;
        case 8:
            result = sine(degrees_to_radians(num1));
            printf("The sine of %g degrees is: %g\n", num1, result);
            break;
        case 9:
            result = cosine(degrees_to_radians(num1));
            printf("The cosine of %g degrees is: %g\n", num1, result);
            break;
        case 10:
            result = tangent(degrees_to_radians(num1));
            printf("The tangent of %g degrees is: %g\n", num1, result);
            break;
        case 11:
            result = power_function(num1, num2);
            printf("The result of %g raised to the power of %g is: %g\n", num1,
                   num2, result);
            break;
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