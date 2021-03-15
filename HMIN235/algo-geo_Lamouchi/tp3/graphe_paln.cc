#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h> //pour cos() et sin()
#include <vector>

using namespace std;

// Un point dans le plan

typedef struct {
  int  abscisse;
  int  ordonnee;
  int numero;
} point;

typedef struct {
  int  abscisse;
  int  ordonnee;
  int nSegment; //numero du segment contenant ce point
  char extr; // 'd' pour debut de segment, 'f' pour fin de segment
} pointSeg;

typedef struct {
    point deb;
    point fin;
}seg;

void AffichagePointsSVG(int n, point sommet[]);
void AffichageEnvConvSVG(int n, point sommet[], vector<point> envconv);
bool Intersectent(seg s1, seg s2);
vector<point>  Graham(int n, point sommet[]);
//********************************************//

//Test si un sommet appartien a un ensemble
bool appartient(point p, vector<point> tab){
    int i = 0;
    bool estLa = false;

    while (!estLa && i<tab.size())
    {
        if (tab[i].numero == p.numero)
        {
            estLa = true;
        }
        i++;
    }
    return estLa;
    
}

//Generation au hasard de l'ensemble des points
bool estDansDisque(int x, int y){
  return (x-400)*(x-400) +(y-400)*(y-400) <= 350*350;
}

// verifier retourner la liste dans 
vector<point> liste_sans(vector<point> l1,vector<point> sans){
  vector<point> ret;
  for (point p : l1)
  {
    bool estLa = false;
    for (point s : sans)
    {
      if(p.numero == s.numero){
        estLa = true;
      }
    }
    if (!estLa)
    {
      ret.push_back(p);
    }
    
  }
  return ret;
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
            point.numero = i;
            sommet[i] = point;
            i++;
        }
    }
    vector<point> point_conv = Graham(n, sommet);
    vector<seg> G = vector<seg>();

    for(int i = 0; i < point_conv.size()-1; i++){
        seg a;
        a.deb = point_conv[i];
        a.fin = point_conv[i+1];
        G.push_back(a);
    }
    // for (int i = 0; i < n; i++)
    // {
    //     if (!appartient(sommet[i], point_conv))
    //     {   
    //         int i1 = 0;
    //         int i2 = 0;
    //         bool trouver = false;
    //         seg a1;
    //         seg a2;
    //         while (!trouver && i1 < n)
    //         {
    //             int s1 = 0;
    //             int s2 = 0;
                
    //             a1.deb = sommet[i];
    //             a1.fin = sommet[i1];

    //             a2.deb = sommet[i];
    //             a2.fin = sommet[i2];

    //             while(s2 < n && !trouver){
    //                 if (!Intersectent(a1,a2)){
    //                     trouver = true;
    //                     //s2 = n;
    //                 }
    //                 s2++;
    //             }
    //             i1++;
    //             i2++;
    //         }
    //         G.push_back(a1);
    //         G.push_back(a2);
    //     }
      
    // }
  
  
  
  /*
  E = ensemble arrete de l'ensemble convexe
  pour chaque sommet s !(appartient au cycle convexe)
    pour chaque sommet s1 et s2 tel que s1 != s2
        si !(E+{ss1, ss2} contient une intersection) 
            ajouter les arretes ss1 et ss2 dans E

  
  */
}


//********************************************//

//Renvoie vrai si p1 est strictement a droite de la droite p_0p_2
bool AnglePolaireInferieur(point p0, point p1, point p2){
  int v_x = p1.abscisse - p0.abscisse;
  int v_y = p1.ordonnee - p0.ordonnee;

  return (v_x*(p2.ordonnee-p0.ordonnee) - v_y*(p2.abscisse-p0.abscisse) > 0);
  //return 
}

//********************************************//


//Retourne -1 si le point pointé par x est avant lexicographiquement celui pointé par y
//Retoune 1 sinon

int ComparePol(const void * p1, const void * p2, void * p0)
{
  point point1= *(point *)p1;
  point point2= *(point *)p2;
  point point0= *(point *)p0;

  if( AnglePolaireInferieur(point0,point1,point2)){
    return -1;}
  return 1;
}


//********************************************//
//Trie les sommets par ordre polaire croissant autour du sommet d'indice i0
void TriPol(int n, point sommetRestants[], point p0){
  qsort_r(sommetRestants, n-1, sizeof(point), ComparePol, &p0);
}

//********************************************//

