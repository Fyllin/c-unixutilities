#include <stdio.h>
#include <stdlib.h>

#define True 1


int main(int argc, char *argv[]) {

    FILE *input;
    size_t line;
    int charCount;
    int i;
    int j;
    int k;
    FILE *output = stdout;

    if (argc == 1) {

        printf("my-zip: file1 [file2 ...]\n");

        exit(1);

    }

    //Going through all of the arguments
    for (i = 1; i < argc; i++){

        if ((input = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "my-zip: cannot open file\n");
            exit(1);
        }

        //Going through the file line by line
        while (True) {

            //buffer for the getline
            size_t bufferSize = 0;
            char *buffer = malloc(bufferSize * sizeof(char));
            if (buffer == NULL) {
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }

            //Using getline() to get the whole line
            line = getline(&buffer, &bufferSize, input);

            //Indicating end of file
            if (line == -1) {

                free(buffer);
                break;

            }

            //Going through the characters of the line one by one
            for (j = 0; j <= line;) {

                charCount = 1;

                //counting how many subsequent characters are the same as the first one
                for(k = 1; buffer[j+k] == buffer[j]; k++){
                    charCount++;
                }

                //outputting the compressed characters
                fwrite(&charCount, sizeof(int), 1, output);
                fwrite(&buffer[j], sizeof(char), 1, output);

                //end of the line
                if (buffer[j] == '\n') break;

                //jumping over the consecutive characters
                j = j+k;
            }

            free(buffer);

        }

        fclose(input);

    }

    return 0;

}


