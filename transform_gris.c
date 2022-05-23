void transform_gris(img* image,int x,int y){
  int pixel=0;
  for(int i=0; i<x;i++){
    for(int j=0; j<y;j++){
      pixel=image.red[x][y]*0.2126+image.green[x][y]*0.7152+image.blu[x][y]*0.0722;
      image.red[x][y]=pixel;
      image.green[x][y]=pixel
      image.blue[x][y]=pixel
    }
  }  
}
