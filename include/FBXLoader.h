#ifndef FBXLoader_H
#define FBXLoader_H

#include "Common.h"
#include "Mesh.h"
#include "Vertices.h"

bool loadFBXFromFile(const string& filename, MeshData *meshData);

void processNode(FbxNode *node, MeshData *meshData);
void processAttribute(FbxNodeAttribute * attribute, MeshData *meshData);
void processMesh(FbxMesh * mesh, MeshData *meshData);
void processMeshNormals(FbxMesh * mesh, Vertex * verts, int numVerts);
void processMeshTextureCoords(FbxMesh * mesh, Vertex * verts, int numVerts);
void calculateTagentAndBinormals(Vertex * verts, int numVerts, int * indices, int numIndices);

#endif
