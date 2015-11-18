#include "GameObject.h"
#include "Shader.h"
#include "Texture.h"

GameObject::GameObject()
{
	m_Mesh=shared_ptr<Mesh>(new Mesh);
	m_ShaderProgram=0;

	m_ModelMatrix=mat4(1.0f);
	m_Position=vec3(0.0f);
	m_Rotation=vec3(0.0f);
	m_Scale=vec3(1.0f);

	m_AmbientMaterial = vec4(0.3f,0.3f,0.3f,1.0f);
	m_DiffuseMaterial=vec4(0.8f,0.8f,0.8f,1.0f);
	m_SpecularMaterial=vec4(1.0f,1.0f,1.0f,1.0f);
	m_SpecularPower=25.0f;

	m_ChildGameObjects.clear();

	m_ParentGameObject = NULL;
	m_DiffuseMap = 0;
}

GameObject::~GameObject()
{
	glDeleteProgram(m_ShaderProgram);
	glDeleteTextures(1, &m_DiffuseMap);
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
}

void GameObject::loadShader(const string& vsFilename, const string& fsFilename)
{
	GLuint vertexShaderProgram = 0;
	vertexShaderProgram = loadShaderFromFile(vsFilename, VERTEX_SHADER);
	checkForCompilerErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	fragmentShaderProgram = loadShaderFromFile(fsFilename, FRAGMENT_SHADER);
	checkForCompilerErrors(fragmentShaderProgram);

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);

	//Link attributes
	glBindAttribLocation(m_ShaderProgram, 0, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, 1, "vertexColour");
	glBindAttribLocation(m_ShaderProgram, 2, "vertexTexCoords");
	glBindAttribLocation(m_ShaderProgram, 3, "vertexNormal");

	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}

void GameObject::loadDiffuseMap(const string& filename)
{
	m_DiffuseMap = loadTextureFromFile(filename);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_2D);
}
