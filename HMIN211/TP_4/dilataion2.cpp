// seuillage_couleur.cpp :  seuiller séparément chacune des trois composantes couleurs (Rouge, Vert, Bleu) de cette image

#include <stdio.h>
#include "image_ppm.h"

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
  char cNomImgLue[250], cNomImgEcrite[250], couleur[250];
  int nH, nW, nTaille, nR, nG, nB, S_R, S_G, S_B;
    int v1, v2, v3, v4 ,v5 , v6, v7, v8;
    int r1, r2, r3, r4 ,r5 , r6, r7, r8;
    int b1, b2, b3, b4 ,b5 , b6, b7, b8;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm  \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   //sscanf (argv[3],"%s",couleur);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);

for(int j = 2; j < nW*3-3; j+=3){
    for(int i = 1; i < nH*3 - 1; i++){
            //ImgOut[i*3*nW+j] = 255;
            //ImgOut[i*3*nW+j+1] = 255;
            //ImgOut[i*3*nW+j+2] = 255;
        }
}


    // for(int j = 2; j < nW*3-3; j+=3){
    //     for(int i = 1; i < nH - 1; i++){

    //         r1 = ImgIn[(i-1)*nW*3+j-1];
    //         r2 = ImgIn[(i)*nW*3+j-1];
    //         r3 = ImgIn[(i+1)*nW*3+j-1];
    //         r4 = ImgIn[(i-1)*nW*3+j];
    //         r5 = ImgIn[(i+1)*nW*3+j];
    //         r6 = ImgIn[(i-1)*nW*3+j+1];
    //         r7 = ImgIn[(i)*nW*3+j+1];
    //         r8 = ImgIn[(i+1)*nW*3+j+1];
    //         //
    //         v1 = ImgIn[(i-1)*nW*3+j-1+1];
    //         v2 = ImgIn[(i)*nW*3+j-1+1];
    //         v3 = ImgIn[(i+1)*nW*3+j-1+1];
    //         v4 = ImgIn[(i-1)*nW*3+j+1];
    //         v5 = ImgIn[(i+1)*nW*3+j+1];
    //         v6 = ImgIn[(i-1)*nW*3+j+1+1];
    //         v7 = ImgIn[(i)*nW*3+j+1+1];
    //         v8 = ImgIn[(i+1)*nW*3+j+1+1];
    //         //
    //         b1 = ImgIn[(i-1)*nW*3+j-1+2];
    //         b2 = ImgIn[(i)*nW*3+j-1+2];
    //         b3 = ImgIn[(i+1)*nW*3+j-1+2];
    //         b4 = ImgIn[(i-1)*nW*3+j+2];
    //         b5 = ImgIn[(i+1)*nW*3+j+2];
    //         b6 = ImgIn[(i-1)*nW*3+j+1+2];
    //         b7 = ImgIn[(i)*nW*3+j+1+2];
    //         b8 = ImgIn[(i+1)*nW*3+j+1+2];
    //         //
    //         ImgOut[i*nW*3+j] = min_(r1, r2, r3, r4, r5, r6, r7, r8);
    //         ImgOut[i*nW*3+j+1] = min_(v1, v2, v3, v4, v5, v6, v7, v8);
    //         ImgOut[i*nW*3+j+2] = min_(b1, b2, b3, b4, b5, b6, b7, b8);
    //     }
    // }

    for (int i = nW*3; i < nTaille3 - nW*3; i+=3)
    {
            r1 = ImgIn[i-3+nW*3];
            r2 = ImgIn[i+nW*3];
            r3 = ImgIn[i+3+nW*3];
            r4 = ImgIn[i+3] ;
            //r5 = ImgIn[i] ;
            r5 = ImgIn[i-3] ;
            r6 = ImgIn[i-3-nW*3] ;
            r7 = ImgIn[i-nW*3] ;
            r8 = ImgIn[i+3-nW*3];

            v1 = ImgIn[i-3+nW*3+1];
            v2 = ImgIn[i+nW*3+1];
            v3 = ImgIn[i+3+nW*3+1];
            v4 = ImgIn[i+3+1] ;
            v5 = ImgIn[i-3+1] ;
            v6 = ImgIn[i-3-nW*3+1] ;
            v7 = ImgIn[i-nW*3+1] ;
            v8 = ImgIn[i+3-nW*3+1];

            b1 = ImgIn[i-3+nW*3+2];
            b2 = ImgIn[i+nW*3+2];
            b3 = ImgIn[i+3+nW*3+2];
            b4 = ImgIn[i+3+2] ;
            b5 = ImgIn[i-3+2] ;
            b6 = ImgIn[i-3-nW*3+2] ;
            b7 = ImgIn[i-nW*3+2] ;
            b8 = ImgIn[i+3-nW*3+2];

            ImgOut[i] = max_(r1, r2, r3, r4, r5, r6, r7, r8);
            ImgOut[i+1] = max_(v1, v2, v3, v4, v5, v6, v7, v8);
            ImgOut[i+2] = max_(b1, b2, b3, b4, b5, b6, b7, b8);
    }
    

    // for (int i=2+nW; i < nTaille3-3-nW; i+=3){
    //         r1 = ImgIn[i-nW -1];
    //         r2 = ImgIn[i -1];
    //         r3 = ImgIn[i+nW -1];
    //         r4 = ImgIn[ i-nW ];
    //         r5 = ImgIn[ i+nW ];
    //         r6 = ImgIn[ i-nW +1];
    //         r7 = ImgIn[ i +1];
    //         r8 = ImgIn[ i+nW +1];
    //         //
    //         v1 = ImgIn[ i-nW-1+1];
    //         v2 = ImgIn[ i +-1+1];
    //         v3 = ImgIn[ i+nW-1+1];
    //         v4 = ImgIn[ i-nW+1];
    //         v5 = ImgIn[ i+nW+1];
    //         v6 = ImgIn[ i-nW+1+1];
    //         v7 = ImgIn[ i +1+1];
    //         v8 = ImgIn[ i+1+1];
    //         //
    //         b1 = ImgIn[i-nW-1+2];
    //         b2 = ImgIn[i-1+2];
    //         b3 = ImgIn[i+nW-1+2];
    //         b4 = ImgIn[i-nW+2];
    //         b5 = ImgIn[i+nW+2];
    //         b6 = ImgIn[i-nW+1+2];
    //         b7 = ImgIn[i+1+2];
    //         b8 = ImgIn[i+nW+1+2];
    //         //
    //         ImgOut[i] = max_(r1, r2, r3, r4, r5, r6, r7, r8);
    //         ImgOut[i+1] = max_(v1, v2, v3, v4, v5, v6, v7, v8);
    //         ImgOut[i+2] = max_(b1, b2, b3, b4, b5, b6, b7, b8);
    // }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}