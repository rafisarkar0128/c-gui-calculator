#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// function prototypes
void print_welcome(void);
void print_choices(void);
int get_choice(void);
void show_choice(int);
double add(double, double);
double substract(double, double);
double multiply(double, double);
double devide(double, double);
double root(double);
double log_base10(double);
double natural_log(double);
void handle_choice(int);
double get_number(char *);
bool ask_continue(void);

// main function
int main(void) {
    int choice;
    char ch;

    // Getting the choice from the user.
    while (true) {
        // Printing the welcome message.
        print_welcome();

        // Getting the user's choice of operation.
        choice = get_choice();

        // If the user chooses to exit, break the loop.
        if (choice == 8) break;

        // Displaying the user's choice.
        show_choice(choice);

        // handling the choice of operations.
        handle_choice(choice);

        // asking the user whether to continue or not
        if (!ask_continue()) break;
    }

    // Exiting the calculator.
    printf("Exiting the calculator. Goodbye!\n");
    printf("--------------------------------------------------\n");
    return 0;
}

// function to print the welcome message
void print_welcome(void) {
    // clearing the whole screen before initializing
    printf("\x1b[2J]\x1b[H");

    // printing the welcome message.
    printf("Welcome to the Looping Calculator!\n");
    printf("--------------------------------------------------\n\n");
}

// function to print the choices of operations
void print_choices(void) {
    printf("Choose an operation : \n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Square Root\n");
    printf("6. Log (Base 10)\n");
    printf("7. Natural Log (ln)\n");
    printf("8. Exit\n");
}

// function to get the user's choice of operation
int get_choice(void) {
    int choice = 0;
    char buffer[100];
    bool success = false;

    // Printing the choices of operations.
    print_choices();

    // looping until a valid choice is entered
    while (!success) {
        printf("Enter your choice (1-8): ");
        fgets(buffer, sizeof(buffer), stdin);

        // Try to parse an integer
        if (sscanf(buffer, "%d", &choice) == 1) {
            // if the choice is valid, set success to true
            if (choice >= 1 && choice <= 8) success = true;
        } else {
            // clearing the whole line
            printf("\x1b[1A\x1b[0J");
        }
    }

    // clearing the whole line again
    printf("\x1b[10A\x1b[0J");
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
            printf("Square Root");
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
double root(double a) {
    if (a < 0) {
        printf("Error: Cannot find the square root of a negative number.\n");
        return 0;
    }

    return sqrt(a);
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

void handle_choice(int choice) {
    // Taking input from the user.
    double num1, num2, r;
    char prompt[100];
    char *ptr = prompt;

    // Prompting the user to enter two numbers.
    if (choice <= 4) {
        ptr = "Enter first number: ";
        num1 = get_number(ptr);
        // Clear the line after first input
        printf("\x1b[1A\x1b[0J");

        ptr = "Enter second number: ";
        num2 = get_number(ptr);
        // Clear the line after second input
        printf("\x1b[1A\x1b[0J");
    } else if (choice >= 5 && choice <= 7) {
        ptr = "Enter the desired number: ";
        num1 = get_number(ptr);
        // Clear the line after the desired input
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
            r = root(num1);
            printf("The square root of %g is: %g\n", num1, r);
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
    }
}

// function to get a number from the user
double get_number(char *prompt) {
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
