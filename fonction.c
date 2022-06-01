#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

//Fonction Binarisation
void binaire(image* im,int seuil) { //* Fonction validée
    for(int i=0; i<im->x;i++) { // on balaie les lignes
        for(int j=0; j<im->y;j++) { // on balaie les colonnes
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
void convolution(image* img, int** matrice,image* img2) { //*Fonction validée
    int compteur_red;
    int compteur_green;
    int compteur_blue;
    for (int i=0;i<(img->x)-2;i++) {
        for (int j=0;j<(img->y)-2;j++) {
            compteur_red=0;
            compteur_green=0;
            compteur_blue=0;
            for (int k=0;k<3;k++) {
                for (int l=0;l<3;l++){
                    compteur_red=compteur_red+matrice[k][l]*img->red[i+k][j+l];
                    compteur_green=compteur_green+matrice[k][l]*img->green[i+k][j+l];
                    compteur_blue=compteur_blue+matrice[k][l]*img->blue[i+k][j+l];
                }
            }
            if (compteur_red>0) {
                img2->red[i][j]=compteur_red;
            } else {
                img2->red[i][j]=-compteur_red;
            }
            if (compteur_green>0) {
                img2->green[i][j]=compteur_green;
            } else {
                img2->green[i][j]=-compteur_green;
            }
            if (compteur_blue>0) {
                img2->blue[i][j]=compteur_blue;
            } else {
                img2->blue[i][j]=-compteur_blue;
            }
        }
    }
    for(int d=0; d<(img->x)-2;d++){ // On balaie les lignes
        for(int e=0; e<(img->y)-2;e++){ // On balaie les colonnes
            img->red[d][e]=img2->red[d][e];
            img->blue[d][e]=img2->blue[d][e];
            img->green[d][e]=img2->green[d][e];
        }
    }

}

void contraste(image* img) { //*Fonction validée
    int** matrice;
    image img2;
    img2.x=img->x;
    img2.y=img->y;
    img2.red=(int**)malloc(img->x *sizeof(int*));
    for (int g = 0; g < img->x; g++) {
        img2.red[g]=(int*)malloc(img->y *sizeof(int));
    }
    img2.green=(int**)malloc(img->x *sizeof(int*));
    for (int h = 0; h < img->x; h++) {
        img2.green[h]=(int*)malloc(img->y *sizeof(int));
    }
    img2.blue=(int**)malloc(img->x *sizeof(int*));
    for (int f = 0; f < img->x; f++) {
        img2.blue[f]=(int*)malloc(img->y *sizeof(int));
    }
    matrice=(int**)malloc(3 *sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrice[i]=(int*)malloc(3 *sizeof(int));
    }
    matrice[0][0]=0;
    matrice[0][1]=-1;
    matrice[0][2]=0;
    matrice[1][0]=-1;
    matrice[1][1]=5;
    matrice[1][2]=-1;
    matrice[2][0]=0;
    matrice[2][1]=-1;
    matrice[2][2]=0;
    convolution(img,matrice,&img2);
    for (int i = 0; i < 3; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

void floutage(image* img) { //*Fonction a tester
    int** matrice;
    image img2;
    img2.x=img->x;
    img2.y=img->y;
    img2.red=(int**)malloc(img->x *sizeof(int*));
    for (int g = 0; g < img->x; g++) {
        img2.red[g]=(int*)malloc(img->y *sizeof(int));
    }
    img2.green=(int**)malloc(img->x *sizeof(int*));
    for (int h = 0; h < img->x; h++) {
        img2.green[h]=(int*)malloc(img->y *sizeof(int));
    }
    img2.blue=(int**)malloc(img->x *sizeof(int*));
    for (int f = 0; f < img->x; f++) {
        img2.blue[f]=(int*)malloc(img->y *sizeof(int));
    }
    matrice=(int**)malloc(3 *sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrice[i]=(int*)malloc(3 *sizeof(int));
    }
    matrice[0][0]=0.0625;
    matrice[0][1]=0.125;
    matrice[0][2]=0.0625;
    matrice[1][0]=0.125;
    matrice[1][1]=0.25;
    matrice[1][2]=0.125;
    matrice[2][0]=0.0625;
    matrice[2][1]=0.125;
    matrice[2][2]=0.0625;
    convolution(img,matrice,&img2);
    for (int i = 0; i < 3; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

void contour(image* img) { //*Fonction a tester
    int** matrice;
    image img2;
    img2.x=img->x;
    img2.y=img->y;
    img2.red=(int**)malloc(img->x *sizeof(int*));
    for (int g = 0; g < img->x; g++) {
        img2.red[g]=(int*)malloc(img->y *sizeof(int));
    }
    img2.green=(int**)malloc(img->x *sizeof(int*));
    for (int h = 0; h < img->x; h++) {
        img2.green[h]=(int*)malloc(img->y *sizeof(int));
    }
    img2.blue=(int**)malloc(img->x *sizeof(int*));
    for (int f = 0; f < img->x; f++) {
        img2.blue[f]=(int*)malloc(img->y *sizeof(int));
    }
    matrice=(int**)malloc(3 *sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrice[i]=(int*)malloc(3 *sizeof(int));
    }
    matrice[0][0]=-1;
    matrice[0][1]=-1;
    matrice[0][2]=-1;
    matrice[1][0]=-1;
    matrice[1][1]=8;
    matrice[1][2]=-1;
    matrice[2][0]=-1;
    matrice[2][1]=-1;
    matrice[2][2]=-1;
    convolution(img,matrice,&img2);
    for (int i = 0; i < 3; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

//Fonction Histogramme
void histogramme(image* img,int* tab) { //* Fonction validée
    int x;
    int y;
    x=img->x;
    y=img->y;
    for(int i=0; i<img->maxvalue;i++){ // on balaie les colonnes
            tab[i]=0;
        }
    for(int i=0; i<x;i++){ // on balaie les lignes
        for(int j=0; j<y;j++){ // on balaie les colonnes
            tab[img->red[i][j]]++;
        }
    }
}

//Fonction Mirroir
void miroir(image* im) { //* Fonction validée
    int pixel=0;
    int pixel_red=0;
    int pixel_green=0;
    int pixel_blue=0;
    int x=im->x;
    int y=im->y;
    for(int i=0; i<(im->x)/2;i++) { // On balaie les lignes
        for(int j=0; j<im->y;j++) { // On balaie les colonnes
            pixel_red=im->red[i][j];
            pixel_blue=im->blue[i][j];
            pixel_green=im->green[i][j];
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
void recadyna(image* im) { //* Fonction validée
    float del;
    int* tab;
    int maxl;
    int minl;
    int v=0, w=0, z=0;
    tab = malloc(im->maxvalue*sizeof(int));
    transform_gris(im);
    histogramme(im,tab);
    while(v==0) {
        if (tab[w]==0){
            w=w+1;
        } else {
            v=1;
        }
    }
    minl=w;
    v=0;
    z=im->maxvalue;
    while(v==0) {
        if (tab[z]==0){
            z=z-1;
        } else {
            v=1;
        }
    }
    maxl=z;
    printf("%d %d \n", maxl, minl);
    del = (float)255/(maxl-minl);
    printf ("%f\n", del);
    for (int i = 0; i < im->x; i++) {
        for (int j=0; j<im->y;j++){
            im->red[i][j]= (im->red[i][j]-minl)*del;
            im->green[i][j]= (im->green[i][j]-minl)*del;
            im->blue[i][j]= (im->blue[i][j]-minl)*del;
        }
    }
}

//Fonction Rotate
void rotate(image* im) { //! 256 * 255 ne fonctionne pas (mais 255 * 256 fonctionne)
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
