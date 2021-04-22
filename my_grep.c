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
#define False 0

int main(int argc, char *argv[]) {

    FILE *input;
    size_t line;
    int isMatch;
    int i;
    int j;
    int k;

    //No arguments given
    if (argc == 1) {

        printf("my-grep: searchterm [file ...]\n");
        exit(1);

    }

    //buffer for the getline
    size_t bufferSize = 0;
    char *buffer = malloc(bufferSize * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    //Only search term given, using standard input
    if (argc == 2) {
        input = stdin;

        printf("Using standard input, '/exit' to exit\n>");

        while (True) {

            //Using getline() to get the whole line

            line = getline(&buffer, &bufferSize, input);

            //Indicating end of file
            if (line == -1) break;
            if (strcmp("/exit\n", buffer) == 0 ) break;


            //Going through the characters of the line one by one
            for (j = 0; j <= line; j++) {

                //If the character is the same as the first character of the search term
                if (argv[1][0] == buffer[j]) {

                    //Go through the characters of the search term and line until a character differs or the search term is found
                    for (k = 1; k <= strlen(argv[1])-1; k++) {

                        if (argv[1][k] != buffer[j+k]) {
                            break;
                        }

                        if (k == strlen(argv[1])-1) isMatch = True;

                    }
                }

                //If a matching line is found, print it
                if (isMatch == True) {

                    buffer[strcspn(buffer, "\n")] = 0;

                    fprintf(stdout, "%s\n\n", buffer);

                    isMatch = False;
                    break;

                }
            }
        }
    }

    //Going through all of the arguments
    for (i = 2; i < argc; i++){
        if ((input = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "my-grep: cannot open file\n");
            exit(1);
        }

        //Going through the file line by line
        while (True) {

            //Using getline() to get the whole line
            line = getline(&buffer, &bufferSize, input);

            //Indicating end of file
            if (line == -1) break;

            //Going through the characters of the line one by one
            for (j = 0; j <= line; j++) {

                //If the character is the same as the first character of the search term
                if (argv[1][0] == buffer[j]) {

                    //Go through the characters of the search term and line until a character differs or the search term is found
                    for (k = 1; k <= strlen(argv[1])-1; k++) {

                        if (argv[1][k] != buffer[j+k]) {
                            break;
                        }

                        if (k == strlen(argv[1])-1) isMatch = True;

                    }
                }

                //If a matching line is found, print it
                if (isMatch == True) {

                    buffer[strcspn(buffer, "\n")] = 0;

                    fprintf(stdout, "%s\n\n", buffer);

                    isMatch = False;
                    break;

                }
            }
        }

        fclose(input);

    }

    free(buffer);
    return 0;

}


