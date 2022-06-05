#ifndef _A_
#define _A_
//Definition Structure
typedef struct image{
  int** red;
  int** green;
  int** blue;
  int maxvalue;
  int x;
  int y;
} image;

typedef struct croix{
  int x;
  int y;
  int epaisseur;
  image im;
} croix;

//Prototypage
int importimage(char* inputname,image* im);
int exportimage(char* outputname,image* im);
void printimage(image* im);
void binaire(image* im,int seuil);
void contraste(image* img);
void contour(image* img);
void floutage(image* img);
void convolution(image* img, float** matrice);
void histogramme(image* im,int* tab);
void miroir(image* im);
void negatif(image* im);
void recadyna(image* im);
void rotate(image* im);
void transform_gris(image* im);
void freeimage(image* im);
void erosion(image* im,croix cr);
void dilatation(image* im,croix cr);
void zoom(image* im);
void dezoom(image* im);
#endif
