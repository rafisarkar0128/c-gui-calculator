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

/**
 * =======================================================================
 *                            DATA STRUCTURES
 * =======================================================================
 */

/**
 * Main calculator state - holds GUI widgets and current input
 */
typedef struct {
    GtkWidget *entry;      // Display entry widget
    GString *input;        // Current input string buffer
    char last_error[128];  // Last error message
    bool just_evaluated;   // Flag to clear display on next number input
} CalculatorState;

/**
 * Token types for mathematical expressions
 */
typedef enum {
    TOK_NUMBER,    // Numeric values (integers, decimals, percentages)
    TOK_OPERATOR,  // Mathematical operators (+, -, *, /, ^)
    TOK_LPAREN,    // Left parenthesis (
    TOK_RPAREN,    // Right parenthesis )
    TOK_FUNCTION,  // Mathematical functions (sin, cos, sqrt, etc.)
    TOK_END,       // End of expression
    TOK_INVALID    // Invalid/unrecognized token
} TokenType;

/**
 * Individual token in a mathematical expression
 */
typedef struct {
    TokenType type;    // Type of this token
    double value;      // Numeric value (for TOK_NUMBER)
    char operator;     // Operator character (for TOK_OPERATOR)
    char function[8];  // Function name (for TOK_FUNCTION)
} Token;

/**
 * Lexical analyzer state - tracks position in input string
 */
typedef struct {
    const char *input;  // Input expression string
    size_t position;    // Current parsing position
} Lexer;

/**
 * Dynamic stack for Token objects
 */
typedef struct {
    Token *data;   // Array of tokens
    int top;       // Index of top element (-1 if empty)
    int capacity;  // Current capacity of array
} TokenStack;

/**
 * Dynamic stack for numeric values
 */
typedef struct {
    double *data;  // Array of doubles
    int top;       // Index of top element (-1 if empty)
    int capacity;  // Current capacity of array
} NumberStack;

/**
 * =======================================================================
 *                            UTILITY FUNCTIONS
 * =======================================================================
 */

/**
 * Clear error buffer by setting first character to null terminator
 */
static void clear_error(char *error_buffer, size_t error_size) {
    if (error_buffer && error_size > 0) {
        error_buffer[0] = '\0';
    }
}

/**
 * Check if character is valid for function names (lowercase letters)
 */
static bool is_function_char(char c) { return (c >= 'a' && c <= 'z'); }

/**
 * Skip whitespace characters in input
 */
static void skip_whitespace(Lexer *lexer) {
    while (lexer->input[lexer->position] != '\0' &&
           (lexer->input[lexer->position] == ' ' ||
            lexer->input[lexer->position] == '\t')) {
        lexer->position++;
    }
}

/**
 * Check if operator is right-associative
 * Only exponentiation (^) is right-associative: 2^3^2 = 2^(3^2) = 512, not
 * (2^3)^2 = 64
 */
static bool is_right_associative(char op) { return op == '^'; }

/**
 * =======================================================================
 * EXPRESSION PARSER - TOKENIZER AND SHUNTING YARD ALGORITHM
 * =======================================================================
 */

/**
 * Initialize a token with default values
 */
static void init_token(Token *token) {
    token->type = TOK_END;
    token->value = 0.0;
    token->operator = 0;
    token->function[0] = '\0';
}

/**
 * Extract next token from input string
 * Handles numbers, operators, parentheses, and function names
 */
