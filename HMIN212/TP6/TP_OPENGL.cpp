///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synth�se d'images - Mod�lisation g�om�trique
// Auteur : Gilles Gesqui�re
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de cr�er des formes de bases.
// La forme repr�sent�e ici est un polygone blanc dessin� sur un fond rouge
///////////////////////////////////////////////////////////////////////////////  

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>


/* Dans les salles de TP, vous avez g�n�ralement acc�s aux glut dans C:\Dev. Si ce n'est pas le cas, t�l�chargez les .h .lib ...
Vous pouvez ensuite y faire r�f�rence en sp�cifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le r�pertoire courant, on aura alors #include "glut.h" 
*/

#include <GL/glut.h> 

// D�finition de la taille de la fen�tre
#define WIDTH  480

#define HEIGHT 480

// D�finition de la couleur de la fen�tre
#define RED   1
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27


// Ent�tes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 


//class point
class Point
{
  public:
    float  x;
    float  y;
    float  z;

    Point(){
      x=0;
      y=0;
      z=0;
    }
    Point(float x, float y, float z):x(x), y(y), z(z){
    }
}; 

//class Vector
class Vector
{
  public:
    float  x;
    float  y;
    float  z;

    Vector(){
      x=0;
      y=0;
      z=0;
    }
    Vector(float x, float y, float z):x(x), y(y), z(z){
    }
};

class Courbe{
  public:
    Point p0;
    Point p1;
    Point* controlPoint;
    int nb_CP;

    Courbe(){
      p0 = Point();
      p1 = Point();
      //Point CP[0];
      controlPoint = NULL;
      nb_CP = 0;
    }

    //droite
    Courbe(Point p_0, Point p_1){
      p0 = p_0;
      p1 = p_1;
      //Point CP[0];
      controlPoint = NULL;
      nb_CP = 0;
    }
    
    Courbe(Point p0, Point p1, Point* controlPoint, int nb_CP):p0(p0), p1(p1),controlPoint(controlPoint), nb_CP(nb_CP){}
};

/**
 * Exercice 1
 * 
*/
void DrawCurve(Point* TabPointOfCurve, long nbPoint){
  glBegin(GL_LINE_STRIP);
  glColor3f(1.0, 1.0, 1.0);
  
  for(int i = 0; i < nbPoint; i++){
    Point p = TabPointOfCurve[i];
    glVertex3f(p.x, p.y, p.z);
  }
  glEnd();
}
//
void HermiteCubicCurve(Point P0, Point P1, Vector V0, Vector V1, long nbU, Point* pointTab){

  float f1, f2, f3, f4;
  float pas = (1.0/(float)(nbU-1));
  printf("pas = %f", pas);

  //Point pointTab[nbU];
  float u =0;
  for(int i = 0; i < nbU; i++){
      f1 = 2*u*u -3*u*u +1;
      f2 = -2*u*u*u +3*u*u;
      f3 = u*u*u -2*u*u +u;
      f4 = u*u*u - u*u;
      Point p = Point (f1*P0.x + f2*P1.x + f3*V0.x + f4*V1.x, 
                      f1*P0.y + f2*P1.y + f3*V0.y + f4*V1.y,
                      f1*P0.z + f2*P1.z + f3*V0.z + f4*V1.z);
      pointTab[i] = p;
      u+=pas;

  }
}

/**
 * Exercice 2
 * 
*/
//fonction factoriel
long fact (long x)
{
  if (x <= 1)
    return 1;
  return (x * fact(x-1));
}

float polyBertstein(float u, long n, long i){
  return (float) (fact(n)/(fact(i)*fact(n-i)))*pow(u,i)*pow(1-u,n-i);
}

//courbe de bezier
void BezierCurveByBernstein(Point* TabControlPoint, long nbControlPoint, Point* pointTab, long nbU){
  float u =0;
  float pas = (float) 1/(nbU-1);
  //long nbPoly = fact ;
  for (long i = 0 ; i < nbU;i++){
    float B = 0.0;
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    //printf("i = %li\n",i);
    for (long j = 0; j < nbControlPoint; j++)
    {
      //printf("deb\n");
      B = polyBertstein(u, nbControlPoint-1, j);
      //printf("suit\n");
      x += B*TabControlPoint[j].x;
      y += B*TabControlPoint[j].y;
      z += B*TabControlPoint[j].z;
      //printf("   j = %li\n",j);
    }
    pointTab[i] = Point(x,y,z);
    u+=pas;

  }
}

