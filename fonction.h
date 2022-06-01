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

void binaire(image* im,int seuil);
void contraste(image* img);
void convolution(image* img, int** matrice,image* img2)
void histogramme(image* im,int* tab);
void miroir(image* im);
void negatif(image* im);
void recadyna(image* im);
void rotate(image* im);
void transform_gris(image* im);

#endif
