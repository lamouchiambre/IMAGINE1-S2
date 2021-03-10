#ifndef pgm2_c
#define pgm2_c

#include "pgm_basic_io.h"
#include "stdlib.h"
#include <math.h>

/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*  functions' implementation                                                        */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
int min(int p, int q){
    if(p < q){
        return p;
    }else{
        return q;
    }
}
int main(int argc, const char* argv[])
{
    int ret 	     = -1;
    unsigned char* img = NULL;
    unsigned int* img2 = NULL;
    FILE* fichier      = NULL;
    int w 	     = 100;
    int h 	     = 100;
    int taille = w*h;
    img = (char *) malloc( taille * sizeof(char) );
    img2 = (char *) malloc( taille * sizeof(int) );
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            img[i+j*w] = (unsigned char) 250;//i%h;
            img2[i+j*w] = 4294967295;
            printf("infinity = %i\n", img2[i+j*w]);
        }
        
    }

    //1 Boule de chan
    int mat1[3][3] = {{-1,1,-1},{1,0,1},{-1,1,-1}};
    
    int x0 = w/2;
    int y0 = (h/2);


    img[x0 + w*y0] = 255;
    for(int i = 0; i < 10; i++){
        img[x0 + y0*w] = mat1[x0][y0];
    }

    int i = 1;
    int r = 0;
    //printf("i = i");
    int rayon = 20;

    // while(r < rayon){
    //     r = img2[x0+i-1+y0*w]+ 1;
    //     printf("r = %i\n", r);

    //     img2[x0+i+(y0)*w] = r; //img[x0+(y0+i)*w]+ 1; 
    //     img[x0+i+(y0)*w] = (unsigned char) r;
    //     //img[(x0-w)+i+(y0)*w] = (unsigned char) r;
    //     int j = 0;
    //     int val1 = 0;
    //     while(j <i && val1 <=rayon ){
    //         val1= img2[x0+i+(y0-j)*w]+1;
    //         if(val1<=rayon){
    //             img2[x0+i+(y0-(1+j))*w] = val1; //min(val1,val2);
    //             printf("val1 = %i\n", val1);
    //             img[x0+i+(y0-(1+j))*w] = (unsigned char) val1; //min(val1,val2);
    //             //img[-(x0+i)-(y0-(1+j))*w] = (unsigned char) val1; //min(val1,val2);
    //         }
    //         j++;
    //     }
    //     i++;
    // }


    // while(r < rayon){
    //     r = img2[x0+i-1+y0*w]+ 1;
    //     printf("r = %i\n", r);

    //     img2[x0+i+(y0)*w] = r; //img[x0+(y0+i)*w]+ 1; 
    //     img[x0+i+(y0)*w] = (unsigned char) r;
    //     //img[(x0-w)+i+(y0)*w] = (unsigned char) r;
    //     int j = 0;
    //     int val1 = 0;
    //     while(j <i && val1 <=rayon ){
    //         val1= img2[x0+i+(y0-j)*w]+1;
    //         if(val1<=rayon){
    //             img2[x0+i+(y0-(1+j))*w] = val1; //min(val1,val2);
    //             printf("val1 = %i\n", val1);
    //             img[x0+i+(y0-(1+j))*w] = (unsigned char) val1; //min(val1,val2);
    //             //img[-(x0+i)-(y0-(1+j))*w] = (unsigned char) val1; //min(val1,val2);
    //         }
    //         j++;
    //     }
    //     i++;
    // }

    //l'autre
    // img2[x0+y0*w] = 0;
    // while(r < rayon){
    //     r = img2[x0+i-1+y0*w]+ 1;
    //     img2[x0+i+(y0)*w] = r; //img[x0+(y0+i)*w]+ 1; 
    //     img2[x0+i+(y0-1)*w] = r;
    //     img[x0+i+(y0)*w] = (unsigned char) r;
    //     int j = 0;
    //     int val1 = 0;
    //     int val2 = 0;

    //     while(j <i && val1 <=rayon ){
    //         val1= img2[x0+i+(y0-j)*w]+1;
    //         val1= img2[(x0-1)+i+(y0-(1+j))*w]+1;
    //         img2[x0+i+(y0-(1+j))*w] = min(val1,val2);
    //         img[x0+i+(y0-(1+j))*w] = (unsigned char) min(val1,val2);
    //         j++;
    //     }
        
    //     i++;

    // }

    img2[x0+y0*w] = 0;
    while(r < rayon){
        r = img2[x0+i-1+y0*w]+ 1;
        img2[x0+i+(y0)*w] = r; //img[x0+(y0+i)*w]+ 1; 
        img2[x0+i+(y0-1)*w] = r;
        img[x0+i+(y0)*w] = (unsigned char) r;
        int j = 0;
        int val1 = 0;
        int val2 = 0;

        while(j <i && val1 <=rayon ){
            val1= img2[x0+i+(y0-j)*w]+1;
            val1= img2[(x0-1)+i+(y0-(1+j))*w]+1;
            img2[x0+i+(y0-(1+j))*w] = min(val1,val2);
            img[x0+i+(y0-(1+j))*w] = (unsigned char) min(val1,val2);
            j++;
        }
        
        i++;

    }



    fichier = fopen("bonjour.pgm","w+");
    fichier = ecritPGM(fichier,img,w,h); 
    fclose(fichier);

  //test affiche image


  
//   printf("je compile\n");
//   if(argc<2){
//     printf("ERREUR -- usage :\n");
//     printf("%s file_name\n",argv[0]);
//   }
//   else{
//     fichier = fopen(argv[1],"r");
//     if(fichier!=NULL){
//       img     = litPGM(fichier,&w,&h);
//       if(img!=NULL){
// 	if( (fichier=ecritPGM(stdout,img,w,h)) != NULL ) ret = 0;
//       }
//     }
//   }
//   return ret;
}


#endif
