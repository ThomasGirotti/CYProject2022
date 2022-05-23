
void miroir(image img){
  int pixel_red=0;
  int pixel_green=0;
  int pixel_blue=0;
  int x;
  int y;
  x=img.x;
  y=img.y;
  for(int i=0; i<x;i++){ // on balye les lignes
    for(int j=0; j<y/2;j++){ // on baleye les collones
      pixel_red=img.pixel.red[i][j]; // on stocke les valeur
      pixel_green=img.pixel.red[i][j];
      pixel_blue=img.pixel.red[i][j];
      img.pixel.red[i][j]=img.pixel.red[i][y-j]; // on met la partie de droite à gauche    
      img.pixel.green[i][j]=img.pixel.green[i][y-j];       
      img.pixel.blue[i][j]=img.pixel.blue[i][y-j];
      img.pixel.red[i][j]=pixel_red;  // on met la partie de gauche (stocké) à droite
      img.pixel.green[i][j]=pixel_green;      
      img.pixel.blue[i][j]=pixel_blue;
    }
  }  
}
