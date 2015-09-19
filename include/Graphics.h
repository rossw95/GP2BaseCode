#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "Common.h"

struct Vertex;

void initOpenGL();

void setViewport( int width, int height );

GLuint createAndFillBuffer(Vertex *pVerts, int count);

string getRendererCapsAsString();

void setCameraProperties(float xPos, float yPos, float zPos, float xLook, float yLook, float zLook, float xUp, float yUp, float zUp);

#endif
