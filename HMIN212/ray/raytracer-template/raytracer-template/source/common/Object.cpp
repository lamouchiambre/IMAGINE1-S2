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
  // R0 = p0; Rd = V; 
  A = (V.x*V.x + V.y*V.y + V.z*V.z);
  B = 2 * (V.x * (p0.x - center.x) + V.y * (p0.y - center.y) + V.z * (p0.z - center.z));
  C = (p0.x - center.x)*(p0.x - center.x) + (p0.y - center.y)*(p0.y - center.y) + (p0.z - center.z)*(p0.z - center.z) - radius*radius;
  //std::cout<<"a= "<<A<<" b= "<<B<<" c= "<<C<<" "<<sqrt(B*B - 4*A*C)<<std::endl; (B*B - 4*A*C) >= 0
  if((B*B - 4*A*C) >= 0){
    double t1 = ((-B - sqrt(B*B - 4*A*C))/2);
    double t2 = ((-B + sqrt(B*B - 4*A*C))/2);
    //std::cout << "t1 = " << t1 <<" t2 = " << t2 << std::endl;
    if (t1 > EPSILON){
      //prendre t1;
      t = ((p0.x + t1*V.x)*(p0.x + t1*V.x) + (p0.y + t1*V.y)*(p0.y + t1*V.y) + (p0.z + t1*V.z)*(p0.z + t1*V.z));
    } else
    {
      if(t1 < EPSILON && t2 > EPSILON){
        t = ((p0.x + t2*V.x)*(p0.x + t2*V.x) + (p0.y + t2*V.y)*(p0.y + t2*V.y) + (p0.z + t2*V.z)*(p0.z + t2*V.z));
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
