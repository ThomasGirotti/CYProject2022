#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "fonction.h"

//Macros
#define OPTSTR "hb:cdefgi:lmno:prsx:Zz"

//Fonction main
int main(int argc, char *argv[]) {

    //Déclaration des variables
    int opt;
    int input = 0;
    int output = 0;
    int binaryseuil;
    int largeur = 0;
    int hauteur = 0;
    int epaisseur = 0;
    int actio = 0;
    int error = 0;
    int bb = 0;
    int cc = 0;
    int dd = 0;
    int ee = 0;
    int ff = 0;
    int gg = 0;
    int ll = 0;
    int mm = 0;
    int nn = 0;
    int pp = 0;
    int rr = 0;
    int ss = 0;
    int grandz = 0;
    int petitz = 0;
    char* inputname;
    char* outputname;
    image im;

    //Définition des actions en fonction des arguments
    while ((opt = getopt(argc, argv, OPTSTR)) != EOF) {
        switch(opt) {
            case 'h':
                printf("AIDE POUR LE PROGRAMME\n"); //? LOG
                exit(EXIT_SUCCESS);
                break;
            case 'b':
                binaryseuil = atoi(optarg);
                bb++;
                printf("-b ENTERED avec %d comme seuil\n", binaryseuil); //? LOG
                break;
            case 'c':
                printf("-c ENTERED\n"); //? LOG
                cc++;
                break;
            case 'd':
                printf("-d ENTERED\n"); //? LOG
                dd++;
                break;
            case 'e':
                printf("-e ENTERED\n"); //? LOG
                ee++;
                break;
            case 'f':
                printf("-f ENTERED\n"); //? LOG
                ff++;
                break;
            case 'g':
                printf("-g ENTERED\n"); //? LOG
                gg++;
                break;
            case 'i':
                inputname = optarg;
                input++;
                printf("-i ENTERED avec %s comme nom de fichier d'entrée\n", inputname); //? LOG
                break;
            case 'l':
                printf("-l ENTERED\n"); //? LOG
                ll++;
                break;
            case 'm':
                printf("-m ENTERED\n"); //? LOG
                mm++;
                break;
            case 'n':
                printf("-n ENTERED\n"); //? LOG
                nn++;
            case 'o':
                outputname = optarg;
                output++;
                printf("-o ENTERED avec %s comme nom de fichier de sortie\n", outputname); //? LOG
                break;
            case 'p':
                printf("-p ENTERED\n"); //? LOG
                pp++;
                break;
            case 'r':
                printf("-r ENTERED\n"); //? LOG
                rr++;
                break;
            case 's':
                printf("-s ENTERED\n"); //? LOG
                ss++;
                break;
            case 'x':
                actio = optind;
                printf("optind = %d\n", optind); //? LOG
                printf("optind = %d\n", optind); //? LOG
                printf("actio + 1 = %d\n", actio+1); //? LOG
                printf("argc = %d\n", argc); //? LOG
                if (actio + 1 >= argc) {
                    printf("Erreur : l'option -x nécessite 3 arguments\nUtilisez l'argument -h pour afficher l'aide.\n");
                    exit(EXIT_FAILURE);
                } else {
                    largeur = atoi(argv[actio-1]);
                    hauteur = atoi(argv[actio]);
                    epaisseur = atoi(argv[actio+1]);
                }
                printf("-x ENTERED avec %d comme largeur, %d comme hauteur et %d comme epaisseur\n", largeur, hauteur, epaisseur); //? LOG
                break;
            case 'Z':
                printf("-Z ENTERED\n"); //? LOG
                grandz++;
                break;
            case 'z':
                printf("-z ENTERED\n"); //? LOG
                petitz++;
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
        exit(EXIT_FAILURE);
    }

    //Call input image
    if ((input > 0) || (actio > 0)) {
        if (input > 0) {
            importimage(inputname,&im); //? Maybe refaire to cause function to return somthing
            printf("Image chargée !\n"); //? LOG
            printf("maxvaluetest = %d\n",im.maxvalue); //? LOG
        }
        if (actio > 0) {
            //Fonction création de la croix
            //croix(&im,largeur,hauteur,epaisseur); //TODO : faire une fonction qui crée une croix
            printf("Croix crée !\n"); //? LOG
        }
    } else {
        printf("Erreur : Aucune image n'a été chargée et l'option -x n'a pas été spécifiée !\nUtilisez l'argument -h pour afficher l'aide.\n");
        exit(EXIT_FAILURE);
    }

//Transformations
    if (gg > 0) {
        transform_gris(&im);
        printf("Niveau de gris effectué !\n"); //? LOG
    }

    if (bb > 0) {
        binaire(&im,binaryseuil);
        printf("Binarisation effectuée !\n"); //? LOG
    }

    if (mm > 0) {
        miroir(&im);
        printf("Miroir effectué !\n"); //? LOG
    }

    if (pp > 0) { //! Revoir la méthode de call
        rotate(&im);
        printf("Rotation effectuée !\n"); //? LOG
    }

    if (nn > 0) {
        negatif(&im);
        printf("Negatif effectué !\n"); //? LOG
    }

    histogramme(&im); //? Appel ?

    if (rr > 0) {
        recadyna(&im);
        printf("Recadrage dynamique effectué !\n"); //? LOG
    }


    convolution(&im); //? Appel ?

/*
    if (cc > 0) {
        contraste(&im);
        printf("Renforcement de contraste effectué !\n"); //? LOG
    }

    if (ff > 0) {
        flou(&im);
        printf("Flou effectué !\n"); //? LOG
    }

    if (ll > 0) {
        detectioncontour(&im);
        printf("Detection de contours effectuée !\n"); //? LOG
    }

    if (ee > 0) {
        erosion(&im);
        printf("Erosion effectuée !\n"); //? LOG
    }

    if (dd > 0) {
        dilatation(&im);
        printf("Dilatation effectuée !\n"); //? LOG
    }

    if (grandz > 0) {
        zoom(&im);
        printf("Zoom effectué !\n"); //? LOG
    }

    if (petitz > 0) {
        dezoom(&im);
        printf("Dezoom effectué !\n"); //? LOG
    }

    if (ss > 0) {
        segmentation(&im);
        printf("Segmentation effectué !\n"); //? LOG
    }
*/
    //Call output image (export ou affichage)
    if (output > 0) {
        exportimage(outputname,&im);
        printf("Image exportée !\n"); //? LOG
    } else {
        printimage(&im);
    }
    return 0;
}

//! dernier exemple pas de -x ?
//! pas d'option pour lancer mirroir et négatif ? (-m et -n non présent)
//! Histogramme à chaque call ??
//TODO : refaire les fonctions pour etre en pointeur