static Token get_next_token(Lexer *lexer) {
    skip_whitespace(lexer);
    Token token;
    init_token(&token);

    char current = lexer->input[lexer->position];

    // End of input
    if (current == '\0') {
        token.type = TOK_END;
        return token;
    }

    // Parse numbers (including decimals and percentages)
    if ((current >= '0' && current <= '9') || current == '.') {
        char buffer[64];
        size_t buf_index = 0;

        // Extract all digits and decimal points
        while (lexer->input[lexer->position] != '\0' &&
               ((lexer->input[lexer->position] >= '0' &&
                 lexer->input[lexer->position] <= '9') ||
                lexer->input[lexer->position] == '.') &&
               buf_index < sizeof(buffer) - 1) {
            buffer[buf_index++] = lexer->input[lexer->position++];
        }
        buffer[buf_index] = '\0';

        token.type = TOK_NUMBER;
        token.value = strtod(buffer, NULL);

        // Handle percentage suffix
        if (lexer->input[lexer->position] != '\0' &&
            lexer->input[lexer->position] == '%') {
            token.value /= 100.0;
            lexer->position++;
        }
        return token;
    }

    // Parse function names (lowercase letters only)
    if (is_function_char(current)) {
        char buffer[8];
        size_t buf_index = 0;

        while (lexer->input[lexer->position] != '\0' &&
               is_function_char(lexer->input[lexer->position]) &&
               buf_index < sizeof(buffer) - 1) {
            buffer[buf_index++] = lexer->input[lexer->position++];
        }
        buffer[buf_index] = '\0';

        token.type = TOK_FUNCTION;
        strncpy(token.function, buffer, sizeof(token.function) - 1);
        token.function[sizeof(token.function) - 1] =
            '\0';  // Ensure null termination
        return token;
    }

    // Parse operators and parentheses
    lexer->position++;
    switch (current) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            token.type = TOK_OPERATOR;
            token.operator = current;
            return token;
        case '(':
            token.type = TOK_LPAREN;
            return token;
        case ')':
            token.type = TOK_RPAREN;
            return token;
        default:
            token.type = TOK_INVALID;
            return token;
    }
}

/**
 * Get operator precedence for correct evaluation order
 * Higher numbers = higher precedence
 */
static int get_precedence(char op) {
    switch (op) {
        case '^':
            return 4;  // Exponentiation (highest)
        case '*':
        case '/':
            return 3;  // Multiplication and division
        case '+':
        case '-':
            return 2;  // Addition and subtraction
        default:
            return 0;  // Unknown operator
    }
}

/**
 * =======================================================================
 *                 DYNAMIC STACKS FOR EXPRESSION PARSING
 * =======================================================================
 */

/**
 * Initialize a token stack
 */
static void token_stack_init(TokenStack *stack) {
    stack->data = NULL;
    stack->top = -1;
    stack->capacity = 0;
}

/**
 * Initialize a number stack
 */
static void number_stack_init(NumberStack *stack) {
    stack->data = NULL;
    stack->top = -1;
    stack->capacity = 0;
}

/**
 * Push a token onto the stack
 */
static void token_stack_push(TokenStack *stack, Token value) {
    // Expand capacity if needed
    if (stack->top + 1 == stack->capacity) {
        stack->capacity = stack->capacity ? stack->capacity * 2 : 16;
        stack->data = realloc(stack->data, sizeof(Token) * stack->capacity);
    }
    stack->data[++stack->top] = value;
}

/**
 * Push a number onto the stack
 */
static void number_stack_push(NumberStack *stack, double value) {
    // Expand capacity if needed
    if (stack->top + 1 == stack->capacity) {
        stack->capacity = stack->capacity ? stack->capacity * 2 : 16;
        stack->data = realloc(stack->data, sizeof(double) * stack->capacity);
    }
    stack->data[++stack->top] = value;
}

/**
 * Pop a token from the stack
 */
static Token token_stack_pop(TokenStack *stack) {
    return stack->data[stack->top--];
}

/**
 * Pop a number from the stack
 */
static double number_stack_pop(NumberStack *stack) {
    return stack->data[stack->top--];
}

/**
 * Peek at the top token of the stack without removing it
 */
static Token token_stack_peek(TokenStack *stack) {
    return stack->data[stack->top];
}

/**
 * Check if token stack is empty
 */
static bool token_stack_empty(TokenStack *stack) { return stack->top < 0; }

/**
 * Check if number stack is empty
 */
static bool number_stack_empty(NumberStack *stack) { return stack->top < 0; }

/**
 * Free memory used by stacks
 */
