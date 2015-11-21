#include "Sample.h"
#include <cstdio>
#include <ctime>
#include <algorithm>

#include "Cube.h"

string vsSimplePath = ASSET_PATH + SHADER_PATH + "/simpleInstanceVS.glsl";
string fsSimplePath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";

string vsSpecularPath=ASSET_PATH+SHADER_PATH+"/specularInstanceVS.glsl";
string fsSpecularPath=ASSET_PATH+SHADER_PATH+"/specularFS.glsl";

string vsTexturePath=ASSET_PATH+SHADER_PATH+"/textureInstanceVS.glsl";
string fsTexturePath=ASSET_PATH+SHADER_PATH+"/simpleFS.glsl";

string texturePath=ASSET_PATH+TEXTURE_PATH+"/texture.png";

vector<shared_ptr<Material> > materialList;
vector<shared_ptr<Instance> > instanceList;

void sortGameObjects(vector<shared_ptr<GameObject> > &displayList)
{
  std::sort(displayList.begin(), displayList.end());
}

void createMaterials()
{

  shared_ptr<Material> simpleMaterial=shared_ptr<Material>(new Material);
  simpleMaterial->loadShader(vsSimplePath,fsSimplePath);
  materialList.push_back(simpleMaterial);

  shared_ptr<Material> greenMaterial=shared_ptr<Material>(new Material);
  greenMaterial->loadShader(vsSpecularPath,fsSpecularPath);
  greenMaterial->setDiffuseMaterial(vec4(0.0f,1.0f,0.0f,1.0f));
  materialList.push_back(greenMaterial);

  shared_ptr<Material> redMaterial=shared_ptr<Material>(new Material);
  redMaterial->loadShader(vsSpecularPath,fsSpecularPath);
  redMaterial->setDiffuseMaterial(vec4(1.0f,0.0f,0.0f,1.0f));
  materialList.push_back(redMaterial);

  shared_ptr<Material> blueMaterial=shared_ptr<Material>(new Material);
  blueMaterial->loadShader(vsSpecularPath,fsSpecularPath);
  blueMaterial->setDiffuseMaterial(vec4(0.0f,0.0f,1.0f,1.0f));
  materialList.push_back(blueMaterial);

  shared_ptr<Material> faceMaterial=shared_ptr<Material>(new Material);
  faceMaterial->loadShader(vsTexturePath,fsTexturePath);
  faceMaterial->loadDiffuseMap(texturePath);
  materialList.push_back(faceMaterial);
}

void initSample(vector<shared_ptr<GameObject> > &displayList,int numX,int numY, int numZ, float spacing,const vec3& startPosition)
{
  shared_ptr<Mesh> mesh=shared_ptr<Mesh>(new Mesh);
  mesh->create(cubeVerts, numberOfCubeVerts, cubeIndices, numberOfCubeIndices);
  srand(time(NULL));
  createMaterials();

  vec3 currentPos=startPosition;
  for (int y=0;y<numY;y++)
  {
    for (int x=0;x<numX;x++)
    {
      for (int z=0;z<numZ;z++)
      {
        shared_ptr<GameObject> gameObject=shared_ptr<GameObject>(new GameObject);
        gameObject->setMesh(mesh);

        int materialID=rand()%materialList.size();
        cout<<"Material ID "<<materialID<<endl;
        gameObject->setMaterial(materialList[materialID]);
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
  //sortGameObjects(displayList);
}

void cleanUpSample()
{

}

/*
//brute force
void visibilityTest(shared_ptr<GameObject> currentObj,vector<shared_ptr<GameObject> > &displayList,vector<shared_ptr<GameObject> > &renderQueue,
    const vec3& cameraPos)
{
  vec3 rayDirection=currentObj->getPosition()-cameraPos;
  rayDirection=normalize(rayDirection);
  BoundingBox currentBox=currentObj->getBounds();

  float distance=0.0f;
  float minDistance=0.0f;
  TestRayOBBIntersection(cameraPos,rayDirection,currentBox.m_Min,currentBox.m_Max,currentBox.m_ModelMatrix,distance);
  //cout<<"Distance "<<distance<<endl;
  for (auto iter=displayList.begin();iter!=displayList.end();iter++)
  {
    if ((*iter)!=currentObj)
    {
      float currentMinDistance=0.0f;
      TestRayOBBIntersection(cameraPos,rayDirection,currentBox.m_Min,currentBox.m_Max,currentBox.m_ModelMatrix,currentMinDistance);
      if (currentMinDistance<minDistance)
      {
        minDistance=currentMinDistance;
      }
    }
  }

  if (distance==0.0f)
  {
    //do nothing
  }
  if (distance<minDistance)
  {
    cout<<"Distance "<<distance<<" "<<minDistance<<endl;
    //renderQueue.push_back(currentObj);
  }
}

void updateRenderQueue(vector<shared_ptr<GameObject> > &displayList,vector<shared_ptr<GameObject> > &renderQueue,
    const vec3& cameraPos)
{
  //cast a ray from the camera to the current game object
  //renderQueue=displayList;
  for (auto iter=displayList.begin();iter!=displayList.end();iter++)
  {
    visibilityTest((*iter),displayList,renderQueue,cameraPos);
  }
  sortGameObjects(renderQueue);
}*/
