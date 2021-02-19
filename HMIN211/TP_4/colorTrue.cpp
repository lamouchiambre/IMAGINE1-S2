// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, S;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm Seuil \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   //sscanf (argv[3],"%d",&S);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);

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
            ImgIn[i+3+nW*3+2] 
            ImgIn[i+3+2] +
            ImgIn[i+2] +
            ImgIn[i-3+2] +
            ImgIn[i-3-nW*3+2] +
            ImgIn[i-nW*3+2] +
            ImgIn[i+3-nW*3+2]
        )/9;

        ImgOut[i] = pR;
        ImgOut[i+1] = pG;
        ImgOut[i+2] = pB;

     }

//    for (int i=0; i < nTaille3; i+=3)
//      {
//        nR = ImgIn[i];
//        nG = ImgIn[i+1];
//        nB = ImgIn[i+2];
//        ImgOut[j] = (nR+nG+nB)/3;
//         //j ++;
//      }
/*
    for (int i = 1; i < nH-1; i++)
    {
        for (int j = 1; j < (nW-1)*3; j+=3)
        {
            //for (int k = 0; i < 3; i++)
            //{
                nR =(
                    ImgIn[(i-1)*nW*3+(j-1)] +
                    ImgIn[(i-1)*nW*3+j] +
                    ImgIn[(i-1)*nW*3+(j+1)] +
                    ImgIn[i*nW*3+(j-1)] +
                    ImgIn[i*nW*3+j] +
                    ImgIn[i*nW*3+(j+1)] +
                    ImgIn[(i+1)*nW*3+(j-1)] +
                    ImgIn[(i+1)*nW*3+j] +
                    ImgIn[(i+1)*nW*3+(j+1)]

                )/9;
                nG =(
                    ImgIn[(i-1)*nW*3+(j-1)+1] +
                    ImgIn[(i-1)*nW*3+j+1] +
                    ImgIn[(i-1)*nW*3+(j+1)+1] +
                    ImgIn[i*nW*3+(j-1)+1] +
                    ImgIn[i*nW*3+j+1] +
                    ImgIn[i*nW*3+(j+1)+1] +
                    ImgIn[(i+1)*nW*3+(j-1)+1] +
                    ImgIn[(i+1)*nW*3+j+1] +
                    ImgIn[(i+1)*nW*3+(j+1)+1]

                )/9;
                // ImgIn[i*nW*3+j+1];
                nB = (
                    ImgIn[(i-1)*nW*3+(j-1)+2] +
                    ImgIn[(i-1)*nW*3+j+2] +
                    ImgIn[(i-1)*nW*3+(j+1)+2] +
                    ImgIn[i*nW*3+(j-1)+2] +
                    ImgIn[i*nW*3+j+2] +
                    ImgIn[i*nW*3+(j+1)+2] +
                    ImgIn[(i+1)*nW*3+(j-1)+2] +
                    ImgIn[(i+1)*nW*3+j+2] +
                    ImgIn[(i+1)*nW*3+(j+1)+2]
                )/9;
                 //ImgIn[i*nW*3+j+2];
                ImgOut[i*nW*3+j] = nR;
                ImgOut[i*nW*3+j+1] = nG;
                ImgOut[i*nW*3+j+2] = nB;
            //}
        }
    }
*/
    //-------------------------------------------//

    

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
