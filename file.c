#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

//Fonction importimage
/* Auteur : Thomas */
/* Date :   27/05 */
/* Résumé : transpose l'image dans la structure image*/
/* Entrée(s) :  char* inputname, image* img*/
/* Sortie(s) :   */
int importimage(char* inputname,image* im) {
    char laLigne[10];
    FILE* file = NULL;
    file = fopen(inputname,"r"); //Ouverture du fichier
    printf("file name is %s\n", inputname); //? LOG
    if (file != NULL) { //Vérification de l'ouverture du fichier
        fgets(laLigne,10,file);
        sscanf(laLigne,"%s",laLigne);
        printf("%s\n",laLigne); //? LOG
        if (strcmp(laLigne, "P3") == 0) { //Vérification du format du fichier
            fscanf(file, "%d %d\n",&im->x,&im->y); //Récupération de la résolution
            printf("im.x = %d im.y = %d\n",im->x,im->y); //? LOG
            fscanf(file,"%d",&im->maxvalue); //Récupération de la max value d'un pixel
            printf("%d\n",im->maxvalue); //? LOG
            im->red=(int**)malloc(im->x *sizeof(int*)); //Initialisation du tableau
            for (int g = 0; g < im->x; g++) {
                im->red[g]=(int*)malloc(im->y *sizeof(int));
            }
            im->green=(int**)malloc(im->x *sizeof(int*));
            for (int h = 0; h < im->x; h++) {
                im->green[h]=(int*)malloc(im->y *sizeof(int));
            }
            im->blue=(int**)malloc(im->x *sizeof(int*));
            for (int f = 0; f < im->x; f++) {
                im->blue[f]=(int*)malloc(im->y *sizeof(int));
            }
            for(int i=0; i<im->y; i++) { //Récupératiion des pixel
                for (int j = 0; j <im->x; j++) {
                    fscanf(file,"%d\n",&im->red[j][i]);
                    fscanf(file,"%d\n",&im->green[j][i]);
                    fscanf(file,"%d\n",&im->blue[j][i]);
                }
            }
            fclose(file);
            printf("Returned 1\n"); //? LOG
            return 0;
        } else {
            printf("Erreur : Le fichier n'est pas au format PPM P3\n");
            return 1;
        }
    } else {
        printf("Erreur : Le fichier n'a pas pu être ouvert, veuillez vérifier le nom\nUtilisez l'argument -h pour afficher l'aide\n");
        return 1;
    }
}
//Fonction exporteimage
/* Auteur : Thomas */
/* Date :   28/05 */
/* Résumé : applique à une image les instructions demandées*/
/* Entrée(s) :  char* outputname, image* img*/
/* Sortie(s) :   */
int exportimage(char* outputname,image* im) {
    FILE* file = NULL;
    file = fopen(outputname,"w"); //Creation du fichier
    if (file != NULL) {
        printf("file name is %s\n", outputname); //? LOG
        fprintf(file,"P3\n"); //Ecriture dans le fichier
        fprintf(file,"%d %d\n",im->x,im->y);
        fprintf(file,"%d\n",im->maxvalue);
        for(int i=0; i<im->y; i++) {
            for (int j = 0; j <im->x; j++) {
                fprintf(file,"%d\n",im->red[j][i]);
                fprintf(file,"%d\n",im->green[j][i]);
                fprintf(file,"%d\n",im->blue[j][i]);
            }
        }
        fclose(file);
        return 1;
    } else {
        printf("Erreur : Le fichier n'a pas pu être créé, veuillez vérifier le nom\nUtilisez l'argument -h pour afficher l'aide\n");
        return 0;
    }
}
//Fonction printfimage
/* Auteur : Thomas */
/* Date :   28/05 */
/* Résumé : renvoie les données de l'image avec les instructions appliquer*/
/* Entrée(s) :  image* img*/
/* Sortie(s) :   */
void printimage(image* im) {
    printf("P3\n");
    printf("%d %d\n",im->x,im->y);
    printf("%d\n",im->maxvalue);
    for(int i=0; i<im->y; i++) {
        for (int j = 0; j <im->x; j++) {
            printf("%d\n",im->red[j][i]);
            printf("%d\n",im->green[j][i]);
            printf("%d\n",im->blue[j][i]);
        }
    }
}

//Fonction exporteimage
/* Auteur : Thomas */
/* Date :   27/05 */
/* Résumé : free les tableaux*/
/* Entrée(s) : image* img*/
/* Sortie(s) :   */
void freeimage(image* im) {
    for (int i = 0; i < im->x; i++) {
        free(im->red[i]);
        free(im->green[i]);
        free(im->blue[i]);
    }
    free(im->red);
    free(im->green);
    free(im->blue);
    im->red = NULL;
    im->green = NULL;
    im->blue = NULL;
}
