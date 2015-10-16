#include "Vertices.h"

struct Mesh
{

  Vertex *pVerts;
  int numVerts;
  int *pIndices;
  int numIndices;

  public Mesh()
  {
    pVerts=NULL;
    numVerts=0;
    pIndices=NULL;
    numIndices=0;
  }

  public ~Mesh()
  {
    if (pVerts)
    {
      delete[] pVerts;
      pVerts=NULL;
    }
    if (pIndices)
    {
      delete[] pIndices;
      pIndices=NULL;
    }
  }

};
