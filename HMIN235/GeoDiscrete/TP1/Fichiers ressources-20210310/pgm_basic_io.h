/* This may look like C code, but it is really -*- C -*-
 
   Copyright (C) 2000 LIRMM
 
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
 
  @(#) $Id: pgm_basic_io.h,v 1.1 2000/03/21 19:12:20 fiorio Exp $
 
  $Log: pgm_basic_io.h,v $
  Revision 1.1  2000/03/21 19:12:20  fiorio
  Initial revision


*/

#ifndef pgm_basic_io_h
#define pgm_basic_io_h

#include <stdio.h>

/*-----------------------------------------------------------------------------------*/


/* --------------------------------------------------------------- 
 *  Function litPGM : lit une image au format PGM P5 et la stocke
 *                     dans une matrice d'unsigned char. Réalise
 *                     l'allocation mémoire
 *
 *  @param FILE* : le fichier contenant l'image (éventuellement stdin)
 *  @return int* : le nombre de colonnes (la largeur)
 *  @return int* : le nombre de lignes (la hauteur)
 *  @return unsigned char* : la matrice contenant l'image
 * --------------------------------------------------------------- */
unsigned char* litPGM(FILE*, int*, int*);


/* --------------------------------------------------------------- 
 *  Function ecritPGM : 
 *
 *  @param FILE* : le fichier dans lequel on écrit (éventuellement stdout)
 *  @param unsigned char*: la matrice contenant l'image
 *  @param int  : la largeur (nombre de colonnes)
 *  @param int  : la hauteur (nombre de lignes)
 *  @return FILE* : NULL si erreur, le fichier dans lequel on a écrit.
 * --------------------------------------------------------------- */
FILE* ecritPGM(FILE*, unsigned char*, int, int);


/*-----------------------------------------------------------------------------------*/

#endif
