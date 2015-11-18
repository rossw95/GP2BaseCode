#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Common.h"

class Material
{
public:
  Material();
  ~Material();

  void loadShader(const string& vsFilename, const string& fsFilename);
  void loadDiffuseMap(const string& filename);

  vec4& getAmbientMaterial()
  {
    return m_AmbientMaterial;
  };

  vec4& getDiffuseMaterial()
  {
    return m_DiffuseMaterial;
  };

  vec4& getSpecularMaterial()
  {
    return m_SpecularMaterial;
  };

  float getSpecularPower()
  {
    return m_SpecularPower;
  };

  GLuint getShaderProgram()
  {
    return m_ShaderProgram;
  };

  GLuint getDiffuseMap()
  {
    return m_DiffuseMap;
  };
private:
  GLuint m_ShaderProgram;

  vec4 m_AmbientMaterial;
  vec4 m_DiffuseMaterial;
  vec4 m_SpecularMaterial;
  float m_SpecularPower;

  GLuint m_DiffuseMap;
};
#endif
