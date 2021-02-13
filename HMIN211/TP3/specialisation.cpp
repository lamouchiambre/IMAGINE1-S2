// histogram_pgm.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char* argv[]){
    char cNomImgLue[250], cNomImgEcrite[250], cNomImgRef[250];
    int nH, nW, nTaille, S;
    int indice;
    //colonne 1; ligne 0
  
    if (argc != 4) 
    {
        printf("Usage: ImageRef.pgm ImageIn.pgm ImageOut.pgm \n"); 
        exit (1) ;
    }
   
    sscanf (argv[1],"%s",cNomImgRef);
    sscanf (argv[2],"%s",cNomImgLue);
    sscanf (argv[3],"%s",cNomImgEcrite);    

    OCTET *ImgIn, *ImgOut, *ImgOutspe, *ImgRef, *ImgOutRef;
    int *tabHisto, *T, *tabHistoRef, *T_ref, *T_ref_inv;
    double *densitee, *densiteeRef;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nHr, nWr, nTailleRef;
    lire_nb_lignes_colonnes_image_pgm(cNomImgRef, &nHr, &nWr);
    nTailleRef = nHr * nWr;

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);
    allocation_tableau(ImgOutspe, OCTET, nTaille);
    allocation_tableau(ImgRef, OCTET, nTaille);
    allocation_tableau(ImgOutRef, OCTET, nTaille);

    allocation_tableau(tabHistoRef, int, 256);
    allocation_tableau(tabHisto, int, 256);
    allocation_tableau(densiteeRef, double, 256);
    allocation_tableau(densitee, double, 256);
    allocation_tableau(T, int, 256);
    allocation_tableau(T_ref, int, 256);
    allocation_tableau(T_ref_inv, int, 256);

    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    lire_image_pgm(cNomImgRef, ImgRef, nHr * nWr);
    
    for(int i = 0; i < 256; i++){
        tabHisto[i] = 0;
        tabHistoRef[i] = 0;
    }

    for (int i=0; i < nH; i++)
        for (int j=0; j < nW; j++)
            tabHisto[ImgIn[i*nW+j]] += 1;
            
    for (int i=0; i < nHr; i++)
        for (int j=0; j < nWr; j++)
            tabHistoRef[ImgRef[i+nWr+j]] +=1;
        
    for (int i = 0; i < 256; i++)
    {
        printf("%d %d \n", i, tabHistoRef[i]);
        densitee[i] = (double)tabHisto[i]/(double)nTaille;
        densiteeRef[i] = (double)tabHistoRef[i]/(double)nTailleRef;
        T[i] = 0;
        T_ref[i] = 0;
        double sum = 0.0;
        double sumRef = 0.0;
        for(int j = 0; j <= i ; j++ ){
            sum+=densitee[j];
            sumRef+=densiteeRef[j];
        }
        T[i] = sum*255;
        T_ref[i] = sumRef*255; 
    }

    for (int i=0; i < nH; i++)
        for (int j=0; j < nW; j++)
            ImgOut[i*nW+j] = T[ImgIn[i*nW+j]];
    
    for (int i=0; i < nHr; i++)
        for (int j=0; j < nWr; j++)
            ImgOutRef[i*nWr+j] = T_ref[ImgRef[i*nWr+j]];

    /*--------------------------------*/
    for(int i = 0; i < 256; i++){
        T_ref_inv[T_ref[i]] = i;
        printf("T_ref_inv[%d] = %d\n", i, T_ref_inv[i]);
    }
    for(int i =0; i < 256; i++){
        if(T_ref_inv[i] == NULL && i != 0){
            T_ref_inv[i] = i;
        }
        printf("T_ref_inv[%d] = %d\n", i, T_ref_inv[i]);
    }
    for (int i=0; i < nH; i++)
        for (int j=0; j < nW; j++)
            ImgOutspe[i*nW + j] = T_ref_inv[ImgIn[i*nW+j]];


    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    ecrire_image_pgm("final.pgm", ImgOutspe,  nH, nW);
    ecrire_image_pgm("spe_ref_out.pgm", ImgOutRef,  nHr, nWr);
    free(ImgIn);
}