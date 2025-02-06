#include <stdio.h>

int main() {
    int max;
    while (1) {
        printf("Enter a number: ");

        if (scanf(" %d", &max) != 1) {
            fprintf(stderr, "Invalid input. Please enter an integer\n");
            while (getchar() != '\n');
            continue;
        }

        if (max > 92) {
            printf("Numbers above 92 are not supported, printting first 92 numbers: \n");
            max = 92;
        }

        printf("%d", 0);
        unsigned long long num1 = 0, num2 = 1, temp;
        for (int i = 0; i < max - 1; i++) {
            if ((num2 % 2) == 0) {
                printf(", %lld", num2);
            }
            temp = num2;
            num2 += num1;
            num1 = temp;
        }
        printf("\n");
    }

    return 0;
}
