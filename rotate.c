/*

typedef struct image{
  int x;
  int y;
  pix pixel;
}

typedef struct pix{
  int red[x][y];
  int green[x][y];
  int blue[x][y];
}
*/

image rotate(image im){
  image imrotate;

  imrotate.x = im.y;
  imrotate.y = im.x;
  
  for(int i=0; i<=im.y; i++){
    for(int j=0; j<=im.x; j++){
      imrotate.pixel.red[i][j]=im.pixel.red[im.y-i][j];
      imrotate.pixel.green[i][j]=im.pixel.green[im.y-i][j];
      imrotate.pixel.blue[i][j]=im.pixel.blue[im.y-i][j];
    }
  }
  return imrotate;
}
