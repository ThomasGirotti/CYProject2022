
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>


void recadyna(image im){
  int del;
  int* tab;
  int max;
  int min;
  tab = (int*)malloc(255*sizeof(int));
  tab = histograme(im);
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
      im.red[i][y]=(im.red[i][y]-min)*del;
      im.green[i][y]=(im.green[i][y]-min)*del;
      im.blue[i][y]=(im.blue[i][y]-min)*del;
    }
  }
}
