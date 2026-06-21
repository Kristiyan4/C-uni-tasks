#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 80

int my_strlen(const char *s) {
    int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

void my_strcpy(char *dest, const char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int is_separator(char c) {
    return c == ' ' || c == '\t' || c == '.' || c == '!' || c == '?' || c == '\0';
}

int my_strcmp(const char *a, const char *b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++; b++;
    }
    return (*a == '\0' && *b == '\0');
}

int my_strncmp(const char *a, const char *b, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return 0;
        if (a[i] == '\0') break;
    }
    return 1;
}

void reverse_line(char *line) {
    int len = my_strlen(line);
    for (int i = 0; i < len / 2; i++) {
        char tmp = line[i];
        line[i] = line[len - 1 - i];
        line[len - 1 - i] = tmp;
    }
}

void left_align(char *line) {
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t') i++;
    if (i == 0) return;

    int j = 0;
    while (line[i]) {
        line[j++] = line[i++];
    }
    line[j] = '\0';
}

void right_align(char *line) {
    left_align(line); 
    int len = my_strlen(line);
    int spaces = MAX_LEN - len;
    if (spaces <= 0) return;

    for (int i = len; i >= 0; i--) {
        line[i + spaces] = line[i];
    }
    for (int i = 0; i < spaces; i++) {
        line[i] = ' ';
    }
}

int count_words(char *line) {
    int count = 0, in_word = 0;
    for (int i = 0; line[i]; i++) {
        if (!is_separator(line[i]) && !in_word) {
            count++;
            in_word = 1;
        } else if (is_separator(line[i])) {
            in_word = 0;
        }
    }
    return count;
}

int count_all_words(char **lines, int count) {
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += count_words(lines[i]);
    }
    return total;
}

int count_occurrences(char **lines, int count, const char *word) {
    int occurrences = 0;
    int wlen = my_strlen(word);
    for (int i = 0; i < count; i++) {
        char *line = lines[i];
        int len = my_strlen(line);
        for (int j = 0; j <= len - wlen; j++) {
            if ((j == 0 || is_separator(line[j - 1])) &&
                my_strncmp(&line[j], word, wlen) &&
                is_separator(line[j + wlen])) {
                occurrences++;
            }
        }
    }
    return occurrences;
}

void replace_word(char **lines, int count, const char *oldWord, const char *newWord) {
    int oldLen = my_strlen(oldWord);
    int newLen = my_strlen(newWord);
    char temp[200];

    for (int i = 0; i < count; i++) {
        char *src = lines[i];
        int srcLen = my_strlen(src);
        int k = 0;

        for (int j = 0; j < srcLen;) {
            if ((j == 0 || is_separator(src[j - 1])) &&
                my_strncmp(&src[j], oldWord, oldLen) &&
                is_separator(src[j + oldLen])) {
                for (int n = 0; n < newLen; n++) temp[k++] = newWord[n];
                j += oldLen;
            } else {
                temp[k++] = src[j++];
            }
        }
        temp[k] = '\0';
        my_strcpy(lines[i], temp);
    }
}

char **lines = NULL;
int line_count = 0;

void input_lines() {
    char buffer[MAX_LEN + 2];
    while (1) {
        printf("Въведи ред (ENTER за край): ");
        fgets(buffer, sizeof(buffer), stdin);

        int len = my_strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';

        if (buffer[0] == '\0') break;

        lines = realloc(lines, (line_count + 1) * sizeof(char*));
        lines[line_count] = malloc(MAX_LEN + 1);
        my_strcpy(lines[line_count], buffer);
        line_count++;
    }
}

void print_lines() {
    printf("\nТекущи редове:\n");
    for (int i = 0; i < line_count; i++) {
        printf("[%d] %s\n", i, lines[i]);
    }
}

void menu() {
    int choice;
    do {
        printf("\n========== МЕНЮ ==========\n");
        printf("1. Въвеждане на редове\n");
        printf("2. Показване на редове\n");
        printf("3. Брой думи\n");
        printf("4. Ляво подравняване (по № ред)\n");
        printf("5. Дясно подравняване (по № ред)\n");
        printf("6. Обръщане на ред (по № ред)\n");
        printf("7. Търсене на дума\n");
        printf("8. Замяна на дума\n");
        printf("9. Изход\n");
        printf("===========================\n");
        printf("Избор: ");
        scanf("%d", &choice);

        int row;
        char word1[81], word2[81];

        switch (choice) {
            case 1:
                input_lines();
                break;
            case 2:
                print_lines();
                break;
            case 3:
                printf("Общ брой думи: %d\n", count_all_words(lines, line_count));
                break;
            case 4:
                printf("Ред за ляво подравняване: ");
                scanf("%d", &row);
                getchar();
                if (row >= 0 && row < line_count)
                    left_align(lines[row]);
                break;
            case 5:
                printf("Ред за дясно подравняване: ");
                scanf("%d", &row);
                getchar();
                if (row >= 0 && row < line_count)
                    right_align(lines[row]);
                break;
            case 6:
                printf("Ред за обръщане: ");
                scanf("%d", &row);
                getchar();
                if (row >= 0 && row < line_count)
                    reverse_line(lines[row]);
                break;
            case 7:
                printf("Въведи дума за търсене: ");
                scanf("%80s", word1);
                getchar();
                printf("Среща се %d пъти.\n", count_occurrences(lines, line_count, word1));
                break;
            case 8:
                printf("Стара дума: ");
                scanf("%80s", word1);
                printf("Нова дума: ");
                scanf("%80s", word2);
                getchar();
                replace_word(lines, line_count, word1, word2);
                break;
            case 9:
                printf("Изход...\n");
                break;
            default:
                printf("Невалиден избор!\n");
        }
    } while (choice != 9);
}

int main() {
    menu();
    for (int i = 0; i < line_count; i++) free(lines[i]);
    free(lines);
    return 0;
}