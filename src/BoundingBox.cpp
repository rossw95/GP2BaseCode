#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
  m_Min=vec3(0.0f);
  m_Max=vec3(0.0f);
  m_ModelMatrix=mat4(1.0f);
}

BoundingBox::~BoundingBox()
{

}

void BoundingBox::calculate(Vertex * pVerts,int numVerts)
{
  m_Min = pVerts[0].position;
  m_Max = pVerts[0].position;
  for (int i = 1; i < numVerts; ++i)
  {
  if ( pVerts[i].position.x < m_Min.x ) m_Min.x = pVerts[i].position.x;
  if ( pVerts[i].position.y < m_Min.y ) m_Min.y = pVerts[i].position.y;
  if ( pVerts[i].position.z < m_Min.z ) m_Min.z = pVerts[i].position.z;
  if ( pVerts[i].position.x > m_Max.x ) m_Max.x = pVerts[i].position.x;
  if ( pVerts[i].position.y > m_Max.y ) m_Max.y = pVerts[i].position.y;
  if ( pVerts[i].position.z > m_Max.z ) m_Max.z = pVerts[i].position.z;
  }
}
