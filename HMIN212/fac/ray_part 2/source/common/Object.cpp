//////////////////////////////////////////////////////////////////////////////
//
//  --- Object.cpp ---
//  Created by Brian Summa
//
//////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "common.h"

Object::IntersectionValues Mash::intersect(vec4 p0, vec4 V){
  IntersectionValues result;

  //this->center;
  //vec4 norm = center//vec4(p0.x - this->center.x, p0.y - this->center.y, p0.z - this->center.z, 0);
  result.t = rayMashIntersection(p0,V);
  result.P = p0 +  result.t * V;
  result.ID_ = 1;
  result.N = p0;
  return result;
}

double Mash::rayMashIntersection(vec4 p0, vec4 V){
  double t = std::numeric_limits< double >::infinity();

  return t;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Sphere::intersect(vec4 p0, vec4 V){
  IntersectionValues result;

  //this->center;
  //vec4 norm = center//vec4(p0.x - this->center.x, p0.y - this->center.y, p0.z - this->center.z, 0);
  result.t = raySphereIntersection(p0,V);
  result.P = p0 +  result.t * V;
  result.ID_ = 1;
  result.N = C * normalize(result.P - this->center);
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
    } else
    {
      if(t1 < EPSILON && t2 > EPSILON){
        t = t2;
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
  
  result.N = C * this->normal;
  result.t = raySquareIntersection(p0,V);
  result.P = p0 +  result.t * V;
  result.ID_ = 2;
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

    if(tmp > 0){
      t = tmp;

      //vec3 ab, bc, cd, da, ap, bp, cp, dp;
      vec3 a, b, c, d, p;
      a = { mesh.vertices[5].x, mesh.vertices[5].y, mesh.vertices[5].z };
      b = { mesh.vertices[1].x, mesh.vertices[1].y, mesh.vertices[1].z };
      c = { mesh.vertices[2].x, mesh.vertices[2].y, mesh.vertices[2].z };
      d = { mesh.vertices[3].x, mesh.vertices[3].y, mesh.vertices[3].z };
      p = {p0.x+ t*V.x,p0.y+ t*V.y, p0.z+ t*V.z };

        vec3 ab = {b.x - a.x, b.y - a.y, b.z - a.z};
        vec3 bc = {c.x - b.x, c.y - b.y, c.z - b.z };
        vec3 cd = {d.x - c.x, d.y - c.y, d.z - c.z};
        vec3 da = {a.x - d.x, a.y - d.y, a.z - d.z};

        vec3 ap = {p.x - a.x, p.y - a.y, p.z - a.z};
        vec3 bp = {p.x - b.x, p.y - b.y, p.z - b.z};
        vec3 cp = {p.x - c.x, p.y - c.y, p.z - c.z};
        vec3 dp = {p.x - d.x, p.y - d.y, p.z - d.z};

        /*-----------------------------*/

        double p1 = dot(ab, ap);
        double p2 = dot(bc, bp);
        double p3 = dot(cd, cp);
        double p4 = dot(da, dp);

        if(!(p1 >= 0 && p2 >= 0 && p3 >= 0 && p4 >= 0)){
          t = std::numeric_limits< double >::infinity();
        }
    }

  }
  
  return t;
}
