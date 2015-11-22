#include "GameObject.h"
#include "Shader.h"
#include "Texture.h"

GameObject::GameObject()
{
	m_Mesh=shared_ptr<Mesh>(NULL);
	m_Material=shared_ptr<Material>(NULL);

	m_ModelMatrix=mat4(1.0f);
	m_Position=vec3(0.0f);
	m_Rotation=vec3(0.0f);
	m_Scale=vec3(1.0f);


	m_ChildGameObjects.clear();

	m_ParentGameObject = NULL;
}

GameObject::~GameObject()
{
	m_ChildGameObjects.clear();
}

void GameObject::update()
{
	mat4 parentModel(1.0f);
	if (m_ParentGameObject)
	{
		parentModel = m_ParentGameObject->getModelMatrix();
	}
	mat4 translationMatrix = translate(mat4(1.0f), m_Position);
	mat4 scaleMatrix = scale(mat4(1.0f), m_Scale);

	mat4 rotationMatrix = rotate(mat4(1.0f), m_Rotation.x, vec3(1.0f, 0.0f, 0.0f))*
		rotate(mat4(1.0f), m_Rotation.y, vec3(0.0f, 1.0f, 0.0f))*
		rotate(mat4(1.0f), m_Rotation.z, vec3(0.0f, 0.0f, 1.0f));

	m_ModelMatrix = scaleMatrix*rotationMatrix*translationMatrix;
	m_ModelMatrix *= parentModel;

	m_Bounds.m_ModelMatrix=m_ModelMatrix;

	for (auto iter = m_ChildGameObjects.begin(); iter != m_ChildGameObjects.end(); iter++)
	{
		(*iter)->update();
	}
}

void GameObject::addChild(shared_ptr<GameObject> child)
{
	child->m_ParentGameObject = this;
	m_ChildGameObjects.push_back(child);
}

void GameObject::createBuffers(Vertex * pVerts, int numVerts, int *pIndices, int numIndices)
{
	m_Mesh=shared_ptr<Mesh>(new Mesh);
	m_Mesh->create(pVerts,numVerts,pIndices,numIndices);
	m_Bounds.calculate(pVerts,numVerts);
}

void GameObject::loadShader(const string& vsFilename, const string& fsFilename)
{
	m_Material=shared_ptr<Material>(new Material);
	m_Material->loadShader(vsFilename,fsFilename);
}

void GameObject::loadDiffuseMap(const string& filename)
{
	m_Material->loadDiffuseMap(filename);
}
