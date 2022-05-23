void transform_gris(image img){
  int pixel=0;
  int x;
  int y;
  x=img.x;
  y=img.y;
  for(int i=0; i<x;i++){ // on balye les lignes
    for(int j=0; j<y;j++){ // on baleye les collones
      pixel=img.red[i][j]*0.2126+img.green[i][j]*0.7152+img.blu[i][j]*0.0722; // application de la formule
      img.pixel.red[i][j]=pixel; // transforme le rouge dans la bonne teinte
      img.pixel.green[i][j]=pixel; // transforme le vert dans la bonne teinte
      img.pixel.blue[i][j]=pixel; // transforme le bleu dans la bonne teinte
    }
  }  
}
