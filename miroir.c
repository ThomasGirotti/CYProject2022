
void miroir(image img){
  int pixel=0;
  int x;
  int y;
  x=img.x;
  y=img.y;
  for(int i=0; i<x;i++){ // on balye les lignes
    for(int j=0; j<y;j++){ // on baleye les collones
      pixel=img.red[img.x][img.y]*0.2126+img.green[img.x][img.y]*0.7152+img.blu[img.x][img.y]*0.0722; // application de la formule
      img.pixel.red[x][y]=pixel; // transforme le rouge dans la bonne teinte
      img.pixel.green[x][y]=pixel; // transforme le vert dans la bonne teinte
      img.pixel.blue[x][y]=pixel; // transforme le bleu dans la bonne teinte
    }
  }  
}
