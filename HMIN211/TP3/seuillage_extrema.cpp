// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, SminR, SminG, SminB, SmaxR, SmaxG, SmaxB;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut, *ImgOut2;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);

    SminR = 20;
    SminG = 20;
    SminB = 20;
    SmaxR = 200;
    SmaxG = 200;
    SmaxB = 200;

   for (int i=0; i < nTaille3; i+=3)
    {
        nR = ImgIn[i];
        nG = ImgIn[i+1];
        nB = ImgIn[i+2];
        //rouge
        if (nR < SminR) 
        {
            ImgOut[i]=SminR;
        }
        else 
        {
            if(nR > SmaxR){
                ImgOut[i]=SmaxR;
            }
            else{
                ImgOut[i] = nR;
            }
        }
        //vert
        if (nG < SminG) 
        {
            ImgOut[i+1]=SminG;
        }
        else 
        {
            if(nG > SmaxG){
                ImgOut[i+1]=SmaxG;
            }
            else{
                ImgOut[i+1] = nG;
            }
        }
        //bleu
        if (nB < SminB) 
        {
           ImgOut[i+2]=SminB;
        }
        else 
        {
            if(nB > SmaxB){
                ImgOut[i+2]=SmaxB;
            }
            else{
                ImgOut[i+2] = nB;
            }
       }
     }

    //ecrire_image_ppm("image_dyn.ppm", ImgOut,  nH, nW);
    //___________________________________________________________//


    allocation_tableau(ImgOut2, OCTET, nTaille3);

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
        tabHistoR[ImgOut[i]]++;
        tabHistoV[ImgOut[i+1]]++;
        tabHistoB[ImgOut[i+2]]++;
    }
    
    int n_R, n_G, n_B;

    int r0 = -1;
    int r1 = -1;
    int v0 = -1;
    int v1 = -1;
    int b0 = -1;
    int b1 = -1;
    for (int i = 0; i < 255; i++)
    { 
      printf("v0 = %i et tabHistov = %i\n", v0, tabHistoV[i]);
      if (r0 == -1 && tabHistoR[i] != 0 )
      {
        r0 = i;
        printf("trouver %i \n", i);
      }
      if (v0 == -1 && tabHistoV[i] != 0)
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
    printf("%i %i \n", v0, v1);
    printf("alpha R : %f | beta R : %f\n", a_r, b_r);
    printf("alpha V : %f | beta V : %f\n", a_v, b_v);
    printf("alpha B : %f | beta B : %f\n", a_b, b_b);
    for (int i=0; i < nTaille3; i+=3)
     {
       n_R = ImgOut[i];
       n_G = ImgOut[i+1];
       n_B = ImgOut[i+2];

       if (((int) n_R*a_r +b_r) < 0)
       {
         ImgOut2[i] = 0;
       }else
       {
         if (((int) n_R*a_r +b_r) > 255)
         {
           ImgOut2[i] = 255;
         }else
         {
           ImgOut2[i] = (int) n_R*a_r +b_r;
         }
       }

       //----------------
       if (((int) n_G*a_v +b_v)<0)
       {
         ImgOut2[i] = 0;
       }else
       {
         if (((int) n_G*a_v +b_v) > 255)
         {
           ImgOut2[i+1] = 255;
         }else
         {
           ImgOut2[i+1] = (int) n_G*a_v +b_v;
         }
       }
       //----------------------
       if (((int) n_B*a_b +b_b) < 0)
       {
         ImgOut2[i+2] = 0;
       }else
       {
         if (((int) n_B*a_b +b_b) > 255)
         {
           ImgOut2[i+2] = 255;
         }else
         {
           ImgOut2[i+2] = (int) n_B*a_b +b_b;
         }
       }
       
       
      //  ImgOut2[i]= (int) n_R*a_r +b_r;
      //  ImgOut2[i+1]= (int) n_G*a_v +b_v; 
      //  ImgOut2[i+2]= (int) n_B*a_b +b_b;
     }


   ecrire_image_ppm(cNomImgEcrite, ImgOut2,  nH, nW);
   
   free(ImgIn);
   return 1;
}
