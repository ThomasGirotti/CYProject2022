void convultion(image img, int** matrice){
  image img2;
  int compteur;
  for (int i=0;i<img.x;i++){
    for (int j=0;j<img.y;j++){
      compteur=0;
      for (int k=0;k<2;k++){
        for (int l=0;l<2;l++){
          compteur=compteur+matrice[k][l]*img*[i+k][j+l];
        }
      }
      img2[i][j]=compteur;
    }
  } 
}
