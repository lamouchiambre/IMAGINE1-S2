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
            img[i+j*w] = (unsigned char) 250;
            img2[i+j*w] = 4294967295;
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

    //i
    // int rayon = 32;

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

    //1

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

    // ii

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

    // iiv
    // rayon = 32;
    // img2[x0+y0*w] = 0;
    // while(r < rayon){
    //     r = img2[x0+i-1+y0*w]+ 3;
    //     img2[x0+i+(y0)*w] = r; //img[x0+(y0+i)*w]+ 1; 
    //     //img2[x0+i+(y0-1)*w] = r+1;
    //     img[x0+i+(y0)*w] = (unsigned char) r;
    //     int j = 0;
    //     int val1 = 0;
    //     int val2 = 0;

    //     while(j <i && val1 <=rayon ){
    //         val1= img2[x0+i+(y0-j)*w]+3;
    //         val2= img2[(x0-1)+i+(y0-j)*w]+4;
    //         img2[x0+i+(y0-(1+j))*w] = min(val1,val2);
    //         img[x0+i+(y0-(1+j))*w] = (unsigned char) min(val1,val2);
    //         j++;
    //     }
    //     i++;
    // }

    // iv
    // rayon = 56;
    // img2[x0+y0*w] = 0;
    // while(r < rayon){
    //     r = img2[x0+i-1+y0*w] + 5;
    //     printf("%i %i r = %i\n",i, 0, r);
    //     img2[x0+i+y0*w] = r; //img[x0+(y0+i)*w]+ 1; 
    //     img[x0+i+y0*w] = (unsigned char) r;
    //     int j = 0;
    //     int val1 = 0;
    //     int val2 = 0;
    //     int val3 = 0;

    //     while(j <i && min(val1,min(val3,val2)) <= rayon ){
    //         val1 = img2[(x0-1)+i+(y0-(j-1))*w]+7;
    //         val2 = img2[(x0)+i+(y0-(j-1))*w]+5;
    //         val3 = img2[(x0-2)+i+(y0-(j-1))*w]+11;
    //         img2[x0+i+(y0-(1+j))*w] = min(val1,min(val3,val2));
    //         img[x0+i+(y0-(1+j))*w] = (unsigned char) min(val1,min(val3,val2));
    //         j++;
    //     }
    //     i++;
    // }

    // v
    // rayon = 56;
    // img2[x0+y0*w] = 0;
    // while(r < rayon){
    //     r = img2[x0+i-1+y0*w]+ 5;
    //     img2[x0+i+(y0)*w] = r; //img[x0+(y0+i)*w]+ 1; 
    //     //img2[x0+i+(y0-1)*w] = r+1;
    //     img[x0+i+(y0)*w] = (unsigned char) r;
    //     int j = 0;
    //     int val1 = 0;
    //     int val2 = 0;
    //     int val3 = 0;

    //     while(j <i && val1 <=rayon ){
    //         val1= img2[x0+i+(y0-j)*w]+5;
    //         val2= img2[(x0-1)+i+(y0-j)*w]+7;
    //         val3= img2[(x0-3)+i+(y0-(j-1))*w]+16;
    //         img2[x0+i+(y0-(1+j))*w] = min(min(val1,val2),val3);
    //         img[x0+i+(y0-(1+j))*w] = (unsigned char) min(min(val1,val2),val3);
    //         j++;
    //     }
    //     i++;
    // }

    //vi
    // rayon = 46;
    // img2[x0+y0*w] = 0;
    // while(r < rayon){
    //     r = img2[x0+i-1+y0*w] + 5;
    //     printf("%i %i r = %i\n",i, 0, r);
    //     img2[x0+i+y0*w] = r; //img[x0+(y0+i)*w]+ 1; 
    //     //img2[x0+i+(y0-1)*w] = r+1;
    //     img[x0+i+y0*w] = (unsigned char) r;
    //     int j = 0;
    //     int val1 = 0;
    //     int val2 = 0;
    //     int val3 = 0;

    //     while(j <i && min(val1,min(val3,val2)) <= rayon ){
    //         val1 = img2[(x0-1)+i+(y0-(j-1))*w]+7;
    //         val2 = img2[(x0)+i+(y0-(j-1))*w]+5;
    //         val3 = img2[(x0-2)+i+(y0-(j-1))*w]+9;
    //         printf("val1 )%i, val2 = %i, val3 = %i\n", val1, val2, val3);
    //         img2[x0+i+(y0-(1+j))*w] = min(val1,min(val3,val2));
    //         printf("min %i %i = %i\n",i,j,min(val1,min(val3,val2)));
    //         img[x0+i+(y0-(1+j))*w] = (unsigned char) min(val1,min(val3,val2));
    //         j++;
    //     }
    //     i++;
    // }


    //je reprend le iv pour mettre la couleur en fonction des vecteur utiliser

    // rayon = 56;
    // img2[x0+y0*w] = 0;
    // while(r < rayon){
    //     r = img2[x0+i-1+y0*w] + 5;
    //     printf("%i %i r = %i\n",i, 0, r);
    //     img2[x0+i+y0*w] = r; //img[x0+(y0+i)*w]+ 1; 
    //     //img2[x0+i+(y0-1)*w] = r+1;
    //     img[x0+i+y0*w] = (unsigned char) 100;
    //     int j = 0;
    //     int val1 = 0;
    //     int val2 = 0;
    //     int val3 = 0;

    //     while(j <i && min(val1,min(val3,val2)) <= rayon ){
    //         val1 = img2[(x0-1)+i+(y0-(j-1))*w]+7;
    //         val2 = img2[(x0)+i+(y0-(j-1))*w]+5;
    //         val3 = img2[(x0-2)+i+(y0-(j-1))*w]+11;
    //         int v = min(val1,min(val3,val2));

    //         printf("val1 )%i, val2 = %i, val3 = %i\n", val1, val2, val3);
    //         img2[x0+i+(y0-(1+j))*w] = min(val1,min(val3,val2));
    //         printf("min %i %i = %i\n",i,j,min(val1,min(val3,val2)));
    //         if(v == val1){
    //             img[x0+i+(y0-(1+j))*w] = (unsigned char) 50;
    //         }else
    //         {
    //             if (v == val2)
    //             {
    //                 img[x0+i+(y0-(1+j))*w] = (unsigned char) 100;
    //             }else
    //             {
    //                 img[x0+i+(y0-(1+j))*w] = (unsigned char) 150;
    //             }
    //         }
    //         //img[x0+i+(y0-(1+j))*w] = (unsigned char) min(val1,min(val3,val2));
    //         j++;
    //     }
    //     i++;
    // }


    int t = min(w,h)/2;
    for (int i = 0; i < t; i++)
    {
        for(int j = 0; j < i+1; j++){
            img[(y0+j)+(x0+i)*w] = img[(x0+i)+(y0-j)*w];
            img[(y0+j)+(x0-i)*w] = img[(x0+i)+(y0-j)*w];
            img[(y0-j)+(x0-i)*w] = img[(x0+i)+(y0-j)*w];
            img[(y0-j)+(x0+i)*w] = img[(x0+i)+(y0-j)*w];

            img[(x0-i)+(y0-j)*w] = img[(x0+i)+(y0-j)*w];
            img[(x0-i)+(y0+j)*w] = img[(x0+i)+(y0-j)*w];
            img[(x0+i)+(y0+j)*w] = img[(x0+i)+(y0-j)*w];
        }
    }
    