static void free_stacks(TokenStack *op_stack, TokenStack *output,
                        NumberStack *numbers) {
    if (op_stack && op_stack->data) free(op_stack->data);
    if (output && output->data) free(output->data);
    if (numbers && numbers->data) free(numbers->data);
}

/**
 * Convert infix expression to Reverse Polish Notation (RPN) using Shunting Yard
 * algorithm This allows proper operator precedence and parentheses handling
 *
 * Example: "3 + 4 * 2" becomes "3 4 2 * +" which evaluates to 11, not 14
 */
static bool convert_to_rpn(const char *expression, TokenStack *output,
                           char *error, size_t error_size) {
    Lexer lexer = {expression, 0};
    TokenStack operator_stack;
    token_stack_init(&operator_stack);
    token_stack_init(output);

    Token previous_token;
    init_token(&previous_token);
    previous_token.type = TOK_INVALID;

    bool success = true;

    while (success) {
        Token current_token = get_next_token(&lexer);

        // Check for invalid tokens
        if (current_token.type == TOK_INVALID) {
            snprintf(error, error_size, "Invalid character in expression");
            success = false;
            break;
        }

        // End of expression
        if (current_token.type == TOK_END) break;

        // Numbers go directly to output
        if (current_token.type == TOK_NUMBER) {
            token_stack_push(output, current_token);
            previous_token = current_token;
            continue;
        }

        // Functions go to operator stack
        if (current_token.type == TOK_FUNCTION) {
            token_stack_push(&operator_stack, current_token);
            previous_token = current_token;
            continue;
        }

        // Handle operators
        if (current_token.type == TOK_OPERATOR) {
            // Handle unary minus: if minus appears at start or after
            // operator/parenthesis/function
            if (current_token.operator == '-' &&
                (previous_token.type == TOK_INVALID ||
                 previous_token.type == TOK_OPERATOR ||
                 previous_token.type == TOK_LPAREN ||
                 previous_token.type == TOK_FUNCTION)) {
                // Convert unary minus to binary subtraction: -x becomes 0-x
                Token zero;
                init_token(&zero);
                zero.type = TOK_NUMBER;
                zero.value = 0.0;
                token_stack_push(output, zero);
            }

            // Process operators according to precedence rules
            while (!token_stack_empty(&operator_stack)) {
                Token top = token_stack_peek(&operator_stack);
                if (top.type == TOK_OPERATOR &&
                    ((get_precedence(top.operator) >
                      get_precedence(current_token.operator)) ||
                     (get_precedence(top.operator) ==
                          get_precedence(current_token.operator) &&
                      !is_right_associative(current_token.operator)))) {
                    token_stack_push(output, token_stack_pop(&operator_stack));
                } else if (top.type == TOK_FUNCTION) {
                    token_stack_push(output, token_stack_pop(&operator_stack));
                } else {
                    break;
                }
            }

            token_stack_push(&operator_stack, current_token);
            previous_token = current_token;
            continue;
        }

        // Left parenthesis
        if (current_token.type == TOK_LPAREN) {
            token_stack_push(&operator_stack, current_token);
            previous_token = current_token;
            continue;
        }

        // Right parenthesis - pop until matching left parenthesis
        if (current_token.type == TOK_RPAREN) {
            bool found_left_paren = false;
            while (!token_stack_empty(&operator_stack)) {
                Token top = token_stack_pop(&operator_stack);
                if (top.type == TOK_LPAREN) {
                    found_left_paren = true;
                    break;
                }
                token_stack_push(output, top);
            }
            if (!found_left_paren) {
                snprintf(error, error_size, "Mismatched parentheses");
                success = false;
                break;
            }

            // If there's a function on top of stack after closing parenthesis,
            // apply it
            if (!token_stack_empty(&operator_stack) &&
                token_stack_peek(&operator_stack).type == TOK_FUNCTION) {
                token_stack_push(output, token_stack_pop(&operator_stack));
            }
            previous_token = current_token;
            continue;
        }
    }

    // Pop remaining operators from stack
    while (success && !token_stack_empty(&operator_stack)) {
        Token top = token_stack_pop(&operator_stack);
        if (top.type == TOK_LPAREN || top.type == TOK_RPAREN) {
            snprintf(error, error_size, "Mismatched parentheses");
            success = false;
            break;
        }
        token_stack_push(output, top);
    }

    // Clean up operator stack
    if (operator_stack.data) {
        free(operator_stack.data);
    }

    return success;
}

