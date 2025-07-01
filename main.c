#include <math.h>
#include <stdio.h>

// function prototypes
void print_choices(void);
int get_choice(void);
void show_choice(int);
float add(float, float);
float difference(float, float);
float product(float, float);
float quotient(float, float);
float root(float);
void handle_choice(int, float, float);

// function to print the choices of operations
void print_choices(void) {
    printf("Choose an operation : \n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Root\n");
    printf("6. Exit\n");
    printf("Enter your choice (1-6): ");
}

// function to get the user's choice of operation
int get_choice(void) {
    int choice;

    do {
        // Printing the choices of operations.
        print_choices();
        scanf("%d", &choice);

        // If the choice is valid (between 1 and 6), break the loop.
        if (choice >= 1 && choice <= 6) break;

        // If the choice is invalid, prompt the user again.
        printf("Invalid choice. Please select a valid operation.\n");

        // Printing a separator for better readability.
        printf("--------------------------------------------------\n");
        printf("\n");
    } while (choice < 1 || choice > 6);

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
            printf("You chose Square Root\n");
            break;
        }
        case 6: {
            printf("You chose to Exit the calculator.\n");
            break;
        }
    }
}

// function to add two float numbers
float add(float a, float b) { return a + b; }

// function to find the difference between two numbers
float difference(float a, float b) { return fabs(a - b); }

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
//function to find the square root of a number
float root(float a)
{
    if(a<0)
    {
        printf("Error: Cannot find the square root of a negative number.\n");
        return 0;
    }
    return sqrt(a);
}

void handle_choice(int choice, float num1, float num2) {
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
    }
}

int main(void) {
    // printing the welcome message.
    printf("Welcome to the Looping Calculator!\n");
    printf("--------------------------------------------------\n");
    printf("\n");

    int choice;

    // Taking input from the user.
    float num1, num2;

    while (1) {
        // Getting the choice from the user.
        choice = get_choice();
        
        // Displaying the user's choice.
        printf("\n");
        show_choice(choice);
        if (choice == 6) break;
        if(choice==5)
        {
            //only one number needed for square root operation
            printf("Enter a Number: ");
            scanf("%f",&num1);
            handle_choice(choice, num1, 0);

        }
        else
        {// Prompting the user to enter two numbers.
        printf("Enter first number: ");
        scanf("%f",&num1);
        printf("Enter second number: ");
        scanf("%f", &num2);

        // handling the choice of operations.
        handle_choice(choice, num1, num2);
        }
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