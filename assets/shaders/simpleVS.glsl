#version 150

//The input vertex
in vec3 vertexPosition;

//The MVP matrix
uniform mat4 MVP;

//The main function
void main()
{
  //Calculate the transformed position
  gl_Position = MVP * vec4(vertexPosition, 1.0);
}