/**
 * Exercice 3
 * 
*/
void BezierCurveByCasteljau(Point* TabControlPoint, long nbControlPoint, long nbU, Point* pointTab){
  int i =0;
  float u = 0;
  float pas = (float) 1.0/(nbU-1);
  Point P[nbControlPoint][nbControlPoint];
      //initalisation
  for(long j = 0; j < nbControlPoint; j++){
    P[0][j] = TabControlPoint[j];
  }


  for(int j = 0; j < nbU; j++ ){
    for(long k = 0; k < nbControlPoint-1; k++){
      for(long i= 0 ; i < nbControlPoint - (k+1) ; i++){
        P[k+1][i] = Point( 
           (1.0-u)*P[k][i].x + u*P[k][i+1].x,
           (1.0-u)*P[k][i].y + u*P[k][i+1].y,
           (1.0-u)*P[k][i].z + u*P[k][i+1].z);
      }
    }
    pointTab[j] = P[nbControlPoint-1][0];

    u+=pas;

  }
}

void BezierCurveByCasteljau2(Point* TabControlPoint, long nbControlPoint, long nbU, Point* pointTab){
  int i =0;
  float u = 0;
  float pas = (float) 1.0/(nbU-1);
  Point P[nbControlPoint][nbControlPoint];
      //initalisation
  for(long j = 0; j < nbControlPoint; j++){
    P[0][j] = TabControlPoint[j];
  }


  for(int j = 0; j < nbU; j++ ){
    for(long k = 0; k < nbControlPoint-1; k++){
      glBegin(GL_LINE_STRIP);
      glColor3f(0.0, 1.0, 0.0);
      for(long i= 0 ; i < nbControlPoint - (k+1) ; i++){
        P[k+1][i] = Point( 
           (1.0-u)*P[k][i].x + u*P[k][i+1].x,
           (1.0-u)*P[k][i].y + u*P[k][i+1].y,
           (1.0-u)*P[k][i].z + u*P[k][i+1].z);
           glVertex3f(P[k+1][i].x, P[k+1][i].y, P[k+1][i].z);
      }
      glEnd();
    }
    pointTab[j] = P[nbControlPoint-1][0];

    u+=pas;

  }
}


//Exercice 1 TP6
void SurfaceCylindrique(Courbe b, Courbe d, long nbU, long nbV, Point** pointTabUV){
  Point pointTab[nbU];
  //Point pointTabUV[nbV][nbU];
  double pasU = 1/ (double) nbU;
  double pasV = 1/ (double) nbV;
  printf("pasV = %f", pasV);
  double su = 0;
  double sv = 0;

  BezierCurveByCasteljau(b.controlPoint, b.nb_CP, nbU, pointTab);
  for(int i = 0; i < nbU; i++){
    //printf("pointTab[%i] = (%f,%f,%f)\n",i,pointTab[i].x, pointTab[i].y, pointTab[i].z);
  }
  //DrawCurve(pointTab, nbU);
  printf("fin Bezier\n");
  for(int i = 0; i < nbV; i++){
    
    for(int j = 0; j < nbU; j++){
      Point p = Point((1-sv)*pointTab[j].x+sv*(d.p1.x),
                      (1-sv)*pointTab[j].y+sv*(d.p1.y),
                      (1-sv)*pointTab[j].z+sv*(d.p1.z));

      pointTabUV[i][j] = p;
      
      printf("pointTabUV[%i][%i] = (%f,%f,%f) sv = %f \n",i,j,pointTabUV[i][j].x,pointTabUV[i][j].y,pointTabUV[i][j].z, sv);
    }
    sv+=pasV;
    printf("________\n");
  }
}
//Exercice 2 TP
void SurfaceReglee(Courbe b1, Courbe b2, long nbU, long nbV, Point** pointTabUV){
  Point pointTabB1[nbU];
  Point pointTabB2[nbU];
  //Point pointTabUV[nbV][nbU];
  double pasU = 1/ (double) nbU;
  double pasV = 1/ (double) nbV;

  BezierCurveByCasteljau(b1.controlPoint, b1.nb_CP, nbU, pointTabB1);
  BezierCurveByCasteljau(b2.controlPoint, b2.nb_CP, nbU, pointTabB2);
  double sv = 0;

  for(int i = 0; i < nbV; i++){
    
    for(int j = 0; j < nbU; j++){
      Point p = Point((1-sv)*pointTabB1[j].x+sv*pointTabB2[j].x,
                      (1-sv)*pointTabB1[j].y+sv*pointTabB2[j].y,
                      (1-sv)*pointTabB1[j].z+sv*pointTabB2[j].z);

      pointTabUV[i][j] = p;
      
      printf("pointTabUV[%i][%i] = (%f,%f,%f) sv = %f \n",i,j,pointTabUV[i][j].x,pointTabUV[i][j].y,pointTabUV[i][j].z, sv);
    }
    sv+=pasV;
    printf("________\n");
  }

}

