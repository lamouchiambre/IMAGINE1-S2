#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <set>
#include <TP1_prof.h>

using namespace std;


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

void AffichageSegmentsSVG(int n, seg segments[]);

//********************************************//

//Generation au hasard de l'ensemble des segments consideres
//Le premier sommet est celui d'abscisse minimale, on refusera des segments verticaux:
//Choisir x=segments[i].deb.abscisse dans [20,500] et y=segments[i].deb.ordonnee dans [100,700]
//Choisir segments[i].fin.abscisse dans [x+20,x+200] et segments[i].fin.ordonnee dans [y-50,y+50]
//Ne pas oublier de remplir les nSegment pour les points créés

void SegmentsAuHasard(int n, seg segments[]){
  srand(time(NULL));
  int xd, yd, xf, yf, nS;
  nS = 0;
  for(int i=0;i<n;i++){
    xd = (rand() % 480) +20;
    yd = (rand() % 600) + 100;

    xf = (rand() % 180) + xd + 20;
    yf = (rand() % 100) - 50 + yd; 

    cout<< nS << " : deb(" << xd << ", " << yd << ") fin(" << xf << ", " << yf << ")" << endl;

    point debut;
    point fin; 
    
    debut.abscisse = xd; debut.ordonnee = yd; debut.nSegment = nS; debut.extr = 'd';
    fin.abscisse = xf; fin.ordonnee = yf; fin.nSegment = nS; fin.extr = 'f';

    seg segment;
    segment.deb = debut; segment.fin = fin;
    segments[i] = segment;

    nS++;
    
  }  

}



//********************************************//

//Retourne -1 si le point pointé par x est avant lexicographiquement celui pointé par y
//Retoune 1 sinon

int compareLex(const void * x, const void * y)
{
  point point1= *(point *)x;
  point point2= *(point *)y;

  int t = 1;

  if (point1.abscisse < point2.abscisse)
  {
    t = -1;
  }
  else if((point1.abscisse == point2.abscisse) && (point1.ordonnee < point2.ordonnee)){
   t = -1;
  }
  // a simplifier peut etre
  //fin

  
  return t ;
}

void TriLex(int n, point extremites[]){
  qsort(extremites, 2*n, sizeof(extremites[0]), compareLex);
}

//********************************************//

//Renvoie Vrai si les deux segments s1 et s2 s'intersectent
//Dans un premier temps, on pourra supposer que deux segments ne sont jamais
//portes par une meme droite


