#ifndef FBXLoader_H
#define FBXLoader_H

#include "Common.h"
#include "Mesh.h"
#include "Vertices.h"
#include <fbxsdk.h>


bool loadFBXFromFile(const string& filename, MeshData * meshData);

void processNode(FbxNode *node, MeshData * meshData);
void processAttribute(FbxNodeAttribute * attribute, MeshData * meshData);
void processMesh(FbxMesh * mesh, MeshData * meshData);
void processMeshTextureCoords(FbxMesh * mesh, Vertex * verts, int numbVerts);
void processMeshNormals(FbxMesh * mesh, Vertex * verts, int numVerts);



#endif
