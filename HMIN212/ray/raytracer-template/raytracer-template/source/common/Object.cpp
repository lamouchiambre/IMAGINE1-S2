//////////////////////////////////////////////////////////////////////////////
//
//  --- Object.cpp ---
//  Created by Brian Summa
//
//////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "common.h"

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Sphere::intersect(vec4 p0, vec4 V){
  IntersectionValues result;
  //TODO: Ray-sphere setup
  result.P = p0;
  result.N = V;
  result.t = raySphereIntersection(p0,V);
  result.ID_ = 1;
  //std::cout << center.x << " " << center.y << " " << center.z << std::endl;
  return result;
}

/* -------------------------------------------------------------------------- */
/* ------ Ray = p0 + t*V  sphere at origin center and radius radius    : Find t ------- */
double Sphere::raySphereIntersection(vec4 p0, vec4 V){
  double t = std::numeric_limits< double >::infinity();
  //TODO: Ray-sphere intersection;
  vec3 rayon(p0.x, p0.y, p0.z);
  double A; double B; double C;
  
  A = (V.x*V.x + V.y*V.y + V.z*V.z);
  B = 2.0 * (V.x * (p0.x - center.x) + V.y * (p0.y - center.y) + V.z * (p0.z - center.z));
  C = (p0.x - center.x)*(p0.x - center.x) + (p0.y - center.y)*(p0.y - center.y) + (p0.z - center.z)*(p0.z - center.z) - radius*radius;
  
  if((B*B - 4.0*A*C) >= 0){
    double t1 = ((-B - sqrt(B*B - 4.0*A*C))/2.0*A);
    double t2 = ((-B + sqrt(B*B - 4.0*A*C))/2.0*A);
    
    if (t1 > EPSILON){
      //prendre t1;
      t = t1;
      //(( t1*V.x - p0.x )*( t1*V.x - p0.x ) + ( t1*V.y - p0.y)*(t1*V.y - p0.y) + (t1*V.z - p0.z)*(t1*V.z - p0.z));
    } else
    {
      if(t1 < EPSILON && t2 > EPSILON){
        t = t2;
        //(( t2*V.x - p0.x )*( t2*V.x - p0.x ) + ( t2*V.y - p0.y)*(t2*V.y - p0.y) + (t2*V.z - p0.z)*(t2*V.z - p0.z));
        //std::cout << "t2 " ;
      }
    } 
  }
  

  return t;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Square::intersect(vec4 p0, vec4 V){
  IntersectionValues result;
  //TODO: Ray-square setup
  result.P = p0;
  result.N = V;
  result.t = raySquareIntersection(p0,V);
  result.ID_ = 1;
  return result;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
double Square::raySquareIntersection(vec4 p0, vec4 V){
  double t   = std::numeric_limits< double >::infinity();
  //TODO: Ray-square intersection;
  this->normal.x;
  //determination de l'equation cartesienne Ax + By + Cz + D = 0
  //Determiner D = -(Apx + Bpy +Cpz)
  double A = normal.x;
  double B = normal.y;
  double C = normal.z;
  double D = -(A * point.x + B * point.y + C * point.z);

  if ((A*p0.x + B*p0.y + C*p0.z) != 0)
  {
    double tmp = -(A*p0.x + B*p0.y + C*p0.z + D)/(A*V.x + B*V.y + C * V.z);

    if(tmp > EPSILON){
      t = tmp;
      //( tmp*V.x - p0.x )*(tmp*V.x - p0.x ) 
      //    + ( tmp*V.y - p0.y )*(tmp*V.y - p0.y )
      //    + (tmp*V.z - p0.z  )*(tmp*V.z - p0.z);
          //t = tmp;
      // t est dans le plan, il faut verifier si le point est dans le carrer
      
      //projection sur le plan
      vec3 a, b, c, d, vt;
      if (C > 0.5){
        //oublier z
        a = { mesh.vertices[5].x, mesh.vertices[5].y };
        b = { mesh.vertices[1].x, mesh.vertices[1].y };
        c = { mesh.vertices[2].x, mesh.vertices[2].y };
        d = { mesh.vertices[3].x, mesh.vertices[3].y };
        vt = {p0.x+ t*V.x,p0.y+ t*V.y };
      }else
      {
        if (A > 0.5)
        {
          //oublier x
          a = { mesh.vertices[5].y, mesh.vertices[5].z };
          b = { mesh.vertices[1].y, mesh.vertices[1].z };
          c = { mesh.vertices[2].y, mesh.vertices[2].z };
          d = { mesh.vertices[3].y, mesh.vertices[3].z };
          vt = {p0.y + t*V.y, p0.z + t*V.z };
        }
        else
        {
          // oublier y 
          a = { mesh.vertices[5].x, mesh.vertices[5].z };
          b = { mesh.vertices[1].x, mesh.vertices[1].z };
          c = { mesh.vertices[2].x, mesh.vertices[2].z };
          d = { mesh.vertices[3].x, mesh.vertices[3].z };
          vt = {p0.x + t*V.x, p0.z + t*V.z };
        }

        // double p1 = cross();
        // double p2
        // double p3
        // double p4
        /*a continier */
      }
      

    }

  }
  
  return t;
}
