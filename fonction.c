#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

//Fonction Binarisation
void binaire(image* im,int seuil) { //* Fonction validée
    int pixel=0;
    for(int i=0; i<im->y;i++){ // on balaie les lignes
        for(int j=0; j<im->x;j++){ // on balaie les colonnes
            if (((im->red[i][j]+im->green[i][j]+im->blue[i][j])/3)<seuil) {
            im->red[i][j]=0; // transforme le rouge dans la bonne teinte
            im->green[i][j]=0; // transforme le vert dans la bonne teinte
            im->blue[i][j]=0; // transforme le bleu dans la bonne teinte
            } else {
            im->red[i][j]=im->maxvalue; // transforme le rouge dans la bonne teinte
            im->green[i][j]=im->maxvalue; // transforme le vert dans la bonne teinte
            im->blue[i][j]=im->maxvalue; // transforme le bleu dans la bonne teinte   
            }
        }
    }  
}

//Fonction Convolution 
/*
void convolution(image img, int** matrice) { //TODO : Réparer
    image img2;
    int compteur_red;
    int compteur_green;
    int compteur_blue;
    for (int i=0;i<img.x;i++){
        for (int j=0;j<img.y;j++){
            compteur_red=0;
            compteur_green=0;
            compteur_blue=0;
            for (int k=0;k<2;k++){
                for (int l=0;l<2;l++){
                    compteur_red=compteur_red+matrice[k][l]*img->red[i+k][j+l]; //! img doit etre un int
                    compteur_green=compteur_green+matrice[k][l]*img->green[i+k][j+l];
                    compteur_blue=compteur_blue+matrice[k][l]*img->blue[i+k][j+l];
                }
            }
        img2->red[i][j]=compteur_red; //! img2 est de type image / ne peut pas prendre de int
        img2->gree[i][j]=compteur_green;
        img2->blue[i][j]=compteur_blue;
        }
    }
}*/

//Fonction Histogramme
int* histogramme(image* img) { //TODO : Check
    int* tab;
    int x;
    int y;
    tab = malloc(255*sizeof(int)); //? : Remplacer 255 par maxvalue ?
    x=img->x;
    y=img->y;
    for(int i=0; i<x;i++){ // on balaie les lignes
        for(int j=0; j<y;j++){ // on balaie les colonnes
            tab[img->red[i][j]]++;
        }
    }
    return tab;
}

//Fonction Mirroir
void miroir(image* im) { //TODO : voir les cas impair
  int pixel=0;
  int pixel_red=0;
  int pixel_green=0;
  int pixel_blue=0;
  int x=im->x;
  int y=im->y;
  for(int i=0; i<(im->x)/2;i++){ // On balaie les lignes
      for(int j=0; j<im->y;j++){ // On balaie les colonnes
          pixel_red=im->red[i][j]; // Transforme le rouge dans la bonne teinte
          pixel_blue=im->blue[i][j]; // Transforme le vert dans la bonne teinte
          pixel_green=im->green[i][j]; // Transforme le bleu dans la bonne teinte
          im->red[i][j]=im->red[x-1-i][j];
          im->green[i][j]=im->green[x-1-i][j];
          im->blue[i][j]=im->blue[x-1-i][j];
          im->red[x-1-i][j]=pixel_red;
          im->blue[x-1-i][j]=pixel_blue;
          im->green[x-1-i][j]=pixel_green;
      }
  }
}
    
//Fonction Negatif
void negatif(image* im) { //* Fonction validée
    for(int i=0; i<im->x;i++){ // On balaie les lignes
        for(int j=0; j<im->y;j++){ // On balaie les colonnes
            im->red[i][j]= im->maxvalue-im->red[i][j]; // On inverse les couleurs rouges
            im->green[i][j]= im->maxvalue-im->green[i][j]; // On inverse les couleurs vertes
            im->blue[i][j]= im->maxvalue-im->blue[i][j]; // On inverse les couleurs bleues
        }
    }
}

