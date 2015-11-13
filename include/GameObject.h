#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h"
#include "Vertices.h"
class GameObject
{
public:

	GameObject();
	~GameObject();

	void update();
	void createBuffer(Vertex *pverts, int numVerts, int *pIndices, int numIndices);

	void loadShader(const string& vsFilename, const string& fsFilename);
private:
	GLuint getShaderProgram(){

		m_shaderProgram;
	}
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;
	GLuint m_shaderProgram;
	int m_NoOfVertices;
	int m_NoOfIndices;

	mat4 m_ModelMatrix;
	vec3 m_Position;
	vec3 m_Rotaton;
	vec3 m_Scale;

	vec4 m_ambientMaterialColour;
	vec4 m_diffuseMaterialColour;
	vec4 m_specularMaterialColour;
	float m_specularPower;

protected:

};
#endif

