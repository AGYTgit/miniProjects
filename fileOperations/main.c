#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 256
#define MAX_NAME_LENGTH 64

int write_person(const char* name, int age, const char* filename) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file for writing");
        return 1;
    }
    fprintf(file, "%s %d\n", name, age);
    fclose(file);
    printf("Person '%s' added to the file.\n", name);
    return 0;
}

int display_people(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return 1;
    }
    char line[MAX_LINE_LENGTH];
    printf("Contents of the file:\n");
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
    return 0;
}

bool find_person(const char* name, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return false;
    }
    char line[MAX_LINE_LENGTH];
    bool found = false;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char first_name[MAX_NAME_LENGTH];
        char last_name[MAX_NAME_LENGTH];
        int age;
        char* token;
        char* rest_of_line;

        token = strtok_r(line, " ", &rest_of_line);
        if (token == NULL) continue;
        strcpy(first_name, token);

        token = strtok_r(NULL, " ", &rest_of_line);
        if (token == NULL) continue;

        if (isdigit(*token)) {
            sscanf(token, "%d", &age);
            if (strcmp(first_name, name) == 0) {
                printf("Found person: %s (%d years old)\n", first_name, age);
                found = true;
            }
            continue;
        } else {
            strcpy(last_name, token);
            token = strtok_r(NULL, " ", &rest_of_line);
            if (token == NULL || sscanf(token, "%d", &age) != 1) {
                age = -1;
            }

            char full_name[MAX_NAME_LENGTH * 2];
            snprintf(full_name, sizeof(full_name), "%s %s", first_name, last_name);
            if (strcmp(full_name, name) == 0) {
                printf("Found person: %s (%d years old)\n", full_name, age);
                found = true;
                continue;
            }

            if (strcmp(first_name, name) == 0) {
                printf("Found person: %s %s ", first_name, last_name);
                if (age != -1) printf("(%d years old)\n", age);
                else printf("(Age not available)\n");
                found = true;
                continue;
            }

            if (strcmp(last_name, name) == 0) {
                printf("Found person: %s %s ", first_name, last_name);
                if (age != -1) printf("(%d years old)\n", age);
                else printf("(Age not available)\n");
                found = true;
                continue;
            }
        }
    }

    fclose(file);

    if (!found) {
        printf("Person '%s' not found in the file.\n", name);
    }
    return found;
}

int main(int argc, char** argv) {
    char* filename;

    if (argc > 1) {
        filename = argv[1];
        printf("Using filename: %s\n", filename);
    } else {
        filename = "data.txt";
        printf("No filename provided. Using default filename: %s\n", filename);
    }

    int mode;

    while (true) {
        printf("Choose mode:\n");
        printf("1 - Write new data\n");
        printf("2 - Search the file\n");
        printf("3 - Exit\n");
        scanf("%d", &mode);
        getchar();

        if (mode == 3) {
            break;
        } else if (mode == 1) {
            char name[MAX_NAME_LENGTH];
            int age;

            printf("Enter name (or leave blank to finish):\n");
            while (fgets(name, MAX_NAME_LENGTH, stdin) != NULL && strcmp(name, "\n") != 0) {
                name[strcspn(name, "\n")] = 0;
                printf("Enter age:\n");
                while (scanf("%d", &age) != 1) {
                    printf("Invalid input. Please enter an integer for age: ");
                    while (getchar() != '\n');
                }
                getchar();
                write_person(name, age, filename);
                printf("Enter next name (or 'end' to finish):\n");
            }
        } else if (mode == 2) {
            char name[MAX_NAME_LENGTH];
            printf("Enter name to search for:\n");
            fgets(name, MAX_NAME_LENGTH, stdin);
            name[strcspn(name, "\n")] = 0;
            find_person(name, filename);
        } else {
            printf("Invalid mode selection.\n");
        }
    }

    return 0;
}
