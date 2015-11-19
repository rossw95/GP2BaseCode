#include "Sample.h"
#include "Cube.h"
#include "Mesh.h"
#include "Material.h"
#include <cstdio>
#include <ctime>
#include <algorithm>

string vsSimplePath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
string fsSimplePath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";

string vsSpecularPath=ASSET_PATH+SHADER_PATH+"/specularVS.glsl";
string fsSpecularPath=ASSET_PATH+SHADER_PATH+"/specularFS.glsl";

string vsTexturePath=ASSET_PATH+SHADER_PATH+"/textureVS.glsl";
string fsTexturePath=ASSET_PATH+SHADER_PATH+"/textureFS.glsl";

string texturePath=ASSET_PATH+TEXTURE_PATH+"/texture.png";

vector<shared_ptr<Material> > materialList;
/*
bool TestRayOBBIntersection(
 	vec3 ray_origin,
 	vec3 ray_direction,
 	vec3 aabb_min,
 	vec3 aabb_max,
 	mat4 ModelMatrix,
  float& intersection_distance
)
{
  // Intersection method from Real-Time Rendering and Essential Mathematics for Games

  	float tMin = 0.0f;
  	float tMax = 100000.0f;

  	glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

  	glm::vec3 delta = OBBposition_worldspace - ray_origin;

  	// Test intersection with the 2 planes perpendicular to the OBB's X axis
  	{
  		glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
  		float e = glm::dot(xaxis, delta);
  		float f = glm::dot(ray_direction, xaxis);

  		if ( fabs(f) > 0.001f ){ // Standard case

  			float t1 = (e+aabb_min.x)/f; // Intersection with the "left" plane
  			float t2 = (e+aabb_max.x)/f; // Intersection with the "right" plane
  			// t1 and t2 now contain distances betwen ray origin and ray-plane intersections

  			// We want t1 to represent the nearest intersection,
  			// so if it's not the case, invert t1 and t2
  			if (t1>t2){
  				float w=t1;t1=t2;t2=w; // swap t1 and t2
  			}

  			// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
  			if ( t2 < tMax )
  				tMax = t2;
  			// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
  			if ( t1 > tMin )
  				tMin = t1;

  			// And here's the trick :
  			// If "far" is closer than "near", then there is NO intersection.
  			// See the images in the tutorials for the visual explanation.
  			if (tMax < tMin )
  				return false;

  		}else{ // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
  			if(-e+aabb_min.x > 0.0f || -e+aabb_max.x < 0.0f)
  				return false;
  		}
  	}


  	// Test intersection with the 2 planes perpendicular to the OBB's Y axis
  	// Exactly the same thing than above.
  	{
  		glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
  		float e = glm::dot(yaxis, delta);
  		float f = glm::dot(ray_direction, yaxis);

  		if ( fabs(f) > 0.001f ){

  			float t1 = (e+aabb_min.y)/f;
  			float t2 = (e+aabb_max.y)/f;

  			if (t1>t2){float w=t1;t1=t2;t2=w;}

  			if ( t2 < tMax )
  				tMax = t2;
  			if ( t1 > tMin )
  				tMin = t1;
  			if (tMin > tMax)
  				return false;

  		}else{
  			if(-e+aabb_min.y > 0.0f || -e+aabb_max.y < 0.0f)
  				return false;
  		}
  	}


  	// Test intersection with the 2 planes perpendicular to the OBB's Z axis
  	// Exactly the same thing than above.
  	{
  		glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
  		float e = glm::dot(zaxis, delta);
  		float f = glm::dot(ray_direction, zaxis);

  		if ( fabs(f) > 0.001f ){

  			float t1 = (e+aabb_min.z)/f;
  			float t2 = (e+aabb_max.z)/f;

  			if (t1>t2){float w=t1;t1=t2;t2=w;}

  			if ( t2 < tMax )
  				tMax = t2;
  			if ( t1 > tMin )
  				tMin = t1;
  			if (tMin > tMax)
  				return false;

  		}else{
  			if(-e+aabb_min.z > 0.0f || -e+aabb_max.z < 0.0f)
  				return false;
  		}
  	}

  	intersection_distance = tMin;
  	return true;
}*/

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
