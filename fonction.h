#ifndef _A_
#define _A_
//Definition Structure
typedef struct image{
  int** red;
  int** green;
  int** blue;
  int x;
  int y;
} image;

//Prototypage
void importimage(char* inputname,image image);


#endif