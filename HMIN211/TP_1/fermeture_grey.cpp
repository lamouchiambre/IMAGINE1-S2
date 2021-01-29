///
// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

bool est_dans_object(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8){
    //printf("%d",v1+v2+v3+v4+v5+v6+v7+v8);
    return v1+v2+v3+v4+v5+v6+v7+v8 > 0;
}

int max_(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8){
    int max = v1;
    int tab[8];
    tab[0] = v1;
    tab[1] = v2;
    tab[2] = v3;
    tab[3] = v4;
    tab[4] = v5;
    tab[5] = v6;
    tab[6] = v7;
    tab[7] = v8;

    for (int i = 0; i < 8; i++)
    {
        if (max < tab[i]){
            max = tab[i];
        }
    }

    return max;
}

int min_(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8){
    int min = v1;
    int tab[8];
    tab[0] = v1;
    tab[1] = v2;
    tab[2] = v3;
    tab[3] = v4;
    tab[4] = v5;
    tab[5] = v6;
    tab[6] = v7;
    tab[7] = v8;

    for (int i = 0; i < 8; i++)
    {
        if (min > tab[i]){
            min = tab[i];
        }
    }
    
    return min;
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S;
  int v1, v2, v3,v4 ,v5 , v6, v7, v8;
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
   //lire_image_pgm(cNomImgLue, ImgOut, nH * nW);

for (int i=0; i < nTaille; i++)
    ImgOut[i] = 0;

 for (int i=1; i < nH-1; i++)
   for (int j=1; j < nW-1; j++)
     {  
         //p = ImgIn[i*nW+j]
         v1 = ImgIn[(i-1)*nW+j-1];
         v2 = ImgIn[(i)*nW+j-1];
         v3 = ImgIn[(i+1)*nW+j-1];
         v4 = ImgIn[(i-1)*nW+j];
         v5 = ImgIn[(i+1)*nW+j];
         v6 = ImgIn[(i-1)*nW+j+1];
         v7 = ImgIn[(i)*nW+j+1];
         v8 = ImgIn[(i+1)*nW+j+1];

        ImgOut[i*nW+j] = max_(v1, v2, v3, v4, v5, v6, v7, v8);
     }

for (int i=0; i < nTaille; i++)
    ImgIn[i] = ImgOut[i];

 for (int i=1; i < nH-1; i++)
   for (int j=1; j < nW-1; j++)
     {  
         //p = ImgIn[i*nW+j]
         v1 = ImgIn[(i-1)*nW+j-1];
         v2 = ImgIn[(i)*nW+j-1];
         v3 = ImgIn[(i+1)*nW+j-1];
         v4 = ImgIn[(i-1)*nW+j];
         v5 = ImgIn[(i+1)*nW+j];
         v6 = ImgIn[(i-1)*nW+j+1];
         v7 = ImgIn[(i)*nW+j+1];
         v8 = ImgIn[(i+1)*nW+j+1];

        ImgOut[i*nW+j] = min_(v1, v2, v3, v4, v5, v6, v7, v8);
     }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}