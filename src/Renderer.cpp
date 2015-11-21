#include "Renderer.h"

Renderer::Renderer()
{
  m_staticVAO=0;
  m_CurrentIndex=0;
  m_CurrentVertex=0;
  m_staticVBO=0;
  m_staticEBO=0;
}

Renderer::~Renderer()
{
  glDeleteBuffers(1, &m_staticVBO);
	glDeleteBuffers(1, &m_staticEBO);
	glDeleteVertexArrays(1, &m_staticVAO);
}

void Renderer::createBuffers(int VBOSize,int EBOSize)
{
  //Generate Vertex Array
	glGenVertexArrays(1, &m_staticVAO);
	glBindVertexArray(m_staticVAO);

	glGenBuffers(1, &m_staticVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_staticVBO);

	glBufferData(GL_ARRAY_BUFFER, VBOSize, NULL, GL_STATIC_DRAW);

	//create buffer
	glGenBuffers(1, &m_staticEBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_staticEBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOSize, NULL, GL_STATIC_DRAW);

  //Tell the shader that 0 is the position element
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
}

int Renderer::addToBuffers(Vertex * pVerts, int numVerts, int *pIndices, int numIndices)
{
  //we need to check to see if we have space!
  int startIndex=m_CurrentIndex;
  glBindVertexArray(m_staticVAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_staticVBO);
  glBufferSubData(GL_ARRAY_BUFFER,m_CurrentVertex*sizeof(Vertex),numVerts*sizeof(Vertex),pVerts);

  m_CurrentVertex+=numVerts;

  glBindBuffer(GL_ARRAY_BUFFER, m_staticVBO);
  glBufferSubData(GL_ARRAY_BUFFER,m_CurrentIndex*sizeof(int),numIndices*sizeof(int),pIndices);

  m_CurrentIndex+=numIndices;

  return startIndex;
}

void Renderer::render(int startIndex,int endIndex,int count)
{
  glDrawRangeElements(	GL_TRIANGLES,startIndex,endIndex,count,GL_UNSIGNED_INT,NULL);
}
