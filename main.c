#include <math.h>
#include <stdio.h>

// ALTERNATIVE: Define M_PI manually if not available
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// function prototypes
void print_choices(void);
int get_choice(void);
void show_choice(int);
float add(float, float);
float difference(float, float);
float product(float, float);
float quotient(float, float);
float root(float);
float log_base10(float a);
float natural_log(float a);
float sine(float a);
float cosine(float a);
float tangent(float a);
void handle_choice(int);

// main function
int main(void) {
    // printing the welcome message.
    printf("Welcome to the Looping Calculator!\n");
    printf("--------------------------------------------------\n");
    printf("\n");

    int choice;

    while (1) {

        // Getting the choice from the user.
        choice = get_choice();
        if (choice == 11) break;

        // Displaying the user's choice.
        printf("\n");
        show_choice(choice);

        // handling the choice of operations.
        handle_choice(choice);

        // Printing a separator for better readability.
        printf("--------------------------------------------------\n");
        printf("\n");
    }

    // Exiting the calculator.
    printf("\n");
    printf("You chose to exit the calculator.\n");
    printf("Exiting the calculator. Goodbye!\n");
    printf("--------------------------------------------------\n");
    return 0;
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
    printf("8. sine(sin)\n");
    printf("9. cosine(cos)\n");
    printf("10. tangent(tan)\n");
    printf("11. Exit\n");
    printf("Enter your choice (1-11): ");
}

// function to get the user's choice of operation
int get_choice(void) {
    int choice;

    do {
        // Printing the choices of operations.
        print_choices();
        scanf("%d", &choice);

        // If the choice is valid (between 1 and 8), break the loop.
        if (choice >= 1 && choice <= 11) break;

        // If the choice is invalid, prompt the user again.
        printf("Invalid choice. Please select a valid operation.\n");

        // Printing a separator for better readability.
        printf("--------------------------------------------------\n");
        printf("\n");
    } while (choice < 1 || choice > 8);

    return choice;
}

// function to display the user's choice of operation
void show_choice(int choice) {
    switch (choice) {
        case 1: {
            printf("You chose Addition.\n");
            break;
        }

        case 2: {
            printf("You chose Subtraction.\n");
            break;
        }

        case 3: {
            printf("You chose Multiplication.\n");
            break;
        }

        case 4: {
            printf("You chose Division.\n");
            break;
        }

        case 5: {
            printf("You chose Square Root.\n");
            break;
        }

        case 6: {
            printf("You chose Log (Base 10).\n");
            break;
        }

        case 7: {
            printf("You chose Natural Log (ln).\n");
            break;
        }

        case 8: {
            printf("You chose Sine (sin).\n");
            break;
        }

        case 9: {
            printf("You chose Cosine (cos).\n");
            break;
        }

        case 10: {
            printf("You chose Tangent (tan).\n");
            break;
        }

        case 11: {
            printf("You chose to Exit the calculator.\n");
            break;
        }
    }
}

// function to add two float numbers
float add(float a, float b) { return a + b; }

// function to find the difference between two numbers
float difference(float a, float b) { return a - b; }

// function to find the product of two numbers
float product(float a, float b) { return a * b; }

// function to find the quotient of two numbers
float quotient(float a, float b) {
    if (b == 0) {
        printf("Error: Cannot divide by zero.\n");
        return 0;
    }

    return a / b;
}

// function to find the square root of a number
float root(float a) {
    if (a < 0) {
        printf("Error: Cannot find the square root of a negative number.\n");
        return 0;
    }

    return sqrt(a);
}

// function to calculate logarithm base 10 and natural logarithm
float log_base10(float a) {
    if (a <= 0) {
        printf("Error: Logarithm undefined for zero or negative numbers.\n");
        return 0;
    }
    return log10(a);
}

float natural_log(float a) {
    if (a <= 0) {
        printf("Error: Natural log undefined for zero or negative numbers.\n");
        return 0;
    }
    return log(a);
}

// function to calculate sine of an angle (input in degrees)
float sine(float a) {
    // Convert degrees to radians for calculation
    float radians = a * M_PI / 180.0;
    return sin(radians);
}

// function to calculate cosine of an angle (input in degrees)
float cosine(float a) {
    // Convert degrees to radians for calculation
    float radians = a * M_PI / 180.0;
    return cos(radians);
}

// function to calculate tangent of an angle (input in degrees)
float tangent(float a) {
    // Convert degrees to radians for calculation
    float radians = a * M_PI / 180.0;

    // Check for values where tangent is undefined (90°, 270°, etc.)
    float normalized = fmod(a, 180.0);
    if (fabs(normalized - 90.0) < 1e-6 || fabs(normalized + 90.0) < 1e-6) {
        printf("Error: Tangent is undefined for %.2f degrees.\n", a);
        return 0;
    }
    return tan(radians);
}

void handle_choice(int choice) {
    // Taking input from the user.
    float num1, num2;

    // Prompting the user to enter two numbers.
    if (choice <= 4) {
        printf("Enter first number: ");
        scanf("%f", &num1);
        printf("Enter second number: ");
        scanf("%f", &num2);
    } else if (choice >= 5 && choice <= 10) {
        printf("Enter the desired number: ");
        scanf("%f", &num1);
    }

    switch (choice) {
        case 1: {
            printf("The sum is: %.2f\n", add(num1, num2));
            break;
        }

        case 2: {
            printf("The difference is: %.2f\n", difference(num1, num2));
            break;
        }

        case 3: {
            printf("The product is: %.2f\n", product(num1, num2));
            break;
        }

        case 4: {
            printf("The quotient is: %.2f\n", quotient(num1, num2));
            break;
        }

        case 5: {
            printf("The square root of %.2f is: %.2f\n", num1, root(num1));
            break;
        }

        case 6: {
            printf("The logarithm base 10 of %.2f is: %.2f\n", num1,
                   log_base10(num1));
            break;
        }

        case 7: {
            printf("The natural logarithm of %.2f is: %.2f\n", num1,
                   natural_log(num1));
            break;
        }
        case 8: {
            printf("The sine of %.2f degrees is: %.4f\n", num1, sine(num1));
            break;
        }
        case 9: {
            printf("The cosine of %.2f degrees is: %.4f\n", num1, cosine(num1));
            break;
        }
        case 10: {
            printf("The tangent of %.2f degrees is: %.4f\n", num1,
                   tangent(num1));
            break;
        }
    }
}
