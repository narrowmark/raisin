#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *open_csv(char *filename) {
    FILE *input;
    if ((input = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(1);
    }

    return input;
}

char **get_csv_lines(FILE *file) {
    int lines = 128;
    int line_length = 100;

    char **words = (char **)malloc(sizeof(char*) * lines);

    int i;
    for (i = 0; 1; i++) {
        int j;

        if (i >= lines) {
            int new_lines = lines * 2;
            words = (char **)realloc(words, sizeof(char*) * new_lines);
            lines = new_lines;
        }

        words[i] = malloc(line_length);

        if (fgets(words[i], line_length - 1, file) == NULL) {
            break;
        }

        for (j = strlen(words[i])-1; j>=0 && words[i][j] == '\n'; j--) {

        }

    }
    return words;
}

char *get_next_line(char **lines) {
    static int pos = 0;

    if (pos > sizeof(lines)) {
        printf("Position %d is out of bounds.\n", pos);
        return "0";
    }

    pos++;
    char *next_line = lines[pos-1];
    return next_line;
}

void parse_line(char *input) {
    char **values = malloc(sizeof(char *) * strlen(input));
    int i = 0;
    int j = 0;

    while (i < strlen(input)) {
        values[i] = malloc(sizeof(char *) * 3);
        int end_of_line = 0;

        while (j < strlen(input)) {
            if (input[j] == ',') {
                printf("Splitting along a comma at %d.\n", j);
                i++;
                j++;
                break;
            } else if (input[j] == '\n') {
                end_of_line = 1;
                break;
            } else {
                printf("Adding an input to values[%d][%d].\n", i, j);
                values[i][j] = input[j];
                printf("values[%d][%d] = %c\n", i, j, values[i][j]);
            }
            j++;
        }

        if (end_of_line == 1) {
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *test = open_csv(argv[1]);

    char *line;
    char **words = get_csv_lines(test);
/*
    int i;
    for (i = 0; i < 5; i++) {
        line = get_next_line(words);
        printf("%s\n", line);
    }
*/
    line = get_next_line(words);
    parse_line(line);
//    printf("%s\n", line);

    fclose(test);

    return 0;
}
