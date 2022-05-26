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

//Prototypage
void importimage(char* inputname,image* im);
int exportimage(char* outputname,image* im);
void printimage(image* im);

void binaire(image im,int seuil);
int* histogramme(image im);
void miroir(image im);
void negatif(image im);
void recadyna(image im);
void recadrage(image im,int tab[255]);
image rotate(image im);
void transform_gris(image im);

#endif