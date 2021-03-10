/* This may look like C code, but it is really -*- C -*-
 
   Copyright (C) 1998 LIRMM
 
   Author: Christophe Fiorio <fiorio@lirmm.fr>
   This is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.
 
   This sofware is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 
   You may have received a copy of the GNU General Public License along
   with GNU Emacs; see the file COPYING.  If not, write to the Free
   Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 
  @(#) $Id: pgm_basic_io.c,v 1.1 2000/03/21 19:12:20 fiorio Exp $
 
  $Log: pgm_basic_io.c,v $
  Revision 1.1  2000/03/21 19:12:20  fiorio
  Initial revision


*/

#ifndef pgm_basic_io_c
#define pgm_basic_io_c

#include "pgm_basic_io.h"

#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*  functions' implementation                                                        */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/

/* --------------------------------------------------------------- 
 *  Function litPGM : lit une image au format PGM P5 et la stocke
 *                    dans une matrice d'unsigned char. Réalise
 *                    l'allocation mémoire
 *
 *  @param FILE* : le fichier contenant l'image (éventuellement stdin)
 *  @return  int* : le nombre de colonnes (la largeur)
 *  @return  int* : le nombre de lignes (la hauteur)
 *  @return unsigned char* : la matrice contenant l'image
 * --------------------------------------------------------------- */
unsigned char* litPGM(FILE* f, int* w, int* h)
{
  char ch[255]; /* chaine tampon pour la lecture dans l'image */
  int c;        /* caractère pour lire la valeur des pixels  */
  int i=0;      /* i compteur de boucle */
  int s=0;      /* s taille de l'image  */
  unsigned char* ret = NULL;
    
  fgets(ch,255,f); /* le format */
  if( strncmp(ch,"P5",2)!=0 )  ret=NULL; /* si pas P5 alore ERREUR */
  else{
    fgets(ch,255,f); /* la taille */
    while(ch[0]=='#')  fgets(ch,255,f); /* lecture éventuelle des
					   commentaires */
    sscanf(ch,"%d %d",w,h);
    fgets(ch,255,f); /* le fameux 255 */
    s = (*w)*(*h);
    ret = (unsigned char*) malloc(s*sizeof(unsigned char));
    if( (c!=EOF) && (ret!=NULL)){ /* 255 bien lu et l'allocation s'est bien
				     passée */
      i=0;
      while( (i<s) && (c!=EOF)){
	ret[i++]=(unsigned char) (c = fgetc(f));
      }
      if( (i<s) || ((i==s) && (c==EOF)) ) ret = NULL; /* erreur de lecture */
    }
  }
  return ret;
}


/* --------------------------------------------------------------- 
 *  Function ecritPGM : 
 *
 *  @param FILE* : le fichier dans lequel on écrit (éventuellement stdout)
 *  @param unsigned char*: la matrice contenant l'image
 *  @param int : la largeur (nombre de colonnes)
 *  @param int : la hauteur (nombre de lignes)
 *  @return FILE* : NULL si erreur, le fichier dans lequel on a écrit.
 * --------------------------------------------------------------- */
FILE* ecritPGM(FILE* f, unsigned  char* img, int w, int h)
{
  int i	     =0;      /* i compteur de boucle */
  int s	     =0;      /* s taille de l'image  */
  FILE* ret  = f;
  int erreur = 0;
    
  erreur=fputs("P5\n",f); /* le format */
  if( erreur == EOF ){  /* si erreur d'ecriture */
    fclose(f);
    ret = NULL;
  }
  else{
    erreur=fprintf(f,"%d %d\n",w,h);
    erreur = fprintf(f,"255\n"); /* le fameux 255 */
    if(erreur!=4){
      fclose(f);
      ret = NULL;
    }
    else{
      s = w*h;
      i=0;
      while( (i<s) && (erreur!=EOF)){
	erreur=fputc((int)img[i++],f);
      }
      if( (i<s) || ((i==s) && (erreur==EOF)) ) ret = NULL; /* erreur de lecture */
    }
  }
  return ret;  
}



#endif
