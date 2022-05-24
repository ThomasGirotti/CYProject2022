#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void importimage(char* inputname,int* x,int* y) {

    char* laLigne;
    char ligne[20];    
    FILE* file = NULL;

    laLigne=malloc(sizeof(char)*20);

//Ouverture du fichier
    file = fopen(inputname,"r");
    printf("file name is %s\n", inputname);

//Vérification de l'ouverture du fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }

//Vérification du format du fichier
    laLigne=fgets(ligne,20,file);
    if (strcmp(laLigne, "P3") == 0) {
        printf("%s\n",laLigne);
        printf("Erreur : Le fichier n'est pas au format PPM P3\n");
        exit(1);
    }

//Récupération de la résolution
    fseek(file, 2, SEEK_SET);
    fscanf(file, "%d %d",x,y);
    printf("%d %d\n",*x,*y);
    
}