//Exercice 3 TP6
void BezierSurfaceByBernstein(Point** GrilleControlPoint, long nbControlPointU,
 long nbControlPointV,long nbU, long nbV, Point ** pointTabUV){
   printf("________\n");
    double pasU = 1/(double)nbU;
    double pasV = 1/(double)nbV;
    double u = 0;
    double v = 0;
    printf("________\n");
    for(int i = 0; i < nbU; i++ ){
      v = 0;
      for(int j = 0; j < nbV; j++){
        double x = 0;
        double y = 0;
        double z = 0;
        for(int k= 0; k < nbControlPointU; k++){
          for(int l= 0; l < nbControlPointV; l++){
            double Bn = polyBertstein(u, nbControlPointU, k);
            double Bm = polyBertstein(v, nbControlPointV, l);
            x += GrilleControlPoint[k][l].x*Bn*Bm;
            y += GrilleControlPoint[k][l].y*Bn*Bm;
            z += GrilleControlPoint[k][l].z*Bn*Bm;
          }
        }

        pointTabUV[i][j] = Point(x,y,z);
        printf("pointTabUV[%i][%i] = (%f,%f,%f) sv = %f \n",i,j,pointTabUV[i][j].x,pointTabUV[i][j].y,pointTabUV[i][j].z, v);
        v+=pasV;
     }
     u+=pasU;
   }
}
int main(int argc, char **argv) 
{  
  // initialisation  des param�tres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // d�finition et cr�ation de la fen�tre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Premier exemple : carr�");

  // initialisation de OpenGL et de la sc�ne
  initGL();  
  init_scene();

  // choix des proc�dures de callback pour 
  // le trac� graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fen�tre
  glutReshapeFunc(&window_reshape);
  // la gestion des �v�nements clavier
  glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des �v�nements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque
GLvoid initGL() 
{
  glClearColor(RED, GREEN, BLUE, ALPHA);        
}

// Initialisation de la scene. Peut servir � stocker des variables de votre programme
// � initialiser
void init_scene()
{
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // C'est l'endroit o� l'on peut dessiner. On peut aussi faire appel
  // � une fonction (render_scene() ici) qui contient les informations 
  // que l'on veut dessiner
  render_scene();

  // trace la sc�ne grapnique qui vient juste d'�tre d�finie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fen�tre. Augmentez ces valeurs si l'objet est 
  // de trop grosse taille par rapport � la fen�tre.
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

  // toutes les transformations suivantes s�appliquent au mod�le de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break; 
    
  default:
    printf ("La touche %d n�est pas active.\n", key);
    break;
  }     
}

void AfficheGrill(Point** TabPointUV, long nbU, long nbV){
  glBegin(GL_QUAD_STRIP);
  glColor3f(0.1,0.1,0.1);
  for(int i = 0; i< nbU-1; i++){
    for(int j = 0; j < nbV-1; j++){
      glVertex3f(TabPointUV[i][j].x, TabPointUV[i][j].y, TabPointUV[i][j].z);
      glVertex3f(TabPointUV[i][j+1].x, TabPointUV[i][j+1].y, TabPointUV[i][j+1].z);
      glVertex3f(TabPointUV[i+1][j].x, TabPointUV[i+1][j].y, TabPointUV[i+1][j].z);
      glVertex3f(TabPointUV[i+1][j+1].x, TabPointUV[i+1][j+1].y, TabPointUV[i+1][j+1].z);

    }
  }
  glEnd();
}


