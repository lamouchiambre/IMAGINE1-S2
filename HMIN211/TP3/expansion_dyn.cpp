// a voir http://bnazarian.free.fr/MyUploads/IN_GBM_03_PRE_TRAITEMENTS.PDF
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   //sscanf (argv[3],"%d",&S);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

    //calcule de l'histogramme
    int * tabHisto;
    allocation_tableau(tabHisto, int, 256);

    for (int i=0; i < nH; i++)
        for (int j=0; j < nW; j++)
            tabHisto[ImgIn[i*nW+j]] += 1;
    
    //permiere etape determiner Vo et V1
    int v0=-1;
    int v1=-1;
    for (int i = 0; i < 255; i++)
    {
      if (v0 == -1 && tabHisto[i] != 0 )
      {
        v0 = i;
      }
    }

    for (int i = 255; i >= 0; i--)
    {
      printf("%d - %d\n",i ,tabHisto[i]);
      if (v1 == -1 && tabHisto[i] != 0 )
      {
        printf("je suis la\n");
        v1 = i;
      }
    }
    printf("v0 : %d | v1 : %d\n", v0, v1);
    //deuxieme etape determiner les coefficient alpha et beta
    double beta = (double)(255.0*v0)/(double)(v1-v0);
    double alpha = (255)/(double)(v1-v0);
    printf("alpha : %f | beta : %f\n", alpha, beta);
    for (int i=0; i < nH; i++)
      for (int j=0; j < nW; j++)
      {
        ImgOut[i*nW+j]= (int) (ImgIn[i*nW+j]*alpha + beta);
        //printf("%i\n",  ImgOut[i*nW+j]);
      }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
