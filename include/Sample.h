#ifndef _SAMPLE_H
#define _SAMPLE_H

#include "Common.h"
#include "GameObject.h"

GLuint m_BigVAO;

void initVAO();
void initSample(vector<shared_ptr<GameObject> > &displayList,int numX,int numY, int numZ, float spacing, const vec3& startPosition);

/*
//http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/
bool TestRayOBBIntersection(
 	vec3 ray_origin,        // Ray origin, in world space
 	vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
 	vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
 	vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
 	mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
  float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB)
);*/

//void updateRenderQueue(vector<shared_ptr<GameObject> > &displayList,vector<shared_ptr<GameObject> > &renderQueue,const vec3& cameraPos);

void cleanUpSample();

#endif
