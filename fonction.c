#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

//Fonction Binarisation
void binaire(image im,int seuil) { //TODO : Check
    int pixel=0;
    for(int i=0; i<im.y;i++){ // on balaie les lignes
        for(int j=0; j<im.x;j++){ // on balaie les colonnes
            if (((im.red[i][j]+im.green[i][j]+im.blue[i][j])/3)<seuil) {
            im.red[i][j]=0; // transforme le rouge dans la bonne teinte
            im.green[i][j]=0; // transforme le vert dans la bonne teinte
            im.blue[i][j]=0; // transforme le bleu dans la bonne teinte
            } else {
            im.red[i][j]=255; // transforme le rouge dans la bonne teinte
            im.green[i][j]=255; // transforme le vert dans la bonne teinte
            im.blue[i][j]=255; // transforme le bleu dans la bonne teinte   
            }
        }
    }  
}

//Fonction Convolution

//Fonction Histogramme
int* histogramme(image img) { //TODO : Remplace 255 by maxvalue and Check
    int* tab;
    int x;
    int y;
    tab = malloc(255*sizeof(int));
    x=img.x;
    y=img.y;
    for(int i=0; i<x;i++){ // on balaie les lignes
        for(int j=0; j<y;j++){ // on balaie les colonnes
            tab[img.red[i][j]]=+1;
        }
    }
    return tab;
}

//Fonction Mirroir
void miroir(image im) { //TODO : Refaire la fonction (y impair ne fonctionne pas)
    int pixel_red=0;
    int pixel_green=0;
    int pixel_blue=0;
    for(int i=0; i<im.x;i++){ // on balaie les lignes
        for(int j=0; j<im.y/2;j++){ // on balaie les colonnes
            pixel_red=im.red[i][j]; // on stock les valeurs
            pixel_green=im.green[i][j];
            pixel_blue=im.blue[i][j];
            im.red[i][j]=im.red[i][im.y-j]; // on met la partie de droite à gauche    
            im.green[i][j]=im.green[i][im.y-j];       
            im.blue[i][j]=im.blue[i][im.y-j];
            im.red[i][j]=pixel_red;  // on met la partie de gauche (stocké) à droite
            im.green[i][j]=pixel_green;      
            im.blue[i][j]=pixel_blue;
        }
    }  
}

//Fonction Negatif
void negatif(image im) { //TODO : Check
    for(int i=0; i<im.x;i++){ // on balaie les lignes
        for(int j=0; j<im.y;j++){ // on balaie les colonnes
            im.red[i][j]= 255-im.red[i][j];
            im.green[i][j]= 255-im.green[i][j];
            im.blue[i][j]= 255-im.blue[i][j];
        }
    }
}

//Fonction Recadrage_dyna
void recadyna(image im) { //TODO : Replace coordonnees y dans im
    int del;
    int* tab;
    int max;
    int min;
    tab = (int*)malloc(255*sizeof(int));
    tab = histogramme(im);
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
    del = 255/(max-min);
    for (int i = 0; i < im.x; i++) {
        for (int j=0; j<im.y;j++){
            //im.red[i][y]=(im.red[i][y]-min)*del;
            //im.green[i][y]=(im.green[i][y]-min)*del;
            //im.blue[i][y]=(im.blue[i][y]-min)*del;
        }
    }
}


//Fonction Recadrage
void recadrage(image img,int tab[255]) { //TODO : Terminer la fonction
    int x;
    int y;
    x=img.x;
    y=img.y;



}

//Fonction Rotate
image rotate(image im) { //TODO : Check
    image imrotate;
    imrotate.x = im.y;
    imrotate.y = im.x;
    for(int i=0; i<=im.y; i++){
        for(int j=0; j<=im.x; j++){
            imrotate.red[i][j]=im.red[im.y-i][j];
            imrotate.green[i][j]=im.green[im.y-i][j];
            imrotate.blue[i][j]=im.blue[im.y-i][j];
        }
    }
    return imrotate;
}


//Fonction Transform_gris
void transform_gris(image im) { //TODO : Check
    int pixel=0;
    for(int i=0; i<im.x;i++){ // On balaie les lignes
        for(int j=0; j<im.y;j++){ // On balaie les colonnes
            pixel=im.red[i][j]*0.2126+im.green[i][j]*0.7152+im.blue[i][j]*0.0722; // application de la formule
            im.red[i][j]=pixel; // Transforme le rouge dans la bonne teinte
            im.green[i][j]=pixel; // Transforme le vert dans la bonne teinte
            im.blue[i][j]=pixel; // Transforme le bleu dans la bonne teinte
        }
    }  
}
