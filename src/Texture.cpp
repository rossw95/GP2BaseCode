#include "Texture.h"

GLuint	loadTextureFromFile(const string&	filename)
{
	SDL_Surface	*imageSurface = IMG_Load(filename.c_str());
	if (!imageSurface){

		cout << "Can't Load	image " << filename << " " << IMG_GetError();
		return	0;
	}

	GLuint textureID = convertSDLSurfaceToTexture(imageSurface);
	SDL_FreeSurface(imageSurface);

	return textureID;
}

GLuint convertSDLSurfaceToTexture(SDL_Surface * surface)
{
	GLuint textureID = 0;
	GLint		nOfColors = surface->format->BytesPerPixel;

	GLenum	textureFormat = GL_RGB;

	if (nOfColors == 4)					//	contains	an	alpha	channel
	{
		if (surface->format->Rmask == 0x000000ff)
			textureFormat = GL_RGBA;
		else
			textureFormat = GL_BGRA;
	}
	else if (nOfColors == 3)					//	no	alpha	channel
	{
		if (surface->format->Rmask == 0x000000ff)
			textureFormat = GL_RGB;
		else
			textureFormat = GL_BGR;
	}
	else{
		cout<< "warning: the image is not truecolor.. this will	probably break";
		return 0;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, surface->w, surface->h, 0, textureFormat,
		GL_UNSIGNED_BYTE, surface->pixels);

	return textureID;
}