// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250], cNomImgBin[250];
  int nH, nW, nTaille, S;

  if (argc != 3)
     {
       printf("Usage: ImageInGrey.pgm ImageBin.pgm \n");
       exit (1) ;
     }

   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgBin) ;
   //sscanf (argv[3],"%s",cNomImgEcrite);
   //sscanf (argv[4],"%d",&S);

   OCTET *ImgIn, *ImgOut, *ImgBin, *ImgTmp;
    //printf("je suis la 1\n");
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   //int nTaille3 = nTaille*3;

    // lire image 
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    
    allocation_tableau(ImgTmp, OCTET, nTaille);

    allocation_tableau(ImgBin, OCTET, nTaille);
    lire_image_pgm(cNomImgBin, ImgBin, nH * nW);

    allocation_tableau(ImgTmp, OCTET, nTaille);

    int TP[256];
    int FP[256];
    int TN[256];
    int FN[256];

    for (int i = 0; i < 256; i++)
    {
        TP[i] = 0;
        FP[i] = 0;
        TN[i] = 0;
        FN[i] = 0;
    }
    

    for (int s = 0; s < 256; s++)
    {
        //calcule du seullage pour n
         for (int i=0; i < nH; i++){
            for (int j=0; j < nW; j++)
            {
                if ( ImgIn[i*nW+j] < s) ImgTmp[i*nW+j]=0; else ImgTmp[i*nW+j]=255;
            }
         }
        
        for (int i=0; i < nH; i++){
            for (int j=0; j < nW; j++)
            {
                if (ImgTmp[i*nW+j] == ImgBin[i*nW+j])
                {
                    if (ImgTmp[i*nW+j] == 0)
                    {
                        TP[s]++;
                    }else
                    {
                        TN[s]++;
                    }
                    
                    
                }else
                {
                    if (ImgTmp[i*nW+j] == 0)
                    {
                        FP[s]++;
                    }else
                    {
                        FN[s]++;
                    }
                    
                }
                
                
            }
         }
        
    }

    for (int i = 0; i < 256; i++)
    {
        double spe = (double) TP[i]/ (double)(TP[i]+FN[i]);
        double sen = (double) TN[i]/(double) (TN[i]+FP[i]);

        printf("%i %i %i %i %i %f %f\n",i, TP[i], TN[i], FP[i], FN[i],spe,sen  );
    }
    

   free(ImgIn);
   return 1;
}
