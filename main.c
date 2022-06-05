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
                printf("Bienvenue dans l'aide de ce programme\n");
                printf("Ce programme permet de faire des traitements sur une image\n\n");
                printf("APPEL :\n");
                printf("La commande d'appel du programme doit être formulée comme ceci (l'ordre des options n'a pas d'importance) :\n\n");
                printf("./main [-b Arg] [-c] [-d] [-e] [-f] [-g] [-i Arg] [-l] [-m] [-n] [-o Arg] [-p] [-r] [-s] [-x Arg1 Arg2 Arg3] [-Z] [-z]\n\n");
                printf("[-b Arg] : Effectue une binarisation avec Arg le seuil (nombre entier)\n");
                printf("[-c] : Effectue un renforcement de contraste\n");
                printf("[-d] : Effectue une dilatation\n");
                printf("[-e] : Effectue une erosion\n");
                printf("[-f] : Effectue un flou\n");
                printf("[-g] : Effectue une nuance de gris\n");
                printf("[-i Arg] : Indique un fichier d'entrée avec Arg le nom du fichier d'entrée\n");
                printf("[-l] : Effectue une détection de contours\n");
                printf("[-m] : Effectue un mirroir\n");
                printf("[-n] : Effectue un négatif\n");
                printf("[-o Arg] : Indique un fichier de sortie avec Arg le nom du fichier de sortie\n");
                printf("[-p] : Effectue une rotation de 90° dans le sens horaire\n");
                printf("[-r] : Effectue un recadrage dynamique\n");
                printf("[-s] : Effectue une segmentation\n");
                printf("[-x Arg1 Arg2 Arg3] : Créée une croix de largeur Arg1, de hauteur Arg2, et d'épaisseur Arg3\n");
                printf("[-Z] : Effectue un zoom\n");
                printf("[-z] : Effectue un dézoom\n\n");
                printf("COMPORTEMENT :\n");
                printf("L'option -i est obligatoire sauf si l'option -x ou -h sont présentent.\n");
                printf("Si l'option -o n'est pas précisée alors le fichier sera affiché dans la console.\n");
                printf("Il n'y a pas de restrictions sur le nombre d'options.\n");
                exit(EXIT_SUCCESS);
                break;
            case 'b':
                binaryseuil = atoi(optarg);
                bb++;
                break;
            case 'c':
                cc++;
                break;
            case 'd':
                dd++;
                break;
            case 'e':
                ee++;
                break;
            case 'f':
                ff++;
                break;
            case 'g':
                gg++;
                break;
            case 'i':
                inputname = optarg;
                input++;
                break;
            case 'l':
                ll++;
                break;
            case 'm':
                mm++;
                break;
            case 'n':
                nn++;
            case 'o':
                outputname = optarg;
                output++;
                break;
            case 'p':
                pp++;
                break;
            case 'r':
                rr++;
                break;
            case 's':
                ss++;
                break;
            case 'x':
                actio = optind;
                if (actio + 1 >= argc) {
                    printf("Erreur : l'option -x nécessite 3 arguments\nUtilisez l'argument -h pour afficher l'aide.\n");
                    exit(EXIT_FAILURE);
                } else {
                    largeur = atoi(argv[actio-1]);
                    hauteur = atoi(argv[actio]);
                    epaisseur = atoi(argv[actio+1]);
                    if (largeur <= 0 || hauteur <= 0 || epaisseur <= 0) {
                        printf("Erreur : les arguments de l'option -x doivent être des nombres positifs\nUtilisez l'argument -h pour afficher l'aide.\n");
                        exit(EXIT_FAILURE);
                    }
                }
                printf("-x ENTERED avec %d comme largeur, %d comme hauteur et %d comme epaisseur\n", largeur, hauteur, epaisseur); //? LOG
                break;
            case 'Z':
                grandz++;
                break;
            case 'z':
                petitz++;
                break;
            default:
                error++;
                break;
        }
    }
    if ((error != 0) || (argc == 1)) {
        printf("Erreur : Les arguments ont mal été entrés !\nUtilisez l'argument -h pour afficher l'aide.\n");
        exit(EXIT_FAILURE);
    }

    //Call input image
    if ((input > 0) || (actio > 0)) {
        if (input > 0) {
            error = importimage(inputname,&im);
                if (error != 0) {
                    exit(EXIT_FAILURE);
                }
            printf("Image chargée !\n"); //? LOG
        }
        if (actio > 0) {
            creercroix(&im,largeur,hauteur,epaisseur); //TODO : faire une fonction qui crée une croix
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
        if(binaryseuil < 0 || binaryseuil > im.maxvalue) {
                    printf("Erreur : Le seuil doit être compris entre 0 et %d\n",im.maxvalue);
                    exit(EXIT_FAILURE);
                }
        binaire(&im,binaryseuil);
        printf("Binarisation effectuée !\n"); //? LOG
    }
    
    if (mm > 0) {
        miroir(&im);
        printf("Miroir effectué !\n"); //? LOG
    }
    
    if (pp > 0) {
        rotate(&im);
        printf("Rotation effectuée !\n"); //? LOG
    }
    
    if (nn > 0) {
        negatif(&im);
        printf("Negatif effectué !\n"); //? LOG
    }
    
    if (rr > 0) {
        recadyna(&im);
        printf("Recadrage dynamique effectué !\n"); //? LOG
    }
    
    if (cc > 0) {
        contraste(&im);
        printf("Renforcement de contraste effectué !\n"); //? LOG
    }
    
    if (ff > 0) {
        floutage(&im);
        printf("Flou effectué !\n"); //? LOG
    }
    
    if (ll > 0) {
        contour(&im);
        printf("Detection de contours effectuée !\n"); //? LOG
    }
    
    if (ee > 0) {
        croix croix5;
        croix5.x = 5;
        croix5.y = 5;
        croix5.epaisseur = 1;
        erosion(&im,&croix5);
        printf("Erosion effectuée !\n"); //? LOG
    }
    
    if (dd > 0) {
        croix croix5;
        croix5.x = 5;
        croix5.y = 5;
        croix5.epaisseur = 1;
        dilatation(&im,&croix5);
        printf("Dilatation effectuée !\n"); //? LOG
    }
    /*
    if (grandz > 0) {
        zoom(&im);
        printf("Zoom effectué !\n"); //? LOG
    }
    
    if (petitz > 0) {
        dezoom(&im);
        printf("Dezoom effectué !\n"); //? LOG
    }
    */
    //Call output image (export ou affichage)
    if (output > 0) {
        error = exportimage(outputname,&im);
        if (error != 0) {
            exit(EXIT_FAILURE);
        }
        printf("Image exportée !\n"); //? LOG
    } else {
        printimage(&im);
    }
    freeimage(&im);
    return 0;
}