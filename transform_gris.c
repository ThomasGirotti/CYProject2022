void transform_gris(img* image,int x,int y){
  int pixel=0; 
  for(int i=0; i<x;i++){ // on balye les lignes
    for(int j=0; j<y;j++){ // on baleye les collones
      pixel=image.red[x][y]*0.2126+image.green[x][y]*0.7152+image.blu[x][y]*0.0722; // application de la formule
      image.red[x][y]=pixel; // transforme le rouge dans la bonne teinte
      image.green[x][y]=pixel; // transforme le vert dans la bonne teinte
      image.blue[x][y]=pixel; // transforme le bleu dans la bonne teinte
    }
  }  
}
