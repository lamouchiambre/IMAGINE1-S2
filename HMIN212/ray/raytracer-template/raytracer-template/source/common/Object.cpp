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
    /*
    if(!(t1 < 0 && t2 < 0)){
      double det1 = std::max(t1,t2);
      double det2 = std::min(t1,t2);
      if (det2 < 0)
      {
        t = ((p0.x + det1*V.x)*(p0.x + det1*V.x) + (p0.y + det1*V.y)*(p0.y + det1*V.y) + (p0.z + det1*V.z)*(p0.z + det1*V.z));
      }else
      {
        t = ((p0.x + det2*V.x)*(p0.x + det2*V.x) + (p0.y + det2*V.y)*(p0.y + det2*V.y) + (p0.z + det2*V.z)*(p0.z + det2*V.z));
      }
      
      
    } */
    
    if (t1 > EPSILON){
      //prendre t1;
      t = (( t1*V.x - p0.x )*( t1*V.x - p0.x ) + ( t1*V.y - p0.y)*(t1*V.y - p0.y) + (t1*V.z - p0.z)*(t1*V.z - p0.z));
    } else
    {
      if(t1 < EPSILON && t2 > EPSILON){
        t = (( t2*V.x - p0.x )*( t2*V.x - p0.x ) + ( t2*V.y - p0.y)*(t2*V.y - p0.y) + (t2*V.z - p0.z)*(t2*V.z - p0.z));
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
  
  return result;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
double Square::raySquareIntersection(vec4 p0, vec4 V){
  double t   = std::numeric_limits< double >::infinity();
  //TODO: Ray-square intersection;
  return t;
}
