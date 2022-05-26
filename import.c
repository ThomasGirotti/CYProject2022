#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

void importimage(char* inputname,image* im) {

    char laLigne[2];
    FILE* file = NULL;

//Ouverture du fichier
    file = fopen(inputname,"r");
    printf("file name is %s\n", inputname);

//Vérification de l'ouverture du fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier, veuillez vérifier le nom\nUtilisez l'argument -h pour afficher l'aide.\n");
        exit(1);
    }

//Vérification du format du fichier
    fscanf(file,"%s\n",laLigne);
    printf("%s\n",laLigne);
    if (strcmp(laLigne, "P3") != 0) {
        printf("Erreur : Le fichier n'est pas au format PPM P3\n");
        exit(2);
    }

//Récupération de la résolution
    fscanf(file, "%d %d\n",&im->x,&im->y);
    printf("im.x = %d im.y = %d\n",im->x,im->y);

//Récupération de la max value d'un pixel
    fscanf(file,"%d",&im->maxvalue);
    printf("%d\n",im->maxvalue);

//Initialisation du tableau
    im->red=(int**)malloc(im->x *sizeof(int*));
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

//Récupératiion des pixel
    for(int i=0; i<im->y; i++) {
        for (int j = 0; j <im->x; j++) {
            fscanf(file,"%d\n",&im->red[j][i]);
            fscanf(file,"%d\n",&im->green[j][i]);
            fscanf(file,"%d\n",&im->blue[j][i]);
        }
    }
    fclose(file);
}

int exportimage(char* outputname,image* im) {
    FILE* file = NULL;
    //Creation du fichier
    file = fopen(outputname,"w");
    printf("file name is %s\n", outputname);
    //Ecriture dans le fichier
    fprintf(file,"P3\n");
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
}