//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//D�finition de la couleur
  glLineWidth(1.0);
  glColor3f(1.0, 1.0, 1.0);

  //  Nous cr�ons ici un polygone. Nous pourrions aussi cr�er un triangle ou des lignes. Voir ci-dessous les parties 
  // en commentaires (il faut commenter le bloc qui ne vous int�resse pas et d�commenter celui que vous voulez tester.

   // Cr�ation de deux lignes
	// glBegin(GL_LINES);
	// 	glVertex3f(-1, -1, 0);
	// 	glVertex3f(1, 1, 0);
	// 	glVertex3f(1, -1, 0);
	// 	glVertex3f(-1, 1, 0); 
	// glEnd();
  
  // Point p1 = Point(1,1,1);
  // Point p2 = Point(3,1,1);
  // Point tabP[2] = {p1, p2};
  // DrawCurve(tabP, 3);

  //   long nbControlPoint = 4;

  //   Point P0 = Point(-2,1.0,0.0);
  //   Point P1 = Point(-1.0, 2.0,0.0);
  //   Point P2 = Point(0.0, 0.5,0.0);
  //   Point P3 = Point(0.5, -2.0,0.0);
  //   //Point P4 = Point(2.0,1.0,0.0);
  //   Point TabControlPoint[nbControlPoint] = {P0,P1,P2,P3};

  //   Point ** TabTest = new Point*[2];
  //   for(int i =0; i<2; i++){
  //     TabTest[i] = new Point[2];
  //   }
  //   TabTest[0][0] =  Point(0,0,0);
  //   TabTest[0][1] =  Point(0,1,0);
  //   TabTest[1][0] =  Point(1,0,0);
  //   TabTest[1][1] =  Point(1,1,0);
    
  // //Exercice 1
  // long nbU = 10;
  // long nbV = 10;
  //   Courbe b = Courbe(P0,P3,TabControlPoint, nbControlPoint);
  //   Point P4 = Point(-2,2.0,1.0);
  //   Courbe d = Courbe(P0,P4);
  //   //Point PointTabUV[3][4];
  //   Point** PointTabUV = new Point*[nbU];
  //   for(int i = 0; i < nbU; i++){
  //     PointTabUV[i] = new Point[nbV];
  //   }

    
  //   SurfaceCylindrique(b, d, nbU, nbV, PointTabUV);
  //   AfficheGrill(PointTabUV, nbU, nbV);
  //   for (int i = 0; i < nbV; i++){
  //     DrawCurve(PointTabUV[i], nbU);
  //   }

    

  //Exercice 2
    // long nbControlPoint = 3;

    // Point P0 = Point(-2,1.0,0.0);
    // Point P1 = Point(-1.0, 1.0,0.0);
    // Point P2 = Point(0.0, 0.5,0.0);
    // Point TabControlPoint_1[nbControlPoint] = {P0,P1,P2};

    // Point P4 = Point(1,2.0,0.0);
    // Point P5 = Point(-1.0, 1.5,0.0);
    // Point P6 = Point(0.0, 0.5,0.0);
    // Point TabControlPoint_2[nbControlPoint] = {P4,P5,P6};

    // Courbe b1 = Courbe(P0, P2, TabControlPoint_1,nbControlPoint);
    // Courbe b2 = Courbe(P4, P6, TabControlPoint_2,nbControlPoint);

    // long nbU = 10;
    // long nbV = 10;

    // Point** pointTabUV = new Point*[nbU];
    // for(int i = 0; i < nbU; i++){
    //   pointTabUV[i] = new Point[nbV];
    // }

    // SurfaceReglee(b1, b2, nbU, nbV, pointTabUV);
    // //AfficheGrill(pointTabUV, nbU, nbV);
    // for (int i = 0; i < nbV; i++){
    //   DrawCurve(pointTabUV[i], nbU);
    // }
  //Exercice 3

    long nbControlPoint = 3;

    Point P0 = Point(-2,1.0,0.0);
    Point P1 = Point(-1.0, 1.0,0.0);
    Point P2 = Point(0.0, 0.5,0.0);
    // Point TabControlPoint_1[nbControlPoint] = {P0,P1,P2};

    Point P4 = Point(1,2.0,0.0);
    Point P5 = Point(-1.0, 1.5,0.0);
    Point P6 = Point(0.0, 0.5,0.0);
    
    Point P8 = Point(1,2.0,1.0);
    Point P9 = Point(-1.0, 1.5,1.0);
    Point P10 = Point(0.0, 0.5,1.0);

    long nbU = 10;
    long nbV = 10;

    Point** GrilleControlPoint = new Point*[nbControlPoint];
    for(int i = 0; i < nbControlPoint; i++){
      GrilleControlPoint[i] = new Point[3];
    }
    GrilleControlPoint[0][0] = P0;
    GrilleControlPoint[0][1] = P1;
    GrilleControlPoint[0][2] = P2;
    GrilleControlPoint[1][0] = P4;
    GrilleControlPoint[1][1] = P5;
    GrilleControlPoint[1][2] = P6;
    GrilleControlPoint[2][0] = P8;
    GrilleControlPoint[2][1] = P9;
    GrilleControlPoint[2][2] = P10;
    //GrilleControlPoint[1] = {P4,P5,P6};
    //GrilleControlPoint[0] = {P8,P9,P10};

    Point** pointTabUV = new Point*[nbU];
    for(int i = 0; i < nbU; i++){
      pointTabUV[i] = new Point[nbV];
    }
    // Point TabControlPoint_2[nbControlPoint] = {P4,P5,P6};
    

    BezierSurfaceByBernstein(GrilleControlPoint, nbControlPoint, nbControlPoint,nbU, nbV,pointTabUV);
    for (int i = 0; i < nbV; i++){
      DrawCurve(pointTabUV[i], nbU);
    }
  //Exercice 1

  /*
    Point P0 = Point(0,0,0);
    Point P1 = Point(2,0,0);
    Vector V0 = Vector(1,1,0);
    Vector V1 = Vector(1,-1,0);
    int nbU = 10;
    Point tabPoint[nbU];
    HermiteCubicCurve(P0, P1, V0, V1, nbU, tabPoint);
    for(int i = 0; i< nbU; i++ ){
      printf(" p = %f %f %f\n", tabPoint[i].x, tabPoint[i].y, tabPoint[i].z);
    }
    DrawCurve(tabPoint, nbU);
  */

  
  /*Premier  jeu de données
  int nbU = 20;
  long nbControlPoint = 5;
  Point P0 = Point(-2,1.0,0.0);
  Point P1 = Point(-1.0, 2.0,0.0);
  Point P2 = Point(0.0, 0.5,0.0);
  Point P3 = Point(0.5, -2.0,0.0);
  Point P4 = Point(2.0,1.0,0.0);
  Point TabControlPoint[nbControlPoint] = {P0,P1,P2,P3,P4};
  //Point TabControlPoint2[2] = {P0,P5};
  Point pointTab[nbU];
  */

