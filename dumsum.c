#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t dumsum(FILE *f)
{
    uint32_t sum = 0;
    int byte;

    while ((byte = fgetc(f)) != EOF)
    {
        sum += byte;
    }

    return sum;
}

void print_sum(uint32_t sum, int bits, bool decimal, const char *filename)
{
    if (decimal)
    {
        printf("%u", sum);
    }
    else
    {
        if (bits == 8)
        {
            printf("%02x       ", sum);
        }
        else if (bits == 16)
        {
            printf("%04x     ", sum);
        }
        else
        {
            printf("%08x ", sum);
        }
    }
    
    if (filename)
    {
        printf("%s", filename);
    }
    printf("\n");
}

void print_help(const char *prog)
{
    printf("Usage: %s [options] [files...]\n", prog);
    printf("Options:\n");
    printf("  -v, --verbose         Show file names\n");
    printf("  -d, --decimal         Print checksum in decimal\n");
    printf("  -b, --bits <8|16|32>  Checksum bit width/modulus (default: 8)\n");
    printf("  -h, --help            Show this message and exit\n");
    printf("  [files...]            Files to checksum. If no files are provided, stdin is used.\n");
}

int main(int argc, char *argv[])
{
    int opt;
    int bits = 8;

    struct option long_options[] =
    {
        {"verbose", no_argument, NULL, 'v'},
        {"decimal", no_argument, NULL, 'd'},
        {"bits", required_argument, NULL, 'b'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
    };

    bool verbose = false;
    bool decimal = false;

    while ((opt = getopt_long(argc, argv, "vdhb:", long_options, NULL)) != -1)
    {
        switch (opt)
        {
            case 'v':
                verbose = true;
                break;

            case 'd':
                decimal = true;
                break;

            case 'b':
                bits = atoi(optarg);
                if (bits != 8 && bits != 16 && bits != 32)
                {
                    fprintf(stderr, "Invalid bit width: %s (use 8, 16, or 32)\n", optarg);
                    return 1;
                }
                break;

            case 'h':
                print_help(argv[0]);
                return 0;

            default:
                fprintf(stderr, "Usage: %s [-v] [-d] [-b <8|16|32>] [-h]\n", argv[0]);
                return 1;
        }
    }

    uint32_t mask = (bits == 32) ? 0xFFFFFFFF : (1U << bits) - 1;
    FILE *f = stdin;

    if (optind >= argc)
    {
        uint32_t sum = dumsum(f) & mask;
        print_sum(sum, bits, decimal, NULL);
    }
    else
    {
        for (int i = optind; i < argc; i++)
        {
            f = fopen(argv[i], "rb");

            if (!f)
            {
                perror(argv[i]);
                continue;
            }

            uint32_t sum = dumsum(f) & mask;
            fclose(f);

            print_sum(sum, bits, decimal, verbose ? argv[i] : NULL);
        }
    }

    return 0;
}

