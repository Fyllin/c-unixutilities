#include <stdio.h>
#include <stdlib.h>

#define True 1


int main(int argc, char *argv[]) {

    FILE *input;
    size_t line;
    size_t bufferSize;
    char *buffer;
    
    
    for (int i = 1; i < argc; i++){

        //opening the files in order
        if ((input = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "my-cat: cannot open file\n");
            exit(1);
        }

        //reading the lines
        while (True) {

            //buffer for the getline
            bufferSize = 0;
            buffer = malloc(bufferSize * sizeof(char));
            if (buffer == NULL) {
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }

            //Using getline() to get the whole line
            line = getline(&buffer, &bufferSize, input);

            //Indicating end of file
            if (buffer == NULL) break;
            if (line == -1) break;

            //printing the line
            fprintf(stdout, "%s", buffer);

            free(buffer);

        }

        fclose(input);
        
    }
    
    return 0;
}


