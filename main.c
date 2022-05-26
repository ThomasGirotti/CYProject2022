#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "fonction.h"

//Macros
#define OPTSTR "hb:cdefi:lgo:rx:sZz"

//Fonction main
int main(int argc, char *argv[]) {

    //Déclaration des variables
    int opt;
    int input = 0;
    int output = 0;
    int binaryseuil;
    int largeur;
    int hauteur;
    int epaisseur;
    int actio;
    int x;
    int y;
    int error = 0;
    char* inputname;
    char* outputname;
    image im;

    //Initialisation des variables
    inputname = (char*)malloc(100 * sizeof(char));

    //Définition des actions en fonction des arguments
    while ((opt = getopt(argc, argv, OPTSTR)) != EOF) {
        switch(opt) {
            case 'h':
                printf("AIDE POUR LE PROGRAMME\n"); //? LOG
                break;
            case 'b':
                binaryseuil = atoi(optarg);
                printf("-b ENTERED avec %d comme seuil\n", binaryseuil); //? LOG
                break;
            case 'c':
                printf("-c ENTERED\n"); //? LOG
                break;
            case 'd':
                printf("-d ENTERED\n"); //? LOG
                break;
            case 'e':
                printf("-e ENTERED\n"); //? LOG
                break;
            case 'f':
                printf("-f ENTERED\n"); //? LOG
                break;
            case 'i':
                inputname = optarg;
                input++;
                printf("-i ENTERED avec %s comme nom de fichier d'entrée\n", inputname); //? LOG
                break;
            case 'l':
                printf("-l ENTERED\n"); //? LOG
                break;
            case 'g':
                printf("-g ENTERED\n"); //? LOG
                break;
            case 'o':
                outputname = optarg;
                output++;
                printf("-o ENTERED avec %s comme nom de fichier de sortie\n", outputname); //? LOG
                break;
            case 'r':
                printf("-r ENTERED\n"); //? LOG
                break;
            case 'x':
                actio = optind;
                printf("optind = %d\n", optind); //? LOG
                printf("optind = %d\n", optind); //? LOG
                printf("actio + 1 = %d\n", actio+1); //? LOG
                printf("argc = %d\n", argc); //? LOG
                if (actio + 1 >= argc) {
                    printf("Erreur : l'option -x nécessite 3 arguments\nUtilisez l'argument -h pour afficher l'aide.\n");
                    exit(4);
                } else {
                    largeur = atoi(argv[actio-1]);
                    hauteur = atoi(argv[actio]);
                    epaisseur = atoi(argv[actio+1]);
                }
                printf("-x ENTERED avec %d comme largeur, %d comme hauteur et %d comme epaisseur\n", largeur, hauteur, epaisseur); //? LOG
                break;
            case 's':
                printf("-s ENTERED\n"); //? LOG
                break;
            case 'Z':
                printf("-Z ENTERED\n"); //? LOG
                break;
            case 'z':
                printf("-z ENTERED\n"); //? LOG
                break;
            default:
                error++;
                break;
        }
    }
    printf("argc = %d\n",argc); //? LOG
    printf("error = %d\n",error); //? LOG
    if ((error != 0) || (argc == 1)) {
        printf("Erreur : Les arguments ont mal été entrés !\nUtilisez l'argument -h pour afficher l'aide.\n");
        exit(0);
    }

    //Call input image
    if (input > 0) {
        importimage(inputname,&im); //? Maybe refaire cause function to return somthing
        printf("Image chargée !\n"); //? LOG
        printf("maxvaluetest = %d\n",im.maxvalue); //? LOG
    } else if (largeur != 0) { //TODO : refaire logique (déclenchement -x avec -i)
        //Fonction création de la croix
        //croix(&im,largeur,hauteur,epaisseur);
        printf("Croix crée !\n"); //? LOG
    } else {
        printf("Erreur : Aucune image n'a été chargée et l'option -x n'a pas été spécifiée !\nUtilisez l'argument -h pour afficher l'aide.\n");
        exit(5);
    }

    //Call output image (export ou affichage)
    if (output > 0) {
        exportimage(outputname,&im);
        printf("Image exportée !\n"); //? LOG
    } else {
        printimage(&im);
    }
    return 0;
}
