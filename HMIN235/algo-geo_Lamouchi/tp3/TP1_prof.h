#ifdef TP1_PROF_H
#define TP1_PROF_H

// Un point dans le plan, extremité d'un segment

typedef struct {
  int  abscisse;
  int  ordonnee;
  int nSegment; //numero du segment contenant ce point
  char extr; // 'd' pour debut de segment, 'f' pour fin de segment
} point;

// Un segment, avec la convention que l'abscisse de deb est <= celle de fin

typedef struct {
  point deb;
  point fin;
} seg;

bool compareSeg(seg s1,seg s2);


#endif