//Reponse a la question 2
/*
D'apres les figure que j'ai fait c'est la iv qui ressemble le plus a une sphere
*/


//-------------Droite Discrète
    //droit de BRESENHAM
/*
    int p_x0 = 0;
    int p_y0 = 0;
    int p_x1 = 20;
    int p_y1 = 10;

    int dx = p_x1 - p_x0;
    int dy = p_y1 - p_y0;
    int incrHor = 2*dy;
    int incrDiag = 2*(dx-dy);
    int e = 2*dy - dx;
    int y = 0;

    for(int i = p_x0; i < p_x1; i++){
        img[i + y*w];
        img[(x0+i) + (y0-y)*w] = (unsigned char) 0;
        if(e >= 0){
            y++;
            e-= incrDiag;
        }else{
            e+= incrHor;
        }
    }
*/

    //RÉVEILLÈS (1991)
/*
    int p_x0 = 0;
    int p_y0 = 0;
    int p_x1 = 10;
    int p_y1 = 10;

    int vx = p_x1 - p_x0;
    int vy = p_y1 - p_y0;

    int u = vy*p_x0 - vx*p_y0;
    int r_ =vy*p_x0 - vx*p_y0 - u;
    int x = p_x0;
    int y = p_y0;

    while (x < p_x1)
    {
        x++;
        r_+=vy;
        if(r_ < 0 || r_ >= vx){
            y++;
            r_-= vx;
        }
        img[(x0+x) + (y0-y)*w] = (unsigned char) 0;
    }
  */  


    fichier = fopen("img.pgm","w+");
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

// void droit(int x0, int y0, int x1, int y1){
//     int dx = x1 - x0;
//     int dy = y1 - y0;
//     int incrHor = 2*dy;
//     int incrDiag = 2*(dx-dy);
//     int e = 2*dy - dx;
//     int y = 0;

//     for(int i = x0; i <= x1; i++){
//         img[i + y*w];
//         if(e >= 0){
//             y++;
//             e-= incrDag;
//         }else{
//             e+= incrHor;
//         }
//     }
// }

#endif
