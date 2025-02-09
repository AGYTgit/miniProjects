#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

long string_to_long(const char* str) {
    char* endptr;
    return strtol(str, &endptr, 10);
}

int compare_strings(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    bool str1_is_num = true;
    bool str1_has_num = false;
    int str1_num_pos = -1;
    for (size_t i = 0; i < len1; i++) {
        if (!isdigit(str1[i])) {
            str1_is_num = false;
        } else {
            str1_has_num = true;
            if (str1_num_pos == -1) str1_num_pos = i;
        }
    }

    bool str2_is_num = true;
    bool str2_has_num = false;
    int str2_num_pos = -1;
    for (size_t i = 0; i < len2; i++) {
        if (!isdigit(str2[i])) {
            str2_is_num = false;
        } else {
            str2_has_num = true;
            if (str2_num_pos == -1) str2_num_pos = i;
        }
    }

    if (!str1_has_num && !str2_has_num) {
        if (len1 != len2) return len1 - len2;
        return strcmp(str1, str2);
    }

    if (str1_has_num && str2_has_num) {
        if (!str1_is_num && !str2_is_num) {
            return str2_num_pos - str1_num_pos;
        } else if (!str1_is_num && str2_is_num) {
            return -1;
        } else if (str1_is_num && !str2_is_num) {
            return 1;
        } else {
            long num1 = string_to_long(str1);
            long num2 = string_to_long(str2);
            return num1 < num2 ? -1 : (num1 > num2 ? 1 : 0);
        }
    }

    if (str1_has_num) {
        return 1;
    } else {
        return -1;
    }

    return 0;
}

int main() {
    int n;

    printf("Enter the number of strings: ");
    scanf("%d", &n);
    getchar();

    char** strings = (char**)malloc(n * sizeof(char*));
    if (strings == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    printf("Enter the strings:\n");
    for (int i = 0; i < n; i++) {
        char buffer[100];
        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = 0;

        strings[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        if (strings[i] == NULL) {
            perror("Memory allocation failed");
            for (int j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return 1;
        }
        strcpy(strings[i], buffer);
    }

    qsort(strings, n, sizeof(char*), compare_strings);

    printf("Sorted strings:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", strings[i]);
    }

    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}
