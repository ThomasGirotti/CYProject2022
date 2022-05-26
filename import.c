#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

void importimage(char* inputname,image im) {

    char* laLigne;
    FILE* file = NULL;

    laLigne=(char*)malloc(sizeof(char)*20);

//Ouverture du fichier
    file = fopen(inputname,"r");
    printf("file name is %s\n", inputname);

//Vérification de l'ouverture du fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier, veuillez vérifier le nom\n");
        exit(1);
    }

//Vérification du format du fichier
    fscanf(file,"%s\n",laLigne);
    printf("%s\n",laLigne);
    if (strcmp(laLigne, "P3") != 0) {
        printf("Erreur : Le fichier n'est pas au format PPM P3\n");
        exit(1);
    }

//Récupération de la résolution
    fscanf(file, "%d %d\n",&im.x,&im.y);
    printf("im.x = %d im.y = %d\n",im.x,im.y);

//Récupération de la max value d'un pixel
    fscanf(file,"%d",&im.maxvalue);
    printf("%d\n",im.maxvalue);

//Initialisation du tableau
    im.red=(int**)malloc(im.x *sizeof(int*));
    for (int g = 0; g < im.x; g++) {
        im.red[g]=(int*)malloc(im.y *sizeof(int));
    }
    im.green=(int**)malloc(im.x *sizeof(int*));
    for (int h = 0; h < im.x; h++) {
        im.green[h]=(int*)malloc(im.y *sizeof(int));
    }
    im.blue=(int**)malloc(im.x *sizeof(int*));
    for (int f = 0; f < im.x; f++) {
        im.blue[f]=(int*)malloc(im.y *sizeof(int));
    }

//Récupératiion des pixel
    for(int i=0; i<im.y; i++) {
        for (int j = 0; j <im.x; j++) {
            fscanf(file,"%d\n",&im.red[j][i]);
            fscanf(file,"%d\n",&im.green[j][i]);
            fscanf(file,"%d\n",&im.blue[j][i]);
        }
    }

/*
int x;
int y;
printf("Entrez le x souhaité : \n");
scanf("%d",&x);
printf("Entrez le y souhaité : \n");
scanf("%d",&y);
printf("red = %d green = %d blue = %d\n",im.red[x][y],im.green[x][y],im.blue[x][y]);

    for(int i=0; i<im.y; i++) {
        for (int j = 0; j <im.x; j++) {
            printf("%d\n",im.red[j][i]);
            printf("%d\n",im.green[j][i]);
            printf("%d\n",im.blue[j][i]);
        }
    }
*/
    fclose(file);
    free(laLigne);
}