#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "Common.h"

struct Vertex;

void initOpenGL();

void setViewport( int width, int height );

string getRendererCapsAsString();

#endif
