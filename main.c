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

// main function
int main(void) {
    int choice;
    char ch;
    print_welcome();

    // Getting the choice from the user.
    while (true) {
        choice = get_choice();
        if (choice == 8) break;

        // Displaying the user's choice.
        show_choice(choice);

        // handling the choice of operations.
        handle_choice(choice);

        // asking the user whether to continue or not
        printf("\nDo you want to continue [y/n]: ");
        scanf(" %c", &ch);
        while (ch != 'y' && ch != 'n' && ch != 'Y' && ch != 'N') {
            printf("Invalid choice. Do you want to continue [Yes/No]: ");
            scanf(" %c", &ch);
        }

        if (ch == 'y' || ch == 'y') {
            print_welcome();
        } else {
            printf("\x1b[1A\x1b[0K");
            break;
        }
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
    printf("Enter your choice (1-8): ");
}

// function to get the user's choice of operation
int get_choice(void) {
    int choice = 0;

    // Printing the choices of operations.
    print_choices();
    scanf("%d", &choice);

    // If the choice is invalid (not between 1 and 8), keep the loop.
    while (choice < 1 || 8 < choice) {
        // clearing the whole line
        printf("\x1b[1A\x1b[1K");
        // If the choice is invalid, prompt the user again.
        printf("Invalid choice. Please select a valid operation: ");
        scanf("%d", &choice);
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

    // Prompting the user to enter two numbers.
    if (choice <= 4) {
        printf("Enter first number: ");
        scanf("%lf", &num1);
        printf("Enter second number: ");
        scanf("%lf", &num2);
    } else if (choice >= 5 && choice <= 7) {
        printf("Enter the desired number: ");
        scanf("%lf", &num1);
    }

    switch (choice) {
        case 1: {
            r = add(num1, num2);
            printf("The sum is: %g\n", r);
            break;
        }

        case 2: {
            r = substract(num1, num2);
            printf("The difference is: %g\n", r);
            break;
        }

        case 3: {
            r = multiply(num1, num2);
            printf("The product is: %g\n", r);
            break;
        }

        case 4: {
            r = devide(num1, num2);
            printf("The quotient is: %g\n", r);
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
