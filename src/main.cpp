#include "Common.h"
#include "Graphics.h"
#include "Vertices.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "FBXLoader.h"
#include "FileSystem.h"
#include "GameObject.h"
#include "Sample.h"

//matrices
mat4 viewMatrix;
mat4 projMatrix;

mat4 MVPMatrix;

vector<shared_ptr<GameObject> > gameObjects;
vector<shared_ptr<GameObject> > renderQueue;

GLuint currentShaderProgam = 0;
GLuint currentDiffuseMap = 0;


vec4 ambientLightColour=vec4(1.0f,1.0f,1.0f,1.0f);
vec4 diffuseLightColour=vec4(1.0f,1.0f,1.0f,1.0f);
vec4 specularLightColour=vec4(1.0f,1.0f,1.0f,1.0f);
float specularPower=25.0f;

vec3 lightDirection=vec3(0.0f,0.0f,1.0f);
vec3 cameraPosition=vec3(10.0f,10.0f,60.0f);

//for Framebuffer
GLuint FBOTexture;
GLuint FBODepthBuffer;
GLuint frameBufferObject;
GLuint fullScreenVAO;
GLuint fullScreenVBO;
GLuint fullScreenShaderProgram;
const int FRAME_BUFFER_WIDTH = 640;
const int FRAME_BUFFER_HEIGHT = 480;

//timing
unsigned int lastTicks, currentTicks;
float elapsedTime;
float totalTime;
int frameCounter=0;
float FPS;
float frameTime;

void initScene()
{
	currentTicks=SDL_GetTicks();
	totalTime=0.0f;
	initSample(gameObjects,20,20,20,1.1, vec3(0.0f,0.0f,0.0f));
}

void cleanUp()
{
	cleanUpSample();
	gameObjects.clear();
}

void update()
{
	frameCounter++;
	lastTicks=currentTicks;
	currentTicks=SDL_GetTicks();
	elapsedTime = (currentTicks - lastTicks) / 1000.0f;
	totalTime+=elapsedTime;
	frameTime+=elapsedTime;
	if (frameTime>1.0f)
	{
		FPS=frameCounter;
		frameTime=0.0f;
		frameCounter=0;
		cout<<"FPS "<<FPS<<endl;
	}

	projMatrix = perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

	viewMatrix = lookAt(cameraPosition, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
	{
		(*iter)->update();
	}

	renderQueue=gameObjects;
}

void renderGameObject(shared_ptr<GameObject> gameObject)
{
	MVPMatrix = projMatrix*viewMatrix*gameObject->getModelMatrix();

	if (gameObject->getShaderProgram() > 0){
		currentShaderProgam = gameObject->getShaderProgram();
		glUseProgram(currentShaderProgam);
	}

	GLint MVPLocation = glGetUniformLocation(currentShaderProgam, "MVP");

	GLint ambientLightColourLocation = glGetUniformLocation(currentShaderProgam, "ambientLightColour");
	GLint ambientMaterialColourLocation = glGetUniformLocation(currentShaderProgam, "ambientMaterialColour");

	GLint diffuseLightColourLocation = glGetUniformLocation(currentShaderProgam, "diffuseLightColour");
	GLint diffuseLightMaterialLocation = glGetUniformLocation(currentShaderProgam, "diffuseMaterialColour");
	GLint lightDirectionLocation = glGetUniformLocation(currentShaderProgam, "lightDirection");

	GLint specularLightColourLocation = glGetUniformLocation(currentShaderProgam, "specularLightColour");
	GLint specularLightMaterialLocation = glGetUniformLocation(currentShaderProgam, "specularMaterialColour");
	GLint specularPowerLocation = glGetUniformLocation(currentShaderProgam, "specularPower");
	GLint cameraPositionLocation = glGetUniformLocation(currentShaderProgam, "cameraPosition");

	GLint modelLocation = glGetUniformLocation(currentShaderProgam, "Model");

	GLint texture0Location = glGetUniformLocation(currentShaderProgam, "texture0");

	if (gameObject->getDiffuseMap() > 0){
		currentDiffuseMap = gameObject->getDiffuseMap();
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, currentDiffuseMap);
	glUniform1i(texture0Location, 0);

	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVPMatrix));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(gameObject->getModelMatrix()));

	glUniform4fv(ambientLightColourLocation, 1, value_ptr(ambientLightColour));
	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(gameObject->getAmbientMaterial()));

	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(diffuseLightColour));
	glUniform4fv(diffuseLightMaterialLocation, 1, value_ptr(gameObject->getDiffuseMaterial()));
	glUniform3fv(lightDirectionLocation, 1, value_ptr(lightDirection));

	glUniform4fv(specularLightColourLocation, 1, value_ptr(specularLightColour));
	glUniform4fv(specularLightMaterialLocation, 1, value_ptr(gameObject->getSpecularMaterial()));
	glUniform1f(specularPowerLocation, gameObject->getSpecularPower());
	glUniform3fv(cameraPositionLocation, 1, value_ptr(cameraPosition));


	glBindVertexArray(gameObject->getVertexArrayObject());
	if (gameObject->getVertexArrayObject()>0)
		glDrawElements(GL_TRIANGLES, gameObject->getNumberOfIndices(), GL_UNSIGNED_INT, 0);

	for (int i = 0; i < gameObject->getNumberOfChildren(); i++)
	{
		renderGameObject(gameObject->getChild(i));
	}
}


void renderScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto iter = renderQueue.begin(); iter != renderQueue.end(); iter++)
	{
		renderGameObject((*iter));
	}

	renderQueue.clear();
}

void render()
{
	renderScene();
	//renderPostQuad();
}

int main(int argc, char * arg[])
{
	ChangeWorkingDirectory();
	//Controls the game loop
	bool run = true;

	// init everyting - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;

		return -1;
	}
	//
	int	imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int	returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)&	(imageInitFlags)) != imageInitFlags)	{

		cout << "ERROR	SDL_Image	Init	" << IMG_GetError() << endl;
	}

	if (TTF_Init() == -1)	{
		std::cout << "ERROR	TTF_Init:	" << TTF_GetError();
	}

	//Request opengl 4.1 context, Core Context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	//Create a window
	SDL_Window * window = SDL_CreateWindow(
		"SDL",             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		640,                        // width, in pixels
		480,                        // height, in pixels
		SDL_WINDOW_OPENGL           // flags
		);

	// Create an OpenGL context associated with the window.
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	//Call our InitOpenGL Function
	initOpenGL();
	//Set our viewport
	setViewport(640, 480);

	initScene();
	//Value to hold the event generated by SDL
	SDL_Event event;
	//Game Loop
	while (run)
	{
		//While we still have events in the queue
		while (SDL_PollEvent(&event)) {
			//Get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				//set our boolean which controls the loop to false
				run = false;
			}
			if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					break;
				case SDLK_RIGHT:
					break;
				case SDLK_UP:
					break;
				case SDLK_DOWN:
					break;
				default:
					break;
				}
			}
		}
		//init Scene
		update();
		//render
		render();
		//Call swap so that our GL back buffer is displayed
		SDL_GL_SwapWindow(window);

	}

	// clean up, reverse order!!!
	cleanUp();
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