bool Intersectent(seg s1, seg s2){

  //conversion en long long pour eviter un depacement d'int.
  point p1=s1.deb;
  point p2=s1.fin;
  point p3=s2.deb;
  point p4=s2.fin;
  
  long long x1= (long long) p1.abscisse;
  long long x2= (long long) p2.abscisse;
  long long x3= (long long) p3.abscisse;
  long long x4= (long long) p4.abscisse;

  long long y1= (long long) p1.ordonnee;
  long long y2= (long long) p2.ordonnee;
  long long y3= (long long) p3.ordonnee;
  long long y4= (long long) p4.ordonnee;

  long long det_p1p2_p1p3 = (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
  long long det_p1p2_p1p4 = (x2-x1)*(y4-y1) - (x4-x1)*(y2-y1);
  long long det_p3p4_p3p1 = (x4-x3)*(y1-y3) - (x1-x3)*(y4-y3);
  long long det_p3p4_p3p2 = (x4-x3)*(y2-y3) - (x2-x3)*(y4-y3);//bug derniere ligne

  return (det_p1p2_p1p3*det_p1p2_p1p4 <= 0) && (det_p3p4_p3p1*det_p3p4_p3p2 <= 0) ;
}


//********************************************//
//Renvoie vrai ssi le segment s1 est au dessous du segment s2
//Attention, on ne sait pas si s1 est déjà dans l'ordre ou si c'est s2. Il
//y a deux cas à distinguer..!


bool compareSeg(seg s1,seg s2){
  point p1=s1.deb;
  point p2=s1.fin;
  point p3=s2.deb;
  point p4=s2.fin;
  
  if(p1.abscisse <= p3.abscisse){
    long long det12_13 = (p2.abscisse-p1.abscisse)*(p3.ordonnee-p1.ordonnee) - (p3.abscisse-p1.abscisse)*(p2.ordonnee-p1.ordonnee);
    return det12_13 > 0;
  }else{
    long long det34_31 = (p4.abscisse-p3.abscisse)*(p1.ordonnee-p3.ordonnee) - (p1.abscisse-p3.abscisse)*(p4.ordonnee-p3.ordonnee);
    return det34_31 < 0;
  }

   return false;
}


//********************************************//

//Algo d'intersection
//Renvoie vrai si il existe 2 segments qui s'intersectent, faux sinon
//Fonctionne en nlog n

bool Intersection(int n, seg segments[]){

  point extremites[2*n];
  for(int i=0;i<n;i++){
    extremites[2*i]=segments[i].deb;
    extremites[2*i+1]=segments[i].fin;
    cout <<extremites[2*i].nSegment << " " << extremites[2*i+1].nSegment<<endl;
  }

  TriLex(n,extremites);
  cout <<"------------"<<endl;
  for(int i =0;i<n;i++){
    cout <<extremites[2*i].nSegment << " " << extremites[2*i+1].nSegment<<endl;
  }
  set<seg, decltype(compareSeg)*> ordre(compareSeg);
  set<seg, decltype(compareSeg)*>::iterator segSuiv, segPred;
  
  for(int i=0;i<2*n;i++){

    cout << "Ordre: ";
    for (set<seg,decltype(compareSeg)*>::iterator it=ordre.begin(); it!=ordre.end(); ++it)
      cout << ' ' << (*it).deb.nSegment;
    cout << '\n';

    
    point Pcourant=extremites[i];
    int nSeg=Pcourant.nSegment;
    seg segCourant=segments[nSeg];

   printf("seg = %d %c\n", nSeg, Pcourant.extr);
    if(Pcourant.extr=='d'){
      ordre.insert(segCourant); cout << "insertion de "<< nSeg << endl;
      segPred=ordre.lower_bound(segCourant); 
      segSuiv=ordre.upper_bound(segCourant);

      //if((*segSuiv).deb.nSegment < 10 && (*segSuiv).deb.nSegment >= 0){
      if(segSuiv != ordre.end()){
        //printf("suivant\n");
        if (Intersectent(*segSuiv, segCourant)){
          printf("0-Intersection en %i %i\n",segCourant.deb.nSegment, (*segSuiv).deb.nSegment);
          return true;
      }
      }
      //if((*segPred).deb.nSegment < 10 && (*segPred).deb.nSegment >= 0){
      if (segPred != ordre.begin()){
        segPred--;
        //printf("precedent,%i \n", (*segPred).deb.nSegment);
        if(Intersectent(*segPred, segCourant)){
          printf("1-Intersection en %i %i\n",segCourant.deb.nSegment, (*segPred).deb.nSegment);
          return true;
        } 
      }

    }else{
      segPred=ordre.lower_bound(segCourant); 
      segSuiv=ordre.upper_bound(segCourant);
      
      if((segSuiv != ordre.end()) && (segPred != ordre.begin())){
        segPred--;
        if(Intersectent(*segPred,*segSuiv)){
          printf("2- Intersection en %i %i\n",(*segSuiv).deb.nSegment, (*segPred).deb.nSegment);
        return true;
        }
      }
      ordre.erase(segCourant);  

    }
  }
  
    return false;      
}



// int main(){

//  int const n=10;

//  // Le tableau de segments
//  seg segments[n]={0};
  
//   SegmentsAuHasard(n,segments);
//   AffichageSegmentsSVG(n,segments);
   
//   if(Intersection(n,segments)){
//     cout << "Il y a une intersection." << endl;
//   }else{
//     cout <<"Il n'y a pas d'intersection." << endl;
//   }
// }



//********************************************//

//Affichage de n segments dont les coordonnees sont donnees dans segments[n]
//Un fichier segments.svg est cree, visualisable avec un visionneur de document ou un navigateur

void AffichageSegmentsSVG(int n, seg segments[]){

  ofstream output;
  output.open("segments.svg");//
  output << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"<<endl;
  output << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800\" height=\"800\">"<<endl;
  output << "<title>Intersection de segments</title>"<<endl;

  output << endl;

  output << "<rect width=\"800\" height=\"800\" x=\"0\" y=\"0\" fill=\"white\" />"<<endl;
  
  for(int i=0;i<n;i++){
    int x1=50+ segments[i].deb.abscisse;
    int y1=segments[i].deb.ordonnee; y1=800-y1;
    int x2=50+ segments[i].fin.abscisse;
    int y2=segments[i].fin.ordonnee; y2=800-y2;

    
    output << "<circle cx=\"" << x1 << "\" cy=\"" << y1 << "\"" << " r=\"8\"/>" << endl;
    output << "<circle cx=\"" << x2 << "\" cy=\"" << y2 << "\""  << " r=\"8\"/>" << endl;
    output <<  "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2
	   << "\" stroke=\"black\" />"<<endl;

    output << "<text x=\"" << x1-25 << "\" y=\"" << y1 << "\">S" << i << "</text>"<<endl;
    
  }
  output << endl;
  output << "</svg>"<<endl;

  output.close();
}
