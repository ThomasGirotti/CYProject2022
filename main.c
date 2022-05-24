#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define OPTSTR "hb:cdefi:lgo:rx:sZz"

int main(int argc, char *argv[]) {

//Déclaration des variables
    int opt; 
    int binaryseuil; 
    int largeur; 
    int hauteur; 
    int epaisseur;
    int actio;
    char* inputname; 
    char* outputname;

//Initialisation des variables
    inputname = malloc(100 * sizeof(char));

//Définition des actions en fonction des arguments
    while ((opt = getopt(argc, argv, OPTSTR)) != EOF) {
        switch(opt) {
            case 'h':
                printf("AIDE POUR LE PROGRAMME\n");
                break;
            case 'b':
                binaryseuil = atoi(optarg);
                printf("-b ENTERED avec %d comme seuil\n", binaryseuil);
                break;
            case 'c':
                printf("-c ENTERED\n");
                break;
            case 'd':
                printf("-d ENTERED\n");
                break;
            case 'e':
                printf("-e ENTERED\n");
                break;
            case 'f':
                printf("-f ENTERED\n");
                break;
            case 'i':
                inputname = optarg;
                printf("-i ENTERED avec %s comme nom de fichier d'entrée\n", inputname);
                break;
            case 'l':
                printf("-l ENTERED\n");
                break;
            case 'g':
                printf("-g ENTERED\n");
                break;
            case 'o':
                outputname = optarg;
                printf("-o ENTERED avec %s comme nom de fichier de sortie\n", outputname);
                break;
            case 'r':
                printf("-r ENTERED\n");
                break;
            case 'x':
                actio = optind;
                largeur = atoi(argv[actio-1]);
                hauteur = atoi(argv[actio]);
                epaisseur = atoi(argv[actio+1]);
                printf("-x ENTERED avec %d comme largeur, %d comme hauteur et %d comme epaisseur\n", largeur, hauteur, epaisseur);
                break;
            case 's':
                printf("-s ENTERED\n");
                break;
            case 'Z':
                printf("-Z ENTERED\n");
                break;
            case 'z':
                printf("-z ENTERED\n");
                break;
            default:
                printf("Les arguments ont mal été entrés ! \n");
                break;
        }
    }
    return 0;
}
