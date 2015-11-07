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

        for (j=strlen(words[i])-1; j>=0 && words[i][j]=='\n'; j--) {

        }

        words[i][j+1] = '\0';
    }

    //free(words); 
    return words;
}

char *get_next_line(char **lines) {
    static int pos = 0;
    pos++;

    if (pos > sizeof(lines)) {
        printf("Position %d is out of bounds.\n", pos);
        return "0";
    }
    char *next_line = lines[pos-1];
    return next_line;
}

void main(int argc, char *argv[]) {
    FILE *test = open_csv(argv[1]);

    char *line;
    char **words = get_csv_lines(test);

    int i;
    for (i = 0; i < 6; i++) {
        line = get_next_line(words);
        printf("%s\n", line);
    }

    fclose(test);
}
