#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define OPTSTR "hb:cdefi:lgo:rx:::sZz"

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, OPTSTR)) != EOF) {
        switch(opt) {
            case 'h':
                printf("AIDE POUR LE PROGRAMME");
                break;
            case 'b':
                printf("-b ENTERED");
                break;
            case 'c':
                printf("-c ENTERED");
                break;
            case 'd':
                printf("-d ENTERED");
                break;
            case 'e':
                printf("-e ENTERED");
                break;
            case 'f':
                printf("-f ENTERED");
                break;
            case 'i':
                printf("-i ENTERED");
                break;
            case 'l':
                printf("-l ENTERED");
                break;
            case 'g':
                printf("-g ENTERED");
                break;
            case 'o':
                printf("-o ENTERED");
                break;
            case 'r':
                printf("-r ENTERED");
                break;
            case 'x':
                printf("-x ENTERED");
                break;
            case 's':
                printf("-s ENTERED");
                break;
            case 'Z':
                printf("-Z ENTERED");
                break;
            case 'z':
                printf("-z ENTERED");
                break;
            default:
                printf("Mauvais argument entré ! \n");
                break;
        }
    }
    return 0;
}
