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
 
  @(#) $Id: 2pgm.c,v 1.2 2000/03/21 20:30:23 fiorio Exp $
 
  $Log: 2pgm.c,v $
  Revision 1.2  2000/03/21 20:30:23  fiorio
  *** empty log message ***

  Revision 1.1  2000/03/21 19:12:20  fiorio
  Initial revision


*/

#ifndef _2pgm_c
#define _2pgm_c

#include "pgm_basic_io.h"

/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*  functions' implementation                                                        */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/

int main(int argc, const char* argv[])
{
  int ret 	     = -1;
  unsigned char* img = NULL;
  FILE* fichier      = NULL;
  int w 	     = 0;
  int h 	     = 0;
  
  if(argc<2){
    printf("ERREUR -- usage :\n");
    printf("%s file_name\n",argv[0]);
  }
  else{
    fichier = fopen(argv[1],"w+");
    if(fichier!=NULL){
      img = litPGM(stdin,&w,&h);
      if(img!=NULL){
	if( (fichier=ecritPGM(fichier,img,w,h)) != NULL ) ret = 0;
      }
    }
  }
  return ret;
}


#endif