/**
 * Apply mathematical operator to two operands
 * Pops two numbers from stack, applies operation, pushes result back
 */
static bool apply_operator(char op, NumberStack *numbers, char *error,
                           size_t error_size) {
    // Need at least two operands for binary operators
    if (numbers->top < 1) {
        snprintf(error, error_size, "Not enough operands for operator");
        return false;
    }

    // Pop operands (note: order matters for non-commutative operations)
    double right = number_stack_pop(numbers);  // Second operand
    double left = number_stack_pop(numbers);   // First operand
    double result = 0.0;
    bool success = true;

    switch (op) {
        case '+':
            result = left + right;
            break;
        case '-':
            result = left - right;
            break;
        case '*':
            result = left * right;
            break;
        case '/':
            // success = safe_divide(left, right, &result, error, error_size);
            break;
        case '^':
            // success = safe_power(left, right, &result, error, error_size);
            break;
        default:
            snprintf(error, error_size, "Unknown operator: %c", op);
            return false;
    }

    if (success) {
        number_stack_push(numbers, result);
    }

    return success;
}

/**
 * Apply mathematical function to one operand
 * Pops one number from stack, applies function, pushes result back
 */
static bool apply_function(const char *function_name, NumberStack *numbers,
                           char *error, size_t error_size) {
    // Need at least one operand for functions
    if (numbers->top < 0) {
        snprintf(error, error_size, "Function '%s' requires an argument",
                 function_name);
        return false;
    }

    double operand = number_stack_pop(numbers);
    double result = 0.0;
    bool success = true;

    // Apply the appropriate mathematical function
    if (strcmp(function_name, "sqrt") == 0) {
        // success = safe_sqrt(operand, &result, error, error_size);
    } else if (strcmp(function_name, "log") == 0) {
        // success = safe_log10(operand, &result, error, error_size);
    } else if (strcmp(function_name, "ln") == 0) {
        // success = safe_ln(operand, &result, error, error_size);
    } else if (strcmp(function_name, "sin") == 0) {
        // result = sin(deg2rad(operand));  // Convert degrees to radians
    } else if (strcmp(function_name, "cos") == 0) {
        // result = cos(deg2rad(operand));  // Convert degrees to radians
    } else if (strcmp(function_name, "tan") == 0) {
        // success = safe_tan_degrees(operand, &result, error, error_size);
    } else {
        snprintf(error, error_size, "Unknown function: %s", function_name);
        return false;
    }

    if (success) {
        number_stack_push(numbers, result);
    }

    return success;
}

/**
 * Main expression evaluator - converts to RPN then evaluates
 * @param expression: Mathematical expression string
 * @param success: Output parameter indicating if evaluation succeeded
 * @param error_buffer: Buffer for error messages
 * @param error_size: Size of error buffer
 * @return: Computed result, or 0 if error occurred
 */
