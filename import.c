void importimage(char* inputname,image image) {

    int maxvalue;
    char* laLigne;
    FILE* file = NULL;

    laLigne=(char*)malloc(sizeof(char)*20);

//Ouverture du fichier
    file = fopen(inputname,"r");
    printf("file name is %s\n", inputname);

//Vérification de l'ouverture du fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }

//Vérification du format du fichier
    fscanf(file,"%s\n",laLigne);
    printf("%s",laLigne);
    if (strcmp(laLigne, "P3") != 0) {
        printf("Erreur : Le fichier n'est pas au format PPM P3\n");
        exit(1);
    }

//Récupération de la résolution
    fseek(file, 2, SEEK_SET);
    fscanf(file, "%d %d\n",&image.x,&image.y);
    printf("%d %d\n",image.x,image.y);

//Récupération de la max value d'un pixel
    fscanf(file,"%d",&maxvalue);
    printf("%d\n",maxvalue);

//Initialisation du tableau
    image.red=(int**)malloc(image.y *sizeof(int*));
    for (int g = 0; g <= image.y; g++) {
        image.red[g]=(int*)malloc(image.x *sizeof(int));
    }
    image.green=(int**)malloc(image.y *sizeof(int*));
    for (int g = 0; g <= image.y; g++) {
        image.green[g]=(int*)malloc(image.x *sizeof(int));
    }
    image.blue=(int**)malloc(image.y *sizeof(int*));
    for (int g = 0; g <= image.y; g++) {
        image.blue[g]=(int*)malloc(image.x *sizeof(int));
    }

//Récupératiion des pixel
    for(int i=0; i<=image.y; i++) {
        for (int j = 0; j <=image.x; j++) {
            fscanf(file,"%d\n",&image.red[i][j]);
            fscanf(file,"%d\n",&image.green[i][j]);
            fscanf(file,"%d\n",&image.blue[i][j]);
        }
    }

    for(int i=0; i<image.y; i++) {
        for (int j = 0; j <image.x; j++) {
            printf("%d\n",image.red[i][j]);
            printf("%d\n",image.green[i][j]);
            printf("%d\n",image.blue[i][j]);
        }
    }

    printf("%d %d %d \n",image.red[254][252],image.green[254][252],image.blue[254][252]);
    printf("%d %d %d \n",image.red[254][253],image.green[254][253],image.blue[254][253]);
    printf("%d %d %d \n",image.red[254][254],image.green[254][254],image.blue[254][254]);
    printf("%d %d %d \n",image.red[255][0],image.green[255][0],image.blue[255][0]);
}
