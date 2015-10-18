#ifndef _MESH_H
#define _MESH_H

#include <vector>

using namespace std;


#include "Vertices.h"

struct MeshData
{
	vector<Vertex> vertices;
	vector<int> indices;

	int getNumVerts()
	{
		return vertices.size();
	};

	int getNumIndices()
	{
		return indices.size();
	};

	~MeshData()
	{
		vertices.clear();
		vertices.clear();
	}
};

#endif