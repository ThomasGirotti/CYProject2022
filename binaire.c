void binaire(image img,int seuil){
  int pixel=0;
  int x;
  int y;
  x=img.x;
  y=img.y;
  for(int i=0; i<x;i++){ // on balye les lignes
    for(int j=0; j<y;j++){ // on baleye les collones
      if (((img.pixel.red[i][j]+img.pixel.green[i][j]+img.pixel.blue[i][j])/3)<seuil){
        img.pixel.red[i][j]=0; // transforme le rouge en 
        img.pixel.green[i][j]=0; // transforme le vert dans la bonne teinte
        img.pixel.blue[i][j]=0; // transforme le bleu dans la bonne teinte
      }
      else{
        img.pixel.red[i][j]=255; // transforme le rouge dans la bonne teinte
        img.pixel.green[i][j]=255; // transforme le vert dans la bonne teinte
        img.pixel.blue[i][j]=255; // transforme le bleu dans la bonne teinte   
      }
    }
  }  
}
