#include "Sample.h"
#include "Cube.h"
#include "Mesh.h"
#include "Material.h"

string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
string fsPath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";


vector<shared_ptr<Material> > materialList;

void initSample(vector<shared_ptr<GameObject> > &displayList,int numX,int numY, int numZ, float spacing,const vec3& startPosition)
{
  shared_ptr<Mesh> mesh=shared_ptr<Mesh>(new Mesh);
  mesh->create(cubeVerts, numberOfCubeVerts, cubeIndices, numberOfCubeIndices);

  vec3 currentPos=startPosition;
  for (int y=0;y<numY;y++)
  {
    for (int x=0;x<numX;x++)
    {
      for (int z=0;z<numZ;z++)
      {
        shared_ptr<GameObject> gameObject=shared_ptr<GameObject>(new GameObject);
        gameObject->setMesh(mesh);
        gameObject->loadShader(vsPath, fsPath);

        gameObject->setPosition(currentPos);

        displayList.push_back(gameObject);

        currentPos.z+=spacing;
      }
      currentPos.x+=spacing;
      currentPos.z=startPosition.z;
    }
    currentPos.x=startPosition.x;
    currentPos.y+=spacing;
    currentPos.z=startPosition.z;
  }
}