/*Deuxieme jeu de données
  int nbU = 20;
  long nbControlPoint = 4;
  Point P0 = Point(-2,1.0,0.0);
  Point P2 = Point(0.0, 0.5,0.0);
  Point P3 = Point(0.5, -2.0,0.0);
  Point P4 = Point(2.0,-2.0,0.0);
  Point TabControlPoint[nbControlPoint] = {P0,P2,P3,P4};
  //Point TabControlPoint2[2] = {P0,P5};
  Point pointTab[nbU];
  */

  //Exercice 2 : 

  /*
    DrawCurve(TabControlPoint, nbControlPoint);
    BezierCurveByBernstein(TabControlPoint, nbControlPoint, pointTab, nbU);
    DrawCurve(pointTab, nbU);
  */

  //Exercice 3 : 

  /* Afficher BezierCurveByCasteljau simplement

    BezierCurveByCasteljau(TabControlPoint, nbControlPoint, nbU, pointTab);
    DrawCurve(pointTab, nbU);

  */
 
  /* Afficher les étape intermediaire de BezierCurveByCasteljau
    
    BezierCurveByCasteljau2(TabControlPoint, nbControlPoint, nbU, pointTab);
    BezierCurveByCasteljau(TabControlPoint, nbControlPoint, nbU, pointTab);
    DrawCurve(pointTab, nbU);

  */


 // cr�ation d'un polygone
/*	glBegin(GL_POLYGON);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);
	glEnd();
*/


/*
// cr�ation d'un triangle
	glBegin(GL_TRIANGLES);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
	glEnd();
*/
}
