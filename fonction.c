#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

//Fonction Binarisation
/* Auteur : Lilian */
/* Date :  23/05 */
/* Résumé : Transforme l'image en noir et blanc à partir d'un seuil de tolérance*/
/* Entrée(s) :  im* image, int seuil*/
/* Sortie(s) :   */
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
/* Auteur : Lilian */
/* Date :   30/05 */
/* Résumé : prend une matrice de transformation et modifie l'image en fonction de cette dernière.
/* Entrée(s) :  image* img, float** matrice,image* img2 */
/* Sortie(s) :   */
void convolution(image* img, float** matrice) { //TODO : Fix ? Pas le même rendu que sur exemple
    int compteur_red=0;
    int compteur_green=0;
    int compteur_blue=0;    
    
    
    int tab_red[img->x+2][img->y+2]; // tableau pour stocker les pixels
    int tab_green[img->x+2][img->y+2];
    int tab_blue[img->x+2][img->y+2];
    for (int i=0;i<(img->x)+2;i++) {
        for (int j=0;j<(img->y)+2;j++) {
            if (i==0 || i==img->x+1 || j==0 || j==img->y+1){ // initialisation des pixels stockés
                tab_red[i][j]=0;
                tab_green[i][j]=0;
                tab_blue[i][j]=0;
            }
            else {
                tab_red[i][j]=img->red[i-1][j-1];
                tab_green[i][j]=img->green[i-1][j-1];
                tab_blue[i][j]=img->blue[i-1][j-1];
            }
        }
    }   
    for (int i=1;i<(img->x)+1;i++) {
        for (int j=1;j<(img->y)+1;j++) {
            compteur_red=0;
            compteur_green=0;
            compteur_blue=0;
            for (int k=0;k<3;k++) {
                for (int l=0;l<3;l++){ // On traite les pixels avec la matrice
                    compteur_red=compteur_red+matrice[k][l]*tab_red[i+k-1][j+l-1]; // rouge 
                    compteur_green=compteur_green+matrice[k][l]*tab_green[i+k-1][j+l-1]; // vert
                    compteur_blue=compteur_blue+matrice[k][l]*tab_blue[i+k-1][j+l-1]; // bleu
                }
            }
            // on remet les nouveau pixels
            if (compteur_red>0) { 
                img->red[i-1][j-1]=compteur_red;
            } else {
                img->red[i-1][j-1]=0;
            }
            if (compteur_green>0) {
                img->green[i-1][j-1]=compteur_green;
            } else {
                img->green[i-1][j-1]=0;
            }
            if (compteur_blue>0) {
                img->blue[i-1][j-1]=compteur_blue;
            } else {
                img->blue[i-1][j-1]=0;
            }
        }
    }
}

