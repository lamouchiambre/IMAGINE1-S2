// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250], cNomImgBin[250];
  int nH, nW, nTaille, nR, nG, nB, S;
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn. ImageBin ImageOut.ppm Seuil \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgBin);
   sscanf (argv[3],"%s",cNomImgEcrite);
   //sscanf (argv[3],"%d",&S);

   OCTET *ImgIn, *ImgOut, *ImgBin;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);

   allocation_tableau(ImgBin, OCTET, nTaille);
   lire_image_pgm(cNomImgBin, ImgBin, nH * nW);

    printf("-euh...-------\n");
  int j = 0;

   for (int i=nW*3; i < nTaille3-nW*3; i+=3)
    {
        nR = ImgIn[i];
        nG = ImgIn[i+1];
        nB = ImgIn[i+2];
       
        int pR = (
            ImgIn[i-3+nW*3] +
            ImgIn[i+nW*3] +
            ImgIn[i+3+nW*3] +
            ImgIn[i+3] +
            ImgIn[i] +
            ImgIn[i-3] +
            ImgIn[i-3-nW*3] +
            ImgIn[i-nW*3] +
            ImgIn[i+3-nW*3]
        )/9;
        
        int pG = (
            ImgIn[i-3+nW*3+1] +
            ImgIn[i+nW*3+1] +
            ImgIn[i+3+nW*3+1] +
            ImgIn[i+3+1] +
            ImgIn[i+1] +
            ImgIn[i-3+1] +
            ImgIn[i-3-nW*3+1] +
            ImgIn[i-nW*3+1] +
            ImgIn[i+3-nW*3+1]
        )/9;

        int pB = (
            ImgIn[i-3+nW*3+2] +
            ImgIn[i+nW*3+2] +
            ImgIn[i+3+nW*3+2] +
            ImgIn[i+3+2] +
            ImgIn[i+2] +
            ImgIn[i-3+2] +
            ImgIn[i-3-nW*3+2] +
            ImgIn[i-nW*3+2] +
            ImgIn[i+3-nW*3+2]
        )/9;

        if (ImgBin[j] != 0)
        {
            ImgOut[i] = pR;
            ImgOut[i+1] = pG;
            ImgOut[i+2] = pB;
        }else
        {
            ImgOut[i] = ImgIn[i];
            ImgOut[i+1] = ImgIn[i+1];
            ImgOut[i+2] = ImgIn[i+2];
        }
        
        
        j ++;

    }
    

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
