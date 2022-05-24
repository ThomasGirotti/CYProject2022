void negatif(image img){
  int x;
  int y;
  x=img.x;
  y=img.y;
  for(int i=0; i<x;i++){ // on balye les lignes
    for(int j=0; j<y;j++){ // on baleye les collones
      img.pixel.red[i][j]= 255-img.pixel.red[i][j];
      img.pixel.green[i][j]= 255-img.pixel.green[i][j];
      img.pixel.blue[i][j]= 255-img.pixel.blue[i][j];
      }
    }
  }  
}