//Fonction contraste
/* Auteur : Lilian */
/* Date :   31/05 */
/* Résumé : renforce le contraste de l'image*/
/* Entrée(s) :  image* img*/
/* Sortie(s) :   */
void contraste(image* img) { //*Fonction validée
    float** matrice;
    matrice=(float**)malloc(3 *sizeof(float*)); // malloc de la matrice
    for (int i = 0; i < 3; i++) {
        matrice[i]=(float*)malloc(3 *sizeof(float));
    }
    matrice[0][0]=0; // initialisation de la matrice 
    matrice[0][1]=-1;
    matrice[0][2]=0;
    matrice[1][0]=-1;
    matrice[1][1]=5;
    matrice[1][2]=-1;
    matrice[2][0]=0;
    matrice[2][1]=-1;
    matrice[2][2]=0;
    convolution(img,matrice);
    for (int i = 0; i < 3; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

//Fonction floutage
/* Auteur : Lilian */
/* Date :   31/05 */
/* Résumé : rend l'image plus flou*/
/* Entrée(s) :  image* img*/
/* Sortie(s) :   */
void floutage(image* img) { //* Fonction validée
    float** matrice;
    matrice=(float**)malloc(3 *sizeof(float*)); // malloc de la matrice
    for (int i = 0; i < 3; i++) {
        matrice[i]=(float*)malloc(3 *sizeof(float));
    }
    matrice[0][0]=0.0625; // initialisation de la matrice
    matrice[0][1]=0.125;
    matrice[0][2]=0.0625;
    matrice[1][0]=0.125;
    matrice[1][1]=0.25;
    matrice[1][2]=0.125;
    matrice[2][0]=0.0625;
    matrice[2][1]=0.125;
    matrice[2][2]=0.0625;
    convolution(img,matrice);
    for (int i = 0; i < 3; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

//Fonction contour
/* Auteur : Lilian */
/* Date :   31/05 */
/* Résumé : met en évidence les contour de l'image l'image*/
/* Entrée(s) :  image* img*/
/* Sortie(s) :   */
void contour(image* img) { //*Fonction valdiée
    float** matrice;
    matrice=(float**)malloc(3 *sizeof(float*)); // malloc de la matrice
    for (int i = 0; i < 3; i++) {
        matrice[i]=(float*)malloc(3 *sizeof(float));
    }
    matrice[0][0]=-1; // initialisation de la matrice
    matrice[0][1]=-1;
    matrice[0][2]=-1;
    matrice[1][0]=-1;
    matrice[1][1]=8;
    matrice[1][2]=-1;
    matrice[2][0]=-1;
    matrice[2][1]=-1;
    matrice[2][2]=-1;
    convolution(img,matrice);
    for (int i = 0; i < 3; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

//Fonction histogramme
/* Auteur : Lilian */
/* Date :   26/05 */
/* Résumé : créé un histogramme de l'image et les met dans un tableau*/
/* Entrée(s) :  image* img, int* tab*/
/* Sortie(s) :   */
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
            tab[img->red[i][j]]++; // on rajoute 1 à chaque fois que la couleur apparait
        }
    }
}

//Fonction Mirroir
/* Auteur : Lilian */
/* Date :   01/06 */
/* Résumé : remplace l'image par une version miroir de celle-ci*/
/* Entrée(s) :  image* img*/
/* Sortie(s) :   */
void miroir(image* im) { //* Fonction validée
    int pixel_red=0;
    int pixel_green=0;
    int pixel_blue=0;
    int x=im->x;
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
/* Auteur : Lilian */
/* Date :   25/05 */
/* Résumé : inverse les valeur rgb des couleurs de l'image*/
/* Entrée(s) :  image* img*/
/* Sortie(s) :   */
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
/* Auteur : Pierre-Antoine */
/* Date :   29/05 */
/* Résumé : permet de voir avec plus de contraste l'histogramme*/
/* Entrée(s) :  image* img*/
/* Sortie(s) :   */
void recadyna(image* im) { //* Fonction validée
    float del;
    int* tab;
    int maxl;
    int minl;
    int v=0, w=0, z=0;
    tab = malloc(im->maxvalue*sizeof(int));
    transform_gris(im); // on met l'image en nuance de gris
    histogramme(im,tab); // on applique l'histogramme de l'image
    while(v==0) {        // on cherche la luminescence la plus basse
        if (tab[w]==0){
            w=w+1;
        } else {
            v=1;
        }
    }
    minl=w;
    v=0;
    z=im->maxvalue;
    while(v==0) {       // on cherche la luminescence la plus haute
        if (tab[z]==0){
            z=z-1;
        } else {
            v=1;
        }
    }
    maxl=z;
    del = (float)255/(maxl-minl); // on calcule le delta
    for (int i = 0; i < im->x; i++) { // on applique la formule pour tous les pixels
        for (int j=0; j<im->y;j++){
            im->red[i][j]= (im->red[i][j]-minl)*del;
            im->green[i][j]= (im->green[i][j]-minl)*del;
            im->blue[i][j]= (im->blue[i][j]-minl)*del;
        }
    }
}

//Fonction Rotate
/* Auteur : Pierre-Antoine */
/* Date :   02/06 */
/* Résumé : fait tourner une image à 90° vers la gauche*/
/* Entrée(s) :  image* img*/
/* Sortie(s) :   */
void rotate(image* im) { //* FONCTION VALIDEE 
    image im2;   // creation d'une image de transite
    im2.x = im->y;      //on inverse la longueur et la largeur de l'image
    im2.y = im->x;
    im2.red=(int**)malloc(im2.x *sizeof(int*)); //on alloue les different pixel en fonction de la nouvelle resolution
    for (int g = 0; g < im2.x; g++) {
        im2.red[g]=(int*)malloc(im2.y *sizeof(int));
    }
    im2.green=(int**)malloc(im2.x *sizeof(int*));
    for (int h = 0; h < im2.x; h++) {
        im2.green[h]=(int*)malloc(im2.y *sizeof(int));
    }
    im2.blue=(int**)malloc(im2.x *sizeof(int*));
    for (int f = 0; f < im2.x; f++) {
        im2.blue[f]=(int*)malloc(im2.y *sizeof(int));
    }
    for(int i=0; i<im2.x; i++) {   // on transpose les pixels de l'image de base vers l'image de transition
        for(int j=0; j<im2.y; j++) {
            im2.red[i][j]=im->red[j][im2.x-i-1];
            im2.green[i][j]=im->green[j][im2.x-i-1];
            im2.blue[i][j]=im->blue[j][im2.x-i-1];
        }
    }
    im->red = realloc(im->red, im2.x *sizeof(int*)); // on realloue la largeur et la longueur de l'image de base
    for (int g = 0; g < im2.x; g++) {
        im->red[g] = realloc(im->red[g], im2.y *sizeof(int));
    }
    im->green = realloc(im->green, im2.x *sizeof(int*));
    for (int g = 0; g < im2.x; g++) {
        im->green[g] = realloc(im->green[g], im2.y *sizeof(int));
    }
    im->blue = realloc(im->blue, im2.x *sizeof(int*));
    for (int g = 0; g < im2.x; g++) {
        im->blue[g] = realloc(im->blue[g], im2.y *sizeof(int));
    }
    im->x = im2.x;
    im->y = im2.y;
        for(int i=0; i<im->y; i++) {  // on applique les couleurs de l'image de transition sur l'image de base
            for(int j=0; j<im->x; j++) {
                im->red[j][i]=im2.red[j][i];
                im->green[j][i]=im2.green[j][i];
                im->blue[j][i]=im2.blue[j][i];
            }
        }
    freeimage(&im2);  // on free l'image de transition
}

//Fonction Transform_gris
/* Auteur : Lilian */
/* Date :   24/05 */
/* Résumé : Change l'image en nuance de gris*/
/* Entrée(s) :  image* img*/
/* Sortie(s) :   */
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

//Fonction creercroix
/* Auteur : Pierre-Antoine */
/* Date :   04/06 */
/* Résumé : prends une image vierge et dessine une croix dessus*/
/* Entrée(s) :  image* img*, int lon, int larg, int ep/
/* Sortie(s) :   */
void creercroix (image* im,int lon, int larg, int ep){
    int deca1;     // on crée 2 variable utilisés en fonction de l'épaisseur de la croix
    int deca2;
    im->x=lon;
    im->y=larg;
    printf("%d %d", im->x, lon);
   /* im->red = realloc(im->red, im->x *sizeof(int*)); // on realloue les dimensions de l'image de base par la longueur et la largeur rentré initialement
    for (int g = 0; g < im->x; g++) {
        im->red[g] = realloc(im->red[g], im->y *sizeof(int));
    }
    
    im->green = realloc(im->green, im->x *sizeof(int*));
    for (int g = 0; g < im->x; g++) {
        im->green[g] = realloc(im->green[g], im->y *sizeof(int));
    }
    im->blue = realloc(im->blue, im->x *sizeof(int*));
    for (int g = 0; g < im->x; g++) {
        im->blue[g] = realloc(im->blue[g], im->y *sizeof(int));
    }

    for (int i=0; i<lon; i++){  // on rend l'image complétement blanche
        for (int j=0; j<larg; j++){
            im->red[i][j]=255;
            im->green[i][j]=255;
            im->blue[i][j]=255;
        }
    }
    
    if (lon%2==0){   // on dessine le train verticale de la croix dans le case on la longueur est pair
        deca1=0;
        deca2=0;
        for(int k=0; k<ep;k++){
            if (k%2==0){        // si k est multiple de 2
                deca2=deca2+1;
                for (int i=0; i<larg; i++){
                    im->red[lon/2-(deca2-1)][i]=0;
                    im->green[lon/2-(deca2-1)][i]=0;
                    im->blue[lon/2-(deca2-1)][i]=0;
                }
            } else {
                deca1=deca1+1;
                for (int i=0; i<larg; i++){
                    im->red[lon/2+deca1][i]=0;
                    im->green[lon/2+deca1][i]=0;
                    im->blue[lon/2+deca1][i]=0;
                }
            }
        }
    } else {                    //dans le cas d'une longueur impaire, où le milieu existe
        deca1=0;
        deca2=0;
        for(int k=0; k<ep;k++){
            if (k%2==0){
                for (int i=0; i<larg; i++){
                    im->red[(lon-1)/2-deca2][i]=0;
                    im->green[(lon-1)/2-deca2][i]=0;
                    im->blue[(lon-1)/2-deca2][i]=0;
                }
            deca2=deca2+1;
            } else {
                for (int i=0; i<larg; i++){
                    im->red[(lon+1)/2+deca1][i]=0;
                    im->green[(lon+1)/2+deca1][i]=0;
                    im->blue[(lon+1)/2+deca1][i]=0;
                    
                }
            deca1=deca1+1;
            }
        }

    }
    //////////
    if (larg%2==0){        // on refait la même chose pour la largeur
        deca1=0;
        deca2=0;
        for(int k=0; k<ep;k++){
            if (k%2==0){
                deca2=deca2+1;
                for (int i=0; i<lon; i++){
                    im->red[i][larg/2-(deca2-1)]=0;
                    im->green[i][larg/2-(deca2-1)]=0;
                    im->blue[i][larg/2-(deca2-1)]=0;
                }
            } else {
                deca1=deca1+1;
                for (int i=0; i<lon; i++){
                    im->red[i][larg/2+deca1]=0;
                    im->green[i][larg/2+deca1]=0;
                    im->blue[1][larg/2+deca1]=0;
                }
            }
        }
    } else {
        deca1=0;
        deca2=0;
        for(int k=0; k<ep;k++){
            if (k%2==0){
                for (int i=0; i<lon; i++){
                    im->red[(larg-1)/2-deca2][i]=0;
                    im->green[(larg-1)/2-deca2][i]=0;
                    im->blue[(larg-1)/2-deca2][i]=0;
                }
            deca2=deca2+1;
            } else {
                for (int i=0; i<lon; i++){
                    im->red[i][(larg+1)/2+deca1]=0;
                    im->green[i][(larg+1)/2+deca1]=0;
                    im->blue[i][(larg+1)/2+deca1]=0;
                    
                }
            deca1=deca1+1;
            }
        }

    }*/


}

//Fonction dilatation
/* Auteur : Lilian */
/* Date :   04/06 */
/* Résumé : effectue une dilatation sur l'image d'entrée à l'aide de la structure croix de taille 5*/
/* Entrée(s) :  image* im, croix cr*/
/* Sortie(s) :   */
void dilatation(image* im,croix cr) {
    transform_gris(im);
    image im2;
    im2.x = cr.x;
    im2.y = cr.y;
    im2.red=(int**)malloc(im2.x *sizeof(int*)); //Initialisation du tableau
    for (int g = 0; g < im2.x; g++) {
        im2.red[g]=(int*)malloc(im2.y *sizeof(int));
    }
    for (int i=0; i<im2.x; i++){
        for (int j=0; j<im2.y; j++){
            im2.red[i][j]=0;
        }
    }
    im2.red[2][0]=255;
    im2.red[2][1]=255;
    im2.red[0][2]=255;
    im2.red[1][2]=255;
    im2.red[2][2]=255;
    im2.red[3][2]=255;
    im2.red[4][2]=255;
    im2.red[2][3]=255;
    im2.red[2][4]=255;
    int compteur_red;
    int tab_red[im->x][im->y];
    int max_pix=0;
    for (int i=0;i<(im->x);i++) {
        for (int j=0;j<(im->y);j++) {
            tab_red[i][j]=im->red[i][j];
        }
    }
    for (int i=0;i<(im->x)-cr.x;i++) {
        for (int j=0;j<(im->y)-cr.y;j++) {
            max_pix=0;
            for (int k=0;k<cr.x;k++) {
                for (int l=0;l<cr.y;l++) {
                    if (im2.red[k][l]==0) {
                        if (tab_red[i+k-(cr.x)/2][j+l-cr.y/2]>max_pix) {
                            max_pix=tab_red[i+k-(cr.x)/2][j+l-cr.y/2];
                        }
                    }
                }
            im->red[i][j]=max_pix;
            im->green[i][j]=max_pix;
            im->blue[i][j]=max_pix;
            }
        }
    }
}

//Fonction erosion
/* Auteur : Lilian */
/* Date :   04/06 */
/* Résumé : effectue une erosion sur l'image d'entrée à l'aide de la structure croix de taille 5*/
/* Entrée(s) :  image* im, croix cr*/
/* Sortie(s) :   */
void erosion(image* im,croix cr) {
    transform_gris(im);
    image im2;
    im2.x = cr.x;
    im2.y = cr.y;
    im2.red=(int**)malloc(im2.x *sizeof(int*)); //Initialisation du tableau
    for (int g = 0; g < im2.x; g++) {
        im2.red[g]=(int*)malloc(im2.y *sizeof(int));
    }
    for (int i=0; i<im2.x; i++){
        for (int j=0; j<im2.y; j++){
            im2.red[i][j]=0;
        }
    }
    im2.red[2][0]=255;
    im2.red[2][1]=255;
    im2.red[0][2]=255;
    im2.red[1][2]=255;
    im2.red[2][2]=255;
    im2.red[3][2]=255;
    im2.red[4][2]=255;
    im2.red[2][3]=255;
    im2.red[2][4]=255;
    int compteur_red;
    int tab_red[im->x][im->y];
    int max_pix=255;
    for (int i=0;i<(im->x);i++) {
        for (int j=0;j<(im->y);j++) {
            tab_red[i][j]=im->red[i][j];
        }
    }
    for (int i=0;i<(im->x)-cr.x;i++) {
        for (int j=0;j<(im->y)-cr.y;j++) {
            max_pix=255;
            for (int k=0;k<cr.x;k++) {
                for (int l=0;l<cr.y;l++){
                    if (im2.red[k][l]==0) {
                        if (tab_red[i+k-(cr.x)/2][j+l-cr.y/2]<max_pix) {
                            max_pix=tab_red[i+k-(cr.x)/2][j+l-cr.y/2];
                        }
                    }
                }
                im->red[i][j]=max_pix;
                im->green[i][j]=max_pix;
                im->blue[i][j]=max_pix;
            }
        }
    }
}

//Fonction zoom
/* Auteur : Pierre-Antoine */
/* Date :   05/06 */
/* Résumé : effectue un zoom * 2 sur l'image en entrée*/
/* Entrée(s) :  image* im*/
/* Sortie(s) :   */
void zoom(image* im){
    image im2;
    int a, b;
    a=0;
    b=0;
    im2.x=im->x/2;
    im2.y=im->y/2;
    im2.red=(int**)malloc(im2.x *sizeof(int*)); //on alloue les different pixel en fonction de la nouvelle resolution
    for (int g = 0; g < im2.x; g++) {
        im2.red[g]=(int*)malloc(im2.y *sizeof(int));
    }
    im2.green=(int**)malloc(im2.x *sizeof(int*));
    for (int h = 0; h < im2.x; h++) {
        im2.green[h]=(int*)malloc(im2.y *sizeof(int));
    }
    im2.blue=(int**)malloc(im2.x *sizeof(int*));
    for (int f = 0; f < im2.x; f++) {
        im2.blue[f]=(int*)malloc(im2.y *sizeof(int));
    }
      for(int i=0; i<im2.x; i++) {   // on transpose les pixels de l'image de base vers l'image de transition
        for(int j=0; j<im2.y; j++) {
            im2.red[i][j]=im->red[i+(im2.x/2)][j+(im2.y/2)];
            im2.green[i][j]=im->green[i+(im2.x/2)][j+(im2.y/2)];
            im2.blue[i][j]=im->blue[i+(im2.x/2)][j+(im2.y/2)];
        }
    }
    /*
    im->red = realloc(im->red, im2.x *sizeof(int*)); // on realloue la largeur et la longueur de l'image de base
    for (int g = 0; g < im2.x; g++) {
        im->red[g] = realloc(im->red[g], im2.y *sizeof(int));
    }
    im->green = realloc(im->green, im2.x *sizeof(int*));
    for (int g = 0; g < im2.x; g++) {
        im->green[g] = realloc(im->green[g], im2.y *sizeof(int));
    }
    im->blue = realloc(im->blue, im2.x *sizeof(int*));
    for (int g = 0; g < im2.x; g++) {
        im->blue[g] = realloc(im->blue[g], im2.y *sizeof(int));
    }*/
    

    for(int i=0; i<im2.y; i++) {  // on applique les couleurs de l'image de transition sur l'image de base
        for(int j=0; j<im2.x; j++) {
            if (j==im2.x){
                a=1;
            }
            if (i==im2.y){
                b=1;
            }
            im->red[2*j][2*i]=im2.red[j][i];
            im->red[2*j+1][2*i]=im2.red[j][i];
            im->red[2*j][2*i+1]=im2.red[j][i];
            im->red[2*j+1][2*i+1]=im2.red[j][i];

                im->green[2*j][2*i]=im2.green[j][i];
                im->green[2*j+1][2*i]=im2.green[j][i];
                im->green[2*j][2*i+1]=im2.green[j][i];
                im->green[2*j+1][2*i+1]=im2.green[j][i];
                
                im->blue[2*j][2*i]=im2.blue[j][i];
                im->blue[2*j+1][2*i]=im2.blue[j][i];
                im->blue[2*j][2*i+1]=im2.blue[j][i];
                im->blue[2*j+1][2*i+1]=im2.blue[j][i];
            }
    }
    freeimage(&im2); 
}

//Fonction dézoom
/* Auteur : Pierre-Antoine */
/* Date :   05/06 */
/* Résumé : effectue un dézoom /2 sur l'image en entrée*/
/* Entrée(s) :  image* im*/
/* Sortie(s) :   */
void dezoom(image* im){
    image im2;
    im2.x=im->x/2;
    im2.y=im->y/2;
    im2.red=(int**)malloc(im2.x *sizeof(int*)); //on alloue les different pixel en fonction de la nouvelle resolution
    for (int g = 0; g < im2.x; g++) {
        im2.red[g]=(int*)malloc(im2.y *sizeof(int));
    }
    im2.green=(int**)malloc(im2.x *sizeof(int*));
    for (int h = 0; h < im2.x; h++) {
        im2.green[h]=(int*)malloc(im2.y *sizeof(int));
    }
    im2.blue=(int**)malloc(im2.x *sizeof(int*));
    for (int f = 0; f < im2.x; f++) {
        im2.blue[f]=(int*)malloc(im2.y *sizeof(int));
    }
    for(int i=0; i<im2.y; i++) {   // on transpose les pixels de l'image de base vers l'image de transition
        for(int j=0; j<im2.x; j++) {
           im2.red[j][i]=(im->red[2*j][2*i]+im->red[2*j+1][2*i]+im->red[2*j][2*i+1]+im->red[2*j+1][2*i+1])/4;
           im2.green[j][i]=(im->green[2*j][2*i]+im->green[2*j+1][2*i]+im->green[2*j][2*i+1]+im->green[2*j+1][2*i+1])/4;
           im2.blue[j][i]=(im->blue[2*j][2*i]+im->blue[2*j+1][2*i]+im->blue[2*j][2*i+1]+im->blue[2*j+1][2*i+1])/4;
        }
    }
    for(int i=0; i<im2.y; i++) {  // on applique les couleurs de l'image de transition sur l'image de base
            for(int j=0; j<im2.x; j++) {
                 im->red[2*j][2*i]=im2.red[j][i];
                 im->red[2*j+1][2*i]=im2.red[j][i];
                 im->red[2*j][2*i+1]=im2.red[j][i];
                 im->red[2*j+1][2*i+1]=im2.red[j][i];
            
               
               
                im->green[2*j][2*i]=im2.green[j][i];
                im->green[2*j+1][2*i]=im2.green[j][i];
                im->green[2*j][2*i+1]=im2.green[j][i];
                im->green[2*j+1][2*i+1]=im2.green[j][i];
                
                
                
                im->blue[2*j][2*i]=im2.blue[j][i];
                im->blue[2*j+1][2*i]=im2.blue[j][i];
                im->blue[2*j][2*i+1]=im2.blue[j][i];
                im->blue[2*j+1][2*i+1]=im2.blue[j][i];
            }
     }
    freeimage(&im2);
}
    
