#ifndef FBXLoader_H
#define FBXLoader_H

#include "Common.h"
#include "Vertices.h"

bool loadFBXFromFile(const string& filename,Vertex **pVerts,int **pIndices);

void processNode(FbxNode *node);
void processAttribute(FbxNodeAttribute * attribute);
void processMesh(FbxMesh * mesh);
void processMeshNormals(FbxMesh * mesh, Vertex * verts, int numVerts);
void processMeshTextureCoords(FbxMesh * mesh, Vertex * verts, int numVerts);
void calculateTagentAndBinormals(Vertex * verts, int numVerts, int * indices, int numIndices);

#endif
