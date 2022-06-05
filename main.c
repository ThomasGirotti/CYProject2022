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
                printf("./main [-b Arg] [-c] [-d] [-e] [-f] [-g] [-h] [-i Arg] [-l] [-m] [-n] [-o Arg] [-p] [-r] [-x Arg1 Arg2 Arg3] [-Z] [-z]\n\n");
                printf("[-b Arg] : Effectue une binarisation avec Arg le seuil (nombre entier)\n");
                printf("[-c] : Effectue un renforcement de contraste\n");
                printf("[-d] : Effectue une dilatation\n");
                printf("[-e] : Effectue une erosion\n");
                printf("[-f] : Effectue un flou\n");
                printf("[-g] : Effectue une nuance de gris\n");
                printf("[-h] : Affiche l'aide\n");
                printf("[-i Arg] : Indique un fichier d'entrée avec Arg le nom du fichier d'entrée\n");
                printf("[-l] : Effectue une détection de contours\n");
                printf("[-m] : Effectue un mirroir\n");
                printf("[-n] : Effectue un négatif\n");
                printf("[-o Arg] : Indique un fichier de sortie avec Arg le nom du fichier de sortie\n");
                printf("[-p] : Effectue une rotation de 90° dans le sens horaire\n");
                printf("[-r] : Effectue un recadrage dynamique\n");
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
                if (binaryseuil < 0 || binaryseuil > 255) {
                    printf("Erreur : Le seuil de binarisation doit être compris entre 0 et 255\n");
                    exit(EXIT_FAILURE);
                }
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
    //Execution des actions en fonction des arguments
    if ((input > 0) || (actio > 0)) {
        if (input > 0) {
            error = importimage(inputname,&im);
                if (error != 0) {
                    exit(EXIT_FAILURE);
                }
        }
        if (actio > 0) {
            creercroix(&im,largeur,hauteur,epaisseur);
        }
    } else {
        printf("Erreur : Aucune image n'a été chargée et l'option -x n'a pas été spécifiée !\nUtilisez l'argument -h pour afficher l'aide.\n");
        exit(EXIT_FAILURE);
    }
    
    //Manpulations basiques
    if (gg > 0) {
        transform_gris(&im);
    }
    
    if (bb > 0) {
        if(binaryseuil < 0 || binaryseuil > im.maxvalue) {
                    printf("Erreur : Le seuil doit être compris entre 0 et %d\n",im.maxvalue);
                    exit(EXIT_FAILURE);
                }
        binaire(&im,binaryseuil);
    }
    
    if (mm > 0) {
        miroir(&im);
    }
    
    if (pp > 0) {
        rotate(&im);
    }
    
    if (nn > 0) {
        negatif(&im);
    }
    
    if (rr > 0) {
        recadyna(&im);
    }
    
    //Filtrage
    if (cc > 0) {
        contraste(&im);
    }
    
    if (ff > 0) {
        floutage(&im);
    }
    
    if (ll > 0) {
        contour(&im);
    }
    
    //Segmentation
    if (ee > 0) {
        croix croix5;
        croix5.x = 5;
        croix5.y = 5;
        croix5.epaisseur = 1;
        erosion(&im,croix5);
    }
    
    if (dd > 0) {
        croix croix5;
        croix5.x = 5;
        croix5.y = 5;
        croix5.epaisseur = 1;
        dilatation(&im,croix5);
    }

    if(grandz > 0) {
        zoom(&im);
    }
    
    if(petitz > 0) {
        dezoom(&im);
    }
    //Sauvegarde ou affichage
    if (output > 0) {
        error = exportimage(outputname,&im);
        if (error != 0) {
            exit(EXIT_FAILURE);
        }
    } else {
        printimage(&im);
        //printimage(&im);
    }

    //Libération de la mémoire
    freeimage(&im);
    return 0;
}
