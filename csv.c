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

void get_csv_lines(FILE *file) {
    int lines = 128;
    int line_length = 100;

    char **words = (char **)malloc(sizeof(char*)*lines);

    int i;
    for (i = 0; 1; i++) {
        int j;

        if (i >= lines) {
            int new_lines = lines * 2;
            words = (char **)realloc(words, sizeof(char*)*new_lines);
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

    int j;
    for (j = 0; j < i; j++) {
        printf("%s\n", words[j]);
    }

    free(words);
}

void main(int argc, char *argv[]) {
    FILE *test = open_csv(argv[1]);

    char line[1000];
    get_csv_lines(test);
    //line = get_csv_lines(test);
    //printf("%c\n", line[0]);

    fclose(test);
}
