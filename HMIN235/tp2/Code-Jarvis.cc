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
bool estDansDisque(int x, int y){
  return (x-400)*(x-400) +(y-400)*(y-400) <= 350*350;
}
void PointAuHasard(int n, point sommet[]){
  srand(time(NULL));

  int i = 0;
  while (i < n)
  {
    int x = rand() % 800;
    int y = rand() % 800;
    if (estDansDisque(x,y))
    {
      point point;
      point.abscisse = x;
      point.ordonnee = y;
      sommet[i] = point;
      i++;
    }
  }
}

//********************************************//

//Renvoie Vrai si p2 est strictement a droite de la droite p_0p_1

bool AnglePolaireInferieur(point p0, point p1, point p2){
  int v_x = p1.abscisse - p0.abscisse;
  int v_y = p1.ordonnee - p0.ordonnee;

  return (v_x*(p2.ordonnee-p0.ordonnee) - v_y*(p2.abscisse-p0.abscisse) > 0);
}

//********************************************//
/*
list<point>  Jarvis(int n, point sommet[]){
  list<point> envconv;
  
  int min=0; //indice du sommet le plus bas

  envconv.push_back(sommet[min]);
  
  
  int point_courant = min; //indice du point courant
  bool arret = false;
  bool flag = true;
  int k = 1;

    //while (!arret && k < n){
  printf("avant for \n");
  for (int i = 0; i < n; i++)
  {
    //printf("je suis dans for\n");
    if (AnglePolaireInferieur(sommet[point_courant], sommet[k], sommet[i]))
    {
      flag = false;
      printf("point %i est à gauche de vect(%i, %i)\n", i, point_courant, k);
      }
    
    //printf("point %i et de vect(%i, %i)\n", i, point_courant, k);
  }
  if(flag){
    arret = true;
  }
  k++;

  printf("\n");

  point_courant = k--;
  envconv.push_back(sommet[point_courant]);
  return envconv;
}*/

// bool AnglePolaireInferieur(point p0, point p1, point p2){
//   int v_x = p1.abscisse - p0.abscisse;
//   int v_y = p1.ordonnee - p0.ordonnee;

//   return (v_x*p2.ordonnee - v_y*p2.ordonnee) > 0;
// }

//********************************************//

list<point>  Jarvis(int n, point sommet[]){
  list<point> envconv;
  int j = 0;
  int min=0; //indice du sommet le plus bas
  for(int i=0;i<n;i++){
    if (sommet[min].ordonnee > sommet[i].ordonnee)
    {
      min = i;
    }else
    {
      if ( (sommet[min].ordonnee == sommet[i].ordonnee) && (sommet[min].abscisse > sommet[i].abscisse))
      {
        min = i;
      }

    }

  }
  printf("min %i\n", min);
  
  envconv.push_back(sommet[min]);

  int point_courant = min; //indice du point courant
  //int prec = min;
  do{
    int max = 0;
    
    // chercher le plus à gauche
    bool arret = false;
    bool flag = true;
    int k = 0;
    printf("deb_________________\n");
    while (!arret && k < n){
      //printf("--------------- \n");
      flag = true;
      for (int i = 0; i < n; i++)
      {
        if (AnglePolaireInferieur(sommet[point_courant], sommet[k], sommet[i]))
        {
          flag = false;
          //printf("point %i est à gauche de vect(%i, %i)\n", i, point_courant, k);
        }
      }
      
      if(flag && k != point_courant ){
        printf("je prends %i\n", k);
        arret = true;
      }
      k++;
    }
    printf("fin_________________\n");

    point_courant = k - 1;
    printf("%li\n", envconv.size());
    envconv.push_back(sommet[point_courant]);

    j++;

  }while(point_courant != min );
  
  //std::cout << envconv << std::endl;

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
