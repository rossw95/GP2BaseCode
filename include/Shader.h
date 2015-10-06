#ifndef _shader_h
#define _shader_h
#include "Common.h"

;enum SHADER_TYPE
{

	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	

};
GLuint loadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType);

GLuint loadShaderFromFile(const std::string&filename, SHADER_TYPE shaderType);
bool checkForCompilerError(GLuint shaderProgram);
bool checkForLinkErrors(GLuint program);
#endif



