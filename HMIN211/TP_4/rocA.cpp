#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImglue2[250];
  int nH, nW, nTaille, S;

  if (argc != 4)
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n");
       exit (1) ;
     }

   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImglue2);
   sscanf (argv[3],"%d",&S);

   OCTET *ImgIn, *ImgOut;

   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

   allocation_tableau(ImgOut, OCTET, nTaille);
   lire_image_pgm(cNomImglue2, ImgOut, nH * nW);

   int VP = 0;
   int FP = 0;
   int VN = 0;
   int FN = 0;


 for (int i=0; i < nH; i++)
   for (int j=0; j < nW; j++)
     {
       if(ImgOut[i*nW+j]==ImgIn[i*nW+j] && ImgIn[i*nW+j]==0){
        VP++;
       }else if(ImgOut[i*nW+j]==ImgIn[i*nW+j] && ImgIn[i*nW+j]==255){
        VN++;
       }
       else if(ImgOut[i*nW+j]!=ImgIn[i*nW+j] && ImgIn[i*nW+j]==0 && ImgOut[i*nW+j]==255){
        FP++;
       }
       else if(ImgOut[i*nW+j]!=ImgIn[i*nW+j] && ImgIn[i*nW+j]==255 && ImgOut[i*nW+j]==0){
        FN++;
       }

     }

     double sensi = (double)VP/(double)(VP + FN);
     double speci = (double)VN/(double)(VN + FP);


   //ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
     printf("SEUIL : %d , VP : %d , VN : %d ,FP : %d , FN : %d , SENSIBILITE : %f , SPECIFICITE : %f\n",S, VP, VN, FP, FN, sensi, 1-speci );



   free(ImgIn);
   free(ImgOut);
   return 1;
}