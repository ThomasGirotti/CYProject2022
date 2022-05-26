#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

void importimage(char* inputname,image image) {

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
    fscanf(file, "%d %d\n",&image.x,&image.y);
    printf("image.x = %d image.y = %d\n",image.x,image.y);

//Récupération de la max value d'un pixel
    fscanf(file,"%d",&image.maxvalue);
    printf("%d\n",image.maxvalue);

//Initialisation du tableau
    image.red=(int**)malloc(image.x *sizeof(int*));
    for (int g = 0; g < image.x; g++) {
        image.red[g]=(int*)malloc(image.y *sizeof(int));
    }
    image.green=(int**)malloc(image.x *sizeof(int*));
    for (int h = 0; h < image.x; h++) {
        image.green[h]=(int*)malloc(image.y *sizeof(int));
    }
    image.blue=(int**)malloc(image.x *sizeof(int*));
    for (int f = 0; f < image.x; f++) {
        image.blue[f]=(int*)malloc(image.y *sizeof(int));
    }

//Récupératiion des pixel
    for(int i=0; i<image.y; i++) {
        for (int j = 0; j <image.x; j++) {
            fscanf(file,"%d\n",&image.red[j][i]);
            fscanf(file,"%d\n",&image.green[j][i]);
            fscanf(file,"%d\n",&image.blue[j][i]);
        }
    }

/*
int x;
int y;
printf("Entrez le x souhaité : \n");
scanf("%d",&x);
printf("Entrez le y souhaité : \n");
scanf("%d",&y);
printf("red = %d green = %d blue = %d\n",image.red[x][y],image.green[x][y],image.blue[x][y]);

    for(int i=0; i<image.y; i++) {
        for (int j = 0; j <image.x; j++) {
            printf("%d\n",image.red[j][i]);
            printf("%d\n",image.green[j][i]);
            printf("%d\n",image.blue[j][i]);
        }
    }
*/
    fclose(file);
    free(laLigne);
}