#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

typedef double (*Operation)(double, double);

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) {
    if (b == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        exit(EXIT_FAILURE); 
    }
    return a / b;
}

int main() {
    double num1, num2;
    char operator;

    Operation operations[] = {
        ['+'] = add,
        ['-'] = subtract,
        ['*'] = multiply,
        ['/'] = divide
    };

    while (1) {
        printf("Enter two numbers (or 'q' to quit): ");

        char input_str[100];
        if (fgets(input_str, sizeof(input_str), stdin) == NULL) {
            fprintf(stderr, "Error reading input");
            exit(EXIT_FAILURE);
        }

        if (tolower(input_str[0]) == 'q') {
            break;
        }

        if (sscanf(input_str, "%lf %lf", &num1, &num2) != 2) {
            fprintf(stderr, "Invalid input. Please enter numbers or 'q'.\n");
            continue;
        }

        printf("Enter an operator (+, -, *, /) or 'q' to quit: ");
        scanf(" %c", &operator);

        if (tolower(operator) == 'q') {
            break;
        }

        if (operations[operator] != NULL) {
            double result = operations[operator](num1, num2);

            if (result != (int)result) {
                printf("Result: %lf\n", result);
            } else {
                printf("Result: %.0lf\n", result);
            }
        } else {
            fprintf(stderr, "Invalid operator.\n");
        }

        while (getchar() != '\n');
    }

    return 0;
}
