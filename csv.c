#include <stdio.h>
#include <stdlib.h>

FILE *get_csv(char *filename) {
    FILE *input;
    if ((input = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Cannot open %s", filename);
        exit(1);
    }

    return input;
}

void main(int argc, char *argv[]) {
    FILE *test = get_csv(argv[1]);
    char c;
    while (c!=EOF) {
       c = getc(test);
       printf("%c", c);
    }
    printf("\n");
    fclose(test);
}
