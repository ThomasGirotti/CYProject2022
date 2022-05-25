int* histograme(image img){
  int* tab;
  int x;
  int y;
  tab = malloc(255*sizeof(int));
  x=img.x;
  y=img.y;
  for(int i=0; i<x;i++){ // on balaie les lignes
    for(int j=0; j<y;j++){ // on balaie les colonnes
      tab[img.pixel.red[i][j]]=+1
      }
    }
  return tab
}  
}
