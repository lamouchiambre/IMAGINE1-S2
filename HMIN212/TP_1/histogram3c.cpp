// histogram_pgm.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char* argv[]){
    char cNomImgLue[250], cNomImgEcrite[250], couleur[250], rouge[250];
    int nH, nW, nTaille, S;
    int indice;
    //colonne 1; ligne 0

    if (argc != 3) 
    {
        printf("Usage: ImageIn.pgm couleur \n"); 
        exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",couleur);
    sscanf ("R","%s",rouge);
    // //sscanf (argv[4],"%s",type);



    OCTET *ImgIn;
    int * tabHistoR, * tabHistoV, * tabHistoB;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);

    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(tabHistoR, int, 256);
    allocation_tableau(tabHistoV, int, 256);
    allocation_tableau(tabHistoB, int, 256);

    //lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    for(int i = 0; i < 256; i++){
        tabHistoR[i] = 0;
        tabHistoV[i] = 0;
        tabHistoB[i] = 0;
    }

    for (int i=0; i < nTaille3; i+=3){

        tabHistoR[ImgIn[i]] += 1;
        tabHistoV[ImgIn[i+1]] += 1;
        tabHistoB[ImgIn[i+2]] += 1;
        //printf("%d %d %d %d\n", i, tabHistoR[ImgIn[i]], tabHistoV[ImgIn[i+1]], tabHistoB[ImgIn[i+2]]);
    }

        //afficher les tableaux
    for (int i = 0; i < 256; i++){
        printf("%d %d %d %d\n", i, tabHistoR[i], tabHistoV[i], tabHistoB[i]);
    }

    // if (strcmp("R", couleur)==0)
    // {   
    //     printf("c'est rouge \n");
    //     for (int i = 0; i < 256; i++)
    //     {
    //         printf("r %d %d \n", i, tabHistoR[i]);
    //     }
    // }else
    // {
    //     if (strcmp(couleur,"B"))
    //     {
    //         for (int i = 0; i < 256; i++)
    //         {
    //             printf("b %d %d \n", i, tabHistoV[i]);
    //         }
    //     }else{
    //         for (int i = 0; i < 256; i++)
    //         {
    //             printf("v %d %d \n", i, tabHistoB[i]);
    //         }
    //     }
    // }

}