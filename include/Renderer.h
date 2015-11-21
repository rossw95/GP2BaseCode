#ifndef _RENDERER_H
#define _RENDERER_H

#include "Common.h"
#include "Vertices.h"

const int MAX_VBO_SIZE=100000;
const int MAX_EBO_SIZE=300000;

class Renderer
{
public:
  Renderer();
  ~Renderer();
  void createBuffers(int VBOSize,int EBOSize);
  int addToBuffers(Vertex * pVerts, int numVerts, int *pIndices, int numIndices);
  void render(int startIndex,int endIndex,int count);
private:
  GLuint m_staticVAO;
  GLuint m_staticVBO;
  GLuint m_staticEBO;
  int m_CurrentIndex;
  int m_CurrentVertex;
};


#endif
