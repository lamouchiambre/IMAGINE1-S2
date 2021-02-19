#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h> //pour cos() et sin()
#include <list>

using namespace std;

// Un point dans le plan

typedef struct {
  int  abscisse;
  int  ordonnee;
} point;

void AffichagePointsSVG(int n, point sommet[]);
void AffichageEnvConvSVG(int n, point sommet[], list<point> envconv);

//********************************************//

//Generation au hasard de l'ensemble des points

void PointAuHasard(int n, point sommet[]){
  srand(time(NULL));
  for(int i=0;i<n;i++){
    //
    //
    // A COMPLETER
    //
    //
  }
}

//********************************************//

//Renvoie Vrai si p2 est strictement a droite de la droite p_0p_1
bool AnglePolaireInferieur(point p0, point p1, point p2){
    //
    //
    // A COMPLETER
    //
    //
  return false;
}

//********************************************//

list<point>  Jarvis(int n, point sommet[]){
  list<point> envconv;
  
  int min=0; //indice du sommet le plus bas
  for(int i=0;i<n;i++){
    //
    //
    // A COMPLETER
    //
    //
  }
  envconv.push_back(sommet[min]);
  
  
  int point_courant = min; //indice du point courant
  do{
    //
    //
    // A COMPLETER
    //
    //
  }while(point_courant!=min);
  return envconv;
}

//********************************************//

int main(){
  const int n=20;

  point sommet[n]={0};
  list<point> envconv;
  
  PointAuHasard(n,sommet);
  AffichagePointsSVG(n,sommet);
  envconv=Jarvis(n,sommet);
  AffichageEnvConvSVG(n,sommet,envconv);
}

//********************************************//

//Affichage de n segments dont les coordonnees sont donnees dans segments[n]
//Un fichier segments.svg est cree, visualisable avec un visionneur de document ou un navigateur

void AffichagePointsSVG(int n, point sommet[]){

  ofstream output;
  output.open("points.svg");//
  output << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"<<endl;
  output << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800\" height=\"800\">"<<endl;
  output << "<title>Points dans le plan</title>"<<endl;

  output << endl;

  output << "<rect width=\"800\" height=\"800\" x=\"0\" y=\"0\" fill=\"white\" />"<<endl;
  
  for(int i=0;i<n;i++){
    int x1=50+ sommet[i].abscisse;
    int y1=sommet[i].ordonnee; y1=800-y1;
    int x2=50+ sommet[i].abscisse;
    int y2=sommet[i].ordonnee; y2=800-y2;

    
    output << "<circle cx=\"" << x1 << "\" cy=\"" << y1 << "\"" << " r=\"6\"/>" << endl;
    output << "<circle cx=\"" << x2 << "\" cy=\"" << y2 << "\""  << " r=\"6\"/>" << endl;
  
    output << "<text x=\"" << x1-28 << "\" y=\"" << y1 << "\">S" << i << "</text>"<<endl;
    
  }
  output << endl;
  output << "</svg>"<<endl;

  output.close();
}

//********************************************//

//Affichage de n segments dont les coordonnees sont donnees dans segments[n]
//Un fichier segments.svg est cree, visualisable avec un visionneur de document ou un navigateur

void AffichageEnvConvSVG(int n, point sommet[], list<point> envconv){

  ofstream output;
  output.open("envconv.svg");//
  output << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"<<endl;
  output << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800\" height=\"800\">"<<endl;
  output << "<title>Points dans le plan</title>"<<endl;

  output << endl;

  output << "<rect width=\"800\" height=\"800\" x=\"0\" y=\"0\" fill=\"white\" />"<<endl;
  
  for(int i=0;i<n;i++){
    int x1=50+ sommet[i].abscisse;
    int y1=sommet[i].ordonnee; y1=800-y1;
    int x2=50+ sommet[i].abscisse;
    int y2=sommet[i].ordonnee; y2=800-y2;

    
    output << "<circle cx=\"" << x1 << "\" cy=\"" << y1 << "\"" << " r=\"6\"/>" << endl;
    output << "<circle cx=\"" << x2 << "\" cy=\"" << y2 << "\""  << " r=\"6\"/>" << endl;
  
    output << "<text x=\"" << x1-28 << "\" y=\"" << y1 << "\">S" << i << "</text>"<<endl;
    
  }
  output << endl;

  list<point>::iterator it;
  for(it=envconv.begin();it!=envconv.end();it++){
    list<point>::iterator itsuiv;
    itsuiv=it; itsuiv++;
    if(itsuiv!=envconv.end()){

    int x1=50+ it->abscisse;
    int y1=it->ordonnee; y1=800-y1;
    int x2=50+ itsuiv->abscisse;
    int y2= itsuiv->ordonnee; y2=800-y2;


    output <<  "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2
	   << "\" stroke=\"black\" />"<<endl;
    }
  }

  
  output << "</svg>"<<endl;

  output.close();
}
