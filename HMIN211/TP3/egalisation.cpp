// histogram_pgm.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char* argv[]){
    char cNomImgLue[250], cNomImgEcrite[250], type[250];
    int nH, nW, nTaille, S;
    int indice;
    //colonne 1; ligne 0
  
    if (argc != 3) 
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
        exit (1) ;
    }
   
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);
    //sscanf (argv[3],"%d",&indice);
    //sscanf (argv[4],"%s",type);
    

    OCTET *ImgIn, *ImgOut;
    int *tabHisto, *T;
    double *densitee;
   
    //printf("here");
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    allocation_tableau(tabHisto, int, 256);
    allocation_tableau(densitee, double, 256);
    allocation_tableau(T, int, 256);

    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    
    for(int i = 0; i < 256; i++){
        tabHisto[i] = 0;
    }

    for (int i=0; i < nH; i++)
        for (int j=0; j < nW; j++)
            tabHisto[ImgIn[i*nW+j]] += 1;
        
    double sum_d = 0.0;
    for (int i = 0; i < 256; i++)
    {
        //printf("%d %d \n", i, tabHisto[i]);
        densitee[i] = (double)tabHisto[i]/(double)nTaille;
        T[i] = 0;
        double sum = 0.0;
        for(int j = 0; j <= i ; j++ ){
            sum+=densitee[j];
        }
        T[i] = sum*255; 
        sum_d += sum;
        //printf("T = %i %f %i\n", i , sum, T[i]);
        printf("%i %f\n", i,densitee[i]);//sum);
        //densitee[i]);
        //T[i] );
    }

    for (int i=0; i < nH; i++)
        for (int j=0; j < nW; j++)
            ImgOut[i*nW+j] = T[ImgIn[i*nW+j]];
    
    /*--------------------------------*/
    for(int i = 0; i < 256; i++){
        tabHisto[i] = 0;
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
}