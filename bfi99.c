/*

    Copyright (c) 2021 Nathan Archer (pheianox)

    Brainfuck intrepeter BFI99.
    
*/

#include "stdio.h"
#include "stdlib.h"
#define MEMSIZE 30000

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("\nERROR: Please, provide the interpetation target.\n\n");
        return 1;
    }

    char *path = argv[1];

    FILE *file = fopen(path, "r");

    if (NULL == file)
    {
        printf("\nERROR: Couldn't open target file %s.\n\n", path);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size <= 1)
    {
        printf("\nERROR: Target file is empty.\n\n");
        return 1;
    }

    char *buffer = malloc((file_size + 1) * sizeof(char));

    if (NULL == buffer)
    {
        printf("\nERROR: Couldn't allocate memory for target file.\n\n");
        return 1;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    char *p = calloc(MEMSIZE, sizeof(char));
    int   i = 0;
    int   r = 0;

    for (;;)
    {
        switch (buffer[i])
        {
            case '\0':
            {
                return 1;
            }

            case ' ': 
            case '\n': 
            case '\r': 
            {
                i++;
                continue;
            }
            
            case '>':
            {
                p++;
                i++;
                continue;
            }

            case '<':
            {
                p--;
                i++;
                continue;
            }

            case '+':
            {
                *p = (*p + 1) % 256;
                i++;
                continue;
            }

            case '-': 
            {
                if ((*p)-- < 0) *p = 255;
                i++;
                continue;
            }

            case '.':
            {
                putchar(*p);
                i++;
                continue;
            }

            case ',':
            {
                *p = getchar();
                i++;
                continue;
            }

            case '[':
            {
                r = i;
                i++;
                continue;
            }

            case ']':
            {
                i = (0 == *p) ? i + 1 : r;
                continue;
            }

            default:
            {
                printf("Unexpected character \"%c\"", buffer[i]);
                return 1;
            }
        }
    }

    return 0;
}