//Fonction Recadrage_dyna
void recadyna(image* im) { //TODO : Refaire la fonction (ne fonctionne pas)
    int del;
    int* tab;
    int max;
    int min;
    tab = (int*)malloc(255*sizeof(int));
    transform_gris(im);
    tab = histogramme(im);
    for(int i=0; i<255; i++){
      printf("%d \n", tab[i]);
    }
    max = tab[0];
    min = tab[0];
    for (int i = 0; i < 255; i++) {
        if (tab[i]<min){
            min=tab[i];
        }
        if (tab[i]>max){
        max=tab[i];
        }
    }
    del = 255/(max-min); //! Floating point exception
    for (int i = 0; i < im->x; i++) {
        for (int j=0; j<im->y;j++){
            //im->red[i][y]=(im->red[i][y]-min)*del; //! replace y
            //im->green[i][y]=(im->green[i][y]-min)*del; //! replace y
            //im->blue[i][y]=(im->blue[i][y]-min)*del; //! replace y
        }
    }
}

//Fonction Rotate
void rotate(image* im) { //TODO : reste une colone noir à droite quand image rectangle + manque une ligne à gauche
    image imrotate;
    imrotate.x = im->y;
    imrotate.y = im->x;
    imrotate.red=malloc(sizeof(int*)*imrotate.x);
    for(int i=0; i<imrotate.x; i++){
        imrotate.red[i]=malloc(sizeof(int)*imrotate.y); 
    }
    imrotate.blue=malloc(sizeof(int*)*imrotate.x);
    for(int i=0; i<imrotate.x; i++){
        imrotate.blue[i]=malloc(sizeof(int)*imrotate.y); 
    }
    imrotate.green=malloc(sizeof(int*)*imrotate.x);
    for(int i=0; i<imrotate.x; i++){
        imrotate.green[i]=malloc(sizeof(int)*imrotate.y); 
    }
    for(int i=0; i<im->y; i++) {
        for(int j=0; j<im->x; j++) {
            imrotate.red[i][j]=im->red[j][im->x-i-1];
            imrotate.green[i][j]=im->green[j][im->x-i-1];
            imrotate.blue[i][j]=im->blue[j][im->x-i-1];
        }
    }
    im->red = realloc(im->red, im->y *sizeof(int*));
    for (int g = 0; g < im->y; g++) {
        im->red[g] = realloc(im->red[g], im->x *sizeof(int));
    }   
    im->green = realloc(im->green, im->y *sizeof(int*));
    for (int g = 0; g < im->y; g++) {
        im->green[g] = realloc(im->green[g], im->x *sizeof(int));
    }
    im->blue = realloc(im->blue, im->y *sizeof(int*));
    for (int g = 0; g < im->y; g++) {
        im->blue[g] = realloc(im->blue[g], im->x *sizeof(int));
    }
    if (im->x==im->y) {
        for(int i=0; i<im->y; i++) {
            for(int j=0; j<im->x; j++) {
                im->red[i][j]=imrotate.red[i][j];
                im->green[i][j]=imrotate.green[i][j];
                im->blue[i][j]=imrotate.blue[i][j];
            }
        }
    } else {
    im->y=imrotate.y;
    im->x=imrotate.x;
        for(int i=0; i<=im->y; i++) {
            for(int j=0; j<=im->x; j++) {
                im->red[i][j]=imrotate.red[i][j];
                im->green[i][j]=imrotate.green[i][j];
                im->blue[i][j]=imrotate.blue[i][j];
            }
        }
    }
    for(int i=0; i<imrotate.x; i++) {
        free(imrotate.red[i]);
    }
    for(int i=0; i<imrotate.x; i++) {
        free(imrotate.blue[i]);
    }
    for(int i=0; i<imrotate.x; i++) {
        free(imrotate.green[i]);
    }
    free(imrotate.red);
    free(imrotate.blue);
    free(imrotate.green);
    imrotate.red = NULL;
    imrotate.blue = NULL;
    imrotate.green = NULL;
}

//Fonction Transform_gris
void transform_gris(image* im) { //* Fonction validée
    int pixel=0;
    for(int i=0; i<im->x;i++){ // On balaie les lignes
        for(int j=0; j<im->y;j++){ // On balaie les colonnes
            pixel=im->red[i][j]*0.2126+im->green[i][j]*0.7152+im->blue[i][j]*0.0722; // application de la formule
            im->red[i][j]=pixel; // Transforme le rouge dans la bonne teinte
            im->green[i][j]=pixel; // Transforme le vert dans la bonne teinte
            im->blue[i][j]=pixel; // Transforme le bleu dans la bonne teinte
        }
    }  
}