vector<point>  Graham(int n, point sommet[]){
  vector<point> envconv;

  int min=0; //indice du sommet le plus bas
  for(int i=0;i<n;i++){
    if(sommet[min].ordonnee>sommet[i].ordonnee){min=i;}
  }
   printf("min %i \n", min);
  point sommetRestants[n-1];
  int sommetTrier[n-1];

  for(int i=0;i<n;i++){
    if(i<min){sommetRestants[i]=sommet[i];}
    else{if(i>min){sommetRestants[i-1]=sommet[i];}}
  }

  TriPol(n,sommetRestants, sommet[min]);

  for (int i = 0; i < n-1; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if ((sommet[j].ordonnee == sommetRestants[i].ordonnee) && (sommet[j].abscisse == sommetRestants[i].abscisse))
      {
        sommetTrier[i] = j;
      }
    }
  }

  for(int i = 0; i < n-1 ; i++){
    printf( " %i ", sommetTrier[i]);
  }
  printf("\n");

  envconv.push_back(sommet[min]);

  envconv.push_back(sommetRestants[0]);
  envconv.push_back(sommetRestants[1]);

  for(int i=2;i<n-1;i++){

    point dernier = envconv.back();
    envconv.pop_back();

    point avant_dernier = envconv.back();
    envconv.push_back(dernier);

    while (AnglePolaireInferieur(avant_dernier, sommetRestants[i], dernier))
    {
      envconv.pop_back();

      dernier = envconv.back();
      envconv.pop_back();

      avant_dernier = envconv.back();
      envconv.push_back(dernier);
    }

    envconv.push_back(sommetRestants[i]);
    printf("push back %i\n",i);

   printf("%i\n",i);
  }

  envconv.push_back(sommet[min]);
  printf("taille %li\n", envconv.size());
  
  return envconv; 
}



vector<point> Graph(int n, point sommet[]){
  srand(time(NULL));
  vector<point> ensconv = Graham(n, sommet);
  vector<point> v_sommet;

  for (int i = 0; i < n; i++)
  {
    v_sommet.push_back(sommet[i]);
  }
  seg s1;
  s1.deb = ensconv[0];
  s1.fin = ensconv[1];
  
  seg s2;
  s2.deb = ensconv[1];
  s2.fin = ensconv[2];
  printf("s1(%i, %i) et s2(%i, %i) intersectent %i\n",s1.deb.numero, s1.fin.numero, s2.deb.numero, s2.fin.numero, Intersectent(s1, s2) );
  vector<point> other_sommet = liste_sans(v_sommet, ensconv);

  for (point p : other_sommet)
  {
    int nb1 = rand() % n;
    int nb2 = rand() % n;

    //ensconv.push_back(p);
    //ensconv.push_back(sommet[nb1]);

  }
  /*
  Pour chaque point qui n'appartient pas
  */
  vector<seg> arete;
  for (point p : other_sommet){
    int i = 0;
    bool stop = false;
    bool trouver = false;
    point p1;
    seg a1;
    while(i < n && !stop)
    { 
      stop = true;
      p1 = v_sommet[i];
      a1.deb = p;
      a1.fin = p1;

      for (seg d : arete)
      {
        if(Intersectent(a1,d)){
          stop = false;
        }
      }
      i++;
    }
    // point p0 = v_sommet[0];
    // v_sommet.erase(v_sommet.begin());
    // v_sommet.push_back(p0);
    printf("p = %i, i = %i point = %i, stop = %i\n",p.numero, i, p1.numero, stop);
    if (stop)
    {
      arete.push_back(a1);
    }
  }
  
  return ensconv;
}

//********************************************//

int main(){
  const int n=20;

  point sommet[n];
  vector<point> envconv;
  
  PointAuHasard(n,sommet);
  AffichagePointsSVG(n,sommet);
  //envconv=Graham(n,sommet);
  envconv = Graph(n,sommet);
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

void AffichageEnvConvSVG(int n, point sommet[], vector<point> envconv){


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

  vector<point>::iterator it;
  for(it=envconv.begin();it!=envconv.end();it++){
    vector<point>::iterator itsuiv;
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

//Intersection 
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
  //printf("det_p1p2_p1p3 %lli, det_p1p2_p1p4 %lli, det_p3p4_p3p1 %lli, det_p3p4_p3p2 %lli \n",
  //  det_p1p2_p1p3,
  //   det_p1p2_p1p4, 
  //   det_p3p4_p3p1, 
  //   det_p3p4_p3p2);
  return (det_p1p2_p1p3*det_p1p2_p1p4 < 0) && (det_p3p4_p3p1*det_p3p4_p3p2 < 0) ;
}