#ifndef _MESH_H
#define _MESH_H

#include "Vertices.h"
#include "Common.h"

struct MeshData{

	vector<Vertex> vertices;
	vector<int> indices;

	int getNumVerts(){


		return vertices.size();

	}

	int getNumberIndices(){


		return indices.size();

	}

	~MeshData(){


		vertices.clear();
		indices.clear();
	}


};

#endif