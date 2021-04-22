/*
 * CT30A3370 Käyttöjärjestelmät ja systeemiohjelmointi
 * Project 2: Unix Utilities
 * Creator: Ville Felin
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define True 1


int main(int argc, char *argv[]) {

    FILE *input;
    int i;
    int j;

    //no files in arguments
    if (argc == 1) {

        printf("my-unzip: file1 [file2 ...]\n");

        exit(1);

    }

    //allocating memory for the characters and integers
    char *charBuffer = malloc(sizeof(char));
    if (charBuffer == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    int *intBuffer = malloc(sizeof(int));
    if (intBuffer == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    //Going through all of the arguments
    for (i = 1; i < argc; i++){
        if ((input = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "my-grep: cannot open file\n");
            exit(1);
        }

        //going through the whole file one int&char-pair at a tine
        while (True) {

            //getting the integer
            if ((fread(intBuffer, sizeof(int), 1, input)) == 0) break;

            //getting the character
            fread(charBuffer, sizeof(char), 1, input);

            //printing the amount of characters packed
            for (j = 1; j <= intBuffer[0]; j++) fprintf(stdout, "%c", charBuffer[0]);

        }

        fclose(input);

    }

    free(charBuffer);
    free(intBuffer);
    return 0;

}

