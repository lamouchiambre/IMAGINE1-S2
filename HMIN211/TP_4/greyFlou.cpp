// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250], cNomImgBin[250];
  int nH, nW, nTaille, S;

  if (argc != 4)
     {
       printf("Usage: ImageIn.pgm ImageBin.pgm ImageOut.pgm \n");
       exit (1) ;
     }

   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgBin) ;
   sscanf (argv[3],"%s",cNomImgEcrite);
   //sscanf (argv[4],"%d",&S);

   OCTET *ImgIn, *ImgOut, *ImgBin, *ImgTmp;
    printf("je suis la 1\n");
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    allocation_tableau(ImgBin, OCTET, nTaille);
    lire_image_pgm(cNomImgBin, ImgBin, nH * nW);

    allocation_tableau(ImgTmp, OCTET, nTaille);

    for (int i=1; i < (nH-1); i++)
    for (int j=1; j < (nW-1); j++)
    {
       //if ( ImgIn[i*nW+j] < S) ImgOut[i*nW+j]=0; else ImgOut[i*nW+j]=255;
       if (ImgBin[i*nW+j] != 0)
       {
             int p = (
               ImgIn[(i-1)*nW+(j-1)] +
               ImgIn[(i-1)*nW+j] +
               ImgIn[(i-1)*nW+(j+1)] +
               ImgIn[i*nW+(j-1)] +
               ImgIn[i*nW+j] +
               ImgIn[i*nW+(j+1)] +
               ImgIn[(i+1)*nW+(j-1)] +
               ImgIn[(i+1)*nW+j] +
               ImgIn[(i+1)*nW+(j+1)]
           )/9;
           //printf("p = %i\n",p );
           ImgTmp[i*nW+j] = p;
       }else
       {
           ImgTmp[i*nW+j] = ImgIn[i*nW+j];
       }
    }
    

    for (int i=1; i < (nH-1); i++)
    for (int j=1; j < (nW-1); j++)
    {
       //if ( ImgIn[i*nW+j] < S) ImgOut[i*nW+j]=0; else ImgOut[i*nW+j]=255;
       if (ImgBin[i*nW+j] != 0)
       {
             int p = (
               ImgTmp[(i-1)*nW+(j-1)] +
               ImgTmp[(i-1)*nW+j] +
               ImgTmp[(i-1)*nW+(j+1)] +
               ImgTmp[i*nW+(j-1)] +
               ImgTmp[i*nW+j] +
               ImgTmp[i*nW+(j+1)] +
               ImgTmp[(i+1)*nW+(j-1)] +
               ImgTmp[(i+1)*nW+j] +
               ImgTmp[(i+1)*nW+(j+1)]
           )/9;
           //printf("p = %i\n",p );
           ImgOut[i*nW+j] = p;
       }else
       {
           ImgOut[i*nW+j] = ImgIn[i*nW+j];
       }
    }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
