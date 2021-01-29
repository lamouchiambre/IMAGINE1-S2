///
// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

bool est_dans_le_fond(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8){
    //printf("%d",v1+v2+v3+v4+v5+v6+v7+v8);
    return v1+v2+v3+v4+v5+v6+v7+v8 > 0;
}
bool est_dans_object(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8){
    //printf("%d",v1+v2+v3+v4+v5+v6+v7+v8);
    return v1+v2+v3+v4+v5+v6+v7+v8 < 255*8;
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
   //sscanf (argv[3],"%d",&S);

   OCTET *ImgIn, *ImgDil, *ImgEro;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgDil, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgDil, nH * nW);
   
	
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }
 
    // for(i=0; i<nTaille; i++)
    //     memcpy (ImgDil[i], ImgEro[i], taille*sizeof(OCTET));

    for (int i=1; i < nH-1; i++){
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
            
            if( est_dans_object(v1, v2, v3, v4, v5, v6, v7, v8)){
                ImgDil[i*nW+j]=0;    
            } 
        }
    }

    allocation_tableau(ImgEro, OCTET, nTaille);
    ecrire_image_pgm("tp2/ero.pgm", ImgDil,  nH, nW);
    lire_image_pgm("tp2/ero.pgm", ImgEro, nH * nW);
 for (int i=1; i < nH-1; i++){
   for (int j=1; j < nW-1; j++)
     {  
         //p = ImgIn[i*nW+j]
            v1 = ImgDil[(i-1)*nW+j-1];
            v2 = ImgDil[(i)*nW+j-1];
            v3 = ImgDil[(i+1)*nW+j-1];
            v4 = ImgDil[(i-1)*nW+j];
            v5 = ImgDil[(i+1)*nW+j];
            v6 = ImgDil[(i-1)*nW+j+1];
            v7 = ImgDil[(i)*nW+j+1];
            v8 = ImgDil[(i+1)*nW+j+1];
        
       if( est_dans_le_fond(v1, v2, v3, v4, v5, v6, v7, v8)){
            ImgEro[i*nW+j]=255;    
       } 
       
     }
    }



   ecrire_image_pgm(cNomImgEcrite, ImgEro,  nH, nW);
   free(ImgIn);
   return 1;
}