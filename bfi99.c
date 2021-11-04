/*
    Brainfuck intrepeter BFI99.
    Copyright (c) 2021 Nathan Archer (pheianox)
    License: https://github.com/pheianox/bfi99/blob/main/LICENSE.md
*/

#include "stdio.h"
#include "stdlib.h"
#define MEMSIZE 50
#define STACKSIZE 50


int main(int argc, char **argv)
{
    if (2 > argc)
    {
        printf("\nERROR: Please, provide the interpetation target.\n\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if (NULL == fp)
    {
        printf("\nERROR: Couldn't open target file.\n\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    size_t fl = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (0 >= fl)
    {
        printf("\nERROR: Target file is empty.\n\n");
        return 1;
    }

    size_t bl = fl + 1;
    char *bp = malloc(bl * sizeof(char));
    int bi = 0;

    if (NULL == bp)
    {
        printf("\nERROR: Memory allocation failed.\n\n");
        return 1;
    }

    fread(bp, 1, fl, fp);
    bp[fl] = '\0';
    fclose(fp);

    char mp[MEMSIZE] = {0};
    int mi = 0;

    char sp[STACKSIZE] = {0};
    int si = 0;

    while (bi < bl)
    {
        switch (bp[bi])
        {
            case '\0':
            {
                // debugger
                for (int i = 0; i < MEMSIZE; i++) {
                    printf("\tmp[%d] = %d", i, mp[i]);
                }

                return 1;
            }

            case '>':
            {
                ++mi;
                ++bi;
                continue;
            }

            case '<':
            {
                --mi;
                ++bi;
                continue;
            }

            case '+':
            {
                mp[mi] = (mp[mi] + 1) % 256;
                ++bi;
                continue;
            }

            case '-': 
            {
                --mp[mi];
                
                if (mp[mi] < 0) mp[mi] = 255;

                ++bi;
                continue;
            }

            case '.':
            {
                putchar(mp[mi]);
                ++bi;
                continue;
            }

            case ',':
            {
                mp[mi] = getchar();
                ++bi;
                continue;
            }

            case '[':
            {
                sp[si] = bi;
                ++si;
                ++bi;
                continue;
            }

            case ']':
            {
                bi = (0 == mp[mi])
                   ? bi + 1
                   : sp[--si];

                continue;
            }

            default:
            {
                continue;
            }
        }
    }

    return 0;
}
