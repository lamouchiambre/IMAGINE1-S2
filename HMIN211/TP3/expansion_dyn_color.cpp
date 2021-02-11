// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nV, nB;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
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
	
    //allocation histogramme
    int *tabHistoR, *tabHistoV, *tabHistoB;
    allocation_tableau(tabHistoR, int, 256);
    allocation_tableau(tabHistoV, int, 256);
    allocation_tableau(tabHistoB, int, 256);
    
    for(int i = 0; i < 255; i++){
        tabHistoR[i] = 0;
        tabHistoV[i] = 0;
        tabHistoB[i] = 0;
    }
    for (int i=0; i < nTaille3; i+=3)
    {
        tabHistoR[ImgIn[i]]++;
        tabHistoV[ImgIn[i+1]]++;
        tabHistoB[ImgIn[i+2]]++;
        //ImgOut[i]=255;
        //ImgOut[i+1]=255; 
        //ImgOut[i+2]=255;
    }

    //calcule 
    // r0 r1, v0 v1, b0 b1
    int r0 = -1;
    int r1 = -1;
    int v0 = -1;
    int v1 = -1;
    int b0 = -1;
    int b1 = -1;
    for (int i = 0; i < 255; i++)
    {
      if (r0 == -1 && tabHistoR[i] != 0 )
      {
        r0 = i;
      }
      if (v0 == -1 && tabHistoV[i] != 0 )
      {
        v0 = i;
      }
      if (b0 == -1 && tabHistoB[i] != 0 )
      {
        b0 = i;
      }
    }
    /*___________________*/
    for (int i = 255; i >= 0; i--)
    {
      if (r1 == -1 && tabHistoR[i] != 0 )
      {
        r1 = i;
      }
      if (v1 == -1 && tabHistoV[i] != 0 )
      {
        v1 = i;
      }
      if (b1 == -1 && tabHistoB[i] != 0 )
      {
        b1 = i;
      }
    }

    double b_r = (double)(255.0*r0)/(double)(r1-r0);
    double a_r = (255)/(double)(r1-r0);

    double b_v = (double)(255.0*v0)/(double)(v1-v0);
    double a_v = (255)/(double)(v1-v0);

    double b_b = (double)(255.0*b0)/(double)(b1-b0);
    double a_b = (255)/(double)(b1-b0);
    printf("alpha R : %f | beta R : %f\n", a_r, b_r);
    printf("alpha V : %f | beta V : %f\n", a_v, b_v);
    printf("alpha B : %f | beta B : %f\n", a_b, b_b);
    for (int i=0; i < nTaille3; i+=3)
     {
       nR = ImgIn[i];
       nV = ImgIn[i+1];
       nB = ImgIn[i+2];
       ImgOut[i]= nR*a_r +b_r;
       ImgOut[i+1]= nV*a_v +b_v; 
       ImgOut[i+2]= nB*a_b +b_b;
     }
/*
void expansion(ImagePGM& image, int min, int max) {
	for (OCTET& o : image)
		o = (OCTET)round(255.0 / ((double)(max - min)) * ((double)(-min + o)));
}
*/
   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
