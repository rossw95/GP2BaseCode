#ifndef _SAMPLE_H
#define _SAMPLE_H

#include "Common.h"
#include "GameObject.h"

void initSample(vector<shared_ptr<GameObject> > &displayList,int numX,int numY, int numZ, float spacing, const vec3& startPosition);

#endif