static double evaluate_expression(const char *expression, bool *success,
                                  char *error_buffer, size_t error_size) {
    TokenStack rpn_tokens;
    token_stack_init(&rpn_tokens);
    clear_error(error_buffer, error_size);

    // Convert infix expression to RPN
    bool conversion_success =
        convert_to_rpn(expression, &rpn_tokens, error_buffer, error_size);
    if (!conversion_success) {
        *success = false;
        if (rpn_tokens.data) free(rpn_tokens.data);
        return 0.0;
    }

    // Evaluate RPN expression
    NumberStack evaluation_stack;
    number_stack_init(&evaluation_stack);

    for (int i = 0; i <= rpn_tokens.top; i++) {
        Token token = rpn_tokens.data[i];

        if (token.type == TOK_NUMBER) {
            number_stack_push(&evaluation_stack, token.value);
        } else if (token.type == TOK_OPERATOR) {
            if (!apply_operator(token.operator, &evaluation_stack, error_buffer,
                                error_size)) {
                conversion_success = false;
                break;
            }
        } else if (token.type == TOK_FUNCTION) {
            if (!apply_function(token.function, &evaluation_stack, error_buffer,
                                error_size)) {
                conversion_success = false;
                break;
            }
        }
        // Ignore other token types
    }

    double final_result = 0.0;
    if (conversion_success) {
        // Should have exactly one number left on stack
        if (evaluation_stack.top != 0) {
            snprintf(error_buffer, error_size, "Invalid expression syntax");
            conversion_success = false;
        } else {
            final_result = number_stack_pop(&evaluation_stack);
        }
    }

    // Clean up memory
    if (rpn_tokens.data) free(rpn_tokens.data);
    if (evaluation_stack.data) free(evaluation_stack.data);

    *success = conversion_success;
    return final_result;
}

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
        clear_error(state->last_error, sizeof(state->last_error));
        state->just_evaluated = false;
        update_display(state, "0");
        return;
    }

    // Equals button - evaluate current expression
    if (strcmp(button_label, "=") == 0) {
        bool evaluation_success = false;
        double result =
            evaluate_expression(state->input->str, &evaluation_success,
                                state->last_error, sizeof(state->last_error));

        if (evaluation_success) {
            // Display result and prepare for next calculation
            g_string_printf(state->input, "%g", result);
            update_display(state, state->input->str);
            state->just_evaluated = true;  // Flag to clear on next number input
        } else {
            // Display error message
            update_display(state, "Error");
            state->just_evaluated = true;
        }
        return;
    }

    // Auto-clear behavior: if we just showed a result/error and user enters
    // a number or function, clear the input first to start fresh
    if (state->just_evaluated) {
        bool should_clear =
            (button_label[0] >= '0' && button_label[0] <= '9') ||  // Digit
            strcmp(button_label, ".") == 0 ||   // Decimal point
            is_function_char(button_label[0]);  // Function

        if (should_clear) {
            g_string_set_size(state->input, 0);
            state->just_evaluated = false;
        } else if (strchr("+-*/^()%", button_label[0]) != NULL) {
            // If user enters an operator, keep the result and continue
            // calculation
            state->just_evaluated = false;
        }
    }

    // Handle specific button types
    if (strcmp(button_label, "sqrt") == 0) {
        g_string_append(state->input, "sqrt(");
    } else if (strcmp(button_label, "log") == 0) {
        g_string_append(state->input, "log(");
    } else if (strcmp(button_label, "ln") == 0) {
        g_string_append(state->input, "ln(");
    } else if (strcmp(button_label, "sin") == 0) {
        g_string_append(state->input, "sin(");
    } else if (strcmp(button_label, "cos") == 0) {
        g_string_append(state->input, "cos(");
    } else if (strcmp(button_label, "tan") == 0) {
        g_string_append(state->input, "tan(");
    } else if (strcmp(button_label, "^") == 0) {
        g_string_append(state->input, "^");
    } else if (strcmp(button_label, "⌫") == 0) {
        // Backspace - remove last character
        if (state->input->len > 0) {
            g_string_truncate(state->input, state->input->len - 1);
        }
    } else {
        // For all other buttons (digits, operators, parentheses), append
        // directly
        g_string_append(state->input, button_label);
    }

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

    // Create main vertical container to hold widgets (display, buttons,
    // etc.)
    GtkWidget *main_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(main_container), 15);
    gtk_container_add(GTK_CONTAINER(window), main_container);

    // Create display (entry) to shows current input and results
    state->entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(state->entry), 1.0);  // Right-align
    gtk_editable_set_editable(GTK_EDITABLE(state->entry),
                              FALSE);  // Read-only
    gtk_entry_set_text(GTK_ENTRY(state->entry), "0");
    gtk_widget_set_size_request(state->entry, -1,
                                50);  // Set minimum height
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
    state->just_evaluated = false;
    clear_error(state->last_error, sizeof(state->last_error));

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