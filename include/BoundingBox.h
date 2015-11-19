#ifndef _BOUNDINGBOX_H
#define _BOUNDINGBOX_H

#include "Common.h"
#include "Vertices.h"

class BoundingBox
{
public:
  BoundingBox();
  ~BoundingBox();

  void calculate(Vertex * pVerts,int numVerts);

  vec3 m_Min;
  vec3 m_Max;
  mat4 m_ModelMatrix;
};

#endif
