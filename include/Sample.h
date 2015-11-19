#ifndef _SAMPLE_H
#define _SAMPLE_H

#include "Common.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"


struct Instance
{
  shared_ptr<Mesh> mesh;
  shared_ptr<Material> material;
  GLuint instanceVBO;
  int numberOfInstances;
};

extern GLuint instanceVBO;

void initVBO(int size);
void initSample(vector<shared_ptr<GameObject> > &displayList,int numX,int numY, int numZ, float spacing, const vec3& startPosition);

void cleanUpSample();

#endif
