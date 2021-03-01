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

//
void DrawCurve(Point* TabPointOfCurve, long nbPoint){
  glBegin(GL_LINE_STRIP);
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
//
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



//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//D�finition de la couleur
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

    
  // Point P0 = Point(0,0,0);
  // Point P1 = Point(2,0,0);
  // Vector V0 = Vector(1,1,0);
  // Vector V1 = Vector(1,-1,0);
  // int nbU = 10;
  // Point tabPoint[nbU];
  // HermiteCubicCurve(P0, P1, V0, V1, nbU, tabPoint);
  // for(int i = 0; i< nbU; i++ ){
  //   printf(" p = %f %f %f\n", tabPoint[i].x, tabPoint[i].y, tabPoint[i].z);
  // }
  // DrawCurve(tabPoint, nbU);
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


  //BezierCurveByBernstein(TabControlPoint, nbControlPoint, pointTab, nbU);
  //DrawCurve(pointTab, nbU);
  BezierCurveByCasteljau(TabControlPoint, nbControlPoint, nbU, pointTab);
  DrawCurve(pointTab, nbU);

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
