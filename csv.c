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

        words[i][j+1] = '\0';
    }

    //free(words); 
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
//    printf("Size of values: %d\n", strlen(values));
//    printf("Size of input: %d\n", strlen(input));

    while (i < strlen(input)) {
        values[i] = malloc(sizeof(char *) * 3);

        while (j < strlen(input)) {
            if (input[j] == ',') {
                printf("Splitting along a comma at %d.\n", j);
                i++;
                j++;
                break;
            } else {
                printf("Adding an input to values[%d][%d].\n", i, j);
                values[i][j] = input[j];
                printf("values[%d][%d] = %c\n", i, j, values[i][j]);
                //j++;
            }
            j++;
        }

//        if (input[j] == ',') {
//            printf("Splitting along a comma.\n");
//            j++;
//        } else if (input[i] == '\n') {
//            printf("Reached the end of a line.\n");
//            break;
//        } else {
//            printf("Adding an item to values[%d].\n", i);
/*
            while (j < strlen(input)) {
//                printf("made it through: i = %d, j = %d\n", i, j);
                values[i][j] = input[i];
//                printf("%s\n", values[i]);
                j++;
            }
*/
//            values[i][j] = input[i];
//            i++;
//            j++;
//        }
    }

//    printf("Length of values[0]: %d\n", strlen(values[0]));
//    printf("Length of values[1]: %d\n", strlen(values[1]));
//    printf("Length of values[2]: %d\n", strlen(values[2]));
/*
    i = 0;
    j = 0;

    while (i < strlen(input)) {
        while (j < strlen(*values)) {
            printf("%c", values[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
*/
    printf("values[%d] = %s\n", 0, values[0]);
    printf("values[%d] = %s\n", 1, values[1]);
    printf("values[%d] = %s\n", 2, values[2]);
    printf("values[%d] = %s\n", 3, values[3]);
}

void main(int argc, char *argv[]) {
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
    printf("%s\n", line);

    fclose(test);
}
