#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

unsigned char dumsum(FILE *f)
{
    unsigned char sum = 0;
    int byte;
    while ((byte = fgetc(f)) != EOF) {
        sum += byte;
    }
    return sum;
}

void print_help(char *prog)
{
    printf("Usage: %s [options] [files...]\n", prog);
    printf("Options:\n");
    printf("  -v, --verbose        Show file names\n");
    printf("  -d, --debug          Print checksum in decimal\n");
    printf("  -h, --help           Show this message and exit\n");
    printf("  [files...]           Files to checksum. If no files are provided, stdin is used.\n");
}

int main(int argc, char *argv[]) {
    int opt;
    struct option long_options[] = {
        {"verbose", no_argument, NULL, 'v'},
        {"decimal", no_argument, NULL, 'd'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}  // End marker
    };
    bool verbose = false;
    bool decimal = false;

    while ((opt = getopt_long(argc, argv, "vdh", long_options, NULL)) != -1) {
        switch (opt) {
            case 'v':
                verbose = true;
                break;
            case 'd':
                decimal = true;
                break;
            case 'h':
                print_help(argv[0]);
                return 0;
            default:
                fprintf(stderr, "Usage: %s [-v] [-d] [-h]\n", argv[0]);
                return 1;
        }
    }

    FILE *f = stdin;

    if (argc == 1) {
        unsigned char sum = dumsum(f);
        if (decimal)
        {
            printf("%u\n", sum);
        }
        else
        {
            printf("%02x\n", sum);
        }
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            if (argv[i][0] == '-')
            {
                continue;
            }

            f = fopen(argv[i], "rb");
            if (!f)
            {
                perror(argv[i]);
                continue;
            }
            unsigned char sum = dumsum(f);
            fclose(f);

            if (decimal)
            {
                printf("%-10u  ", sum);
            }
            else
            {
                printf("%02x  ", sum);
            }

            if (verbose)
            {
                printf("%s", argv[i]);
            }
            printf("\n");

        }
    }
            
    return 0;
}

