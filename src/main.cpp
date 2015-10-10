#include "Common.h"
#include "Graphics.h"
#include "Vertices.h"
#include "Shader.h"
#include "Texture.h"

Vertex verts[] = {
	//Front
	{ vec3(-0.5f, 0.5f, 0.5f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f) },// Top Left

	{ vec3(-0.5f, -0.5f, 0.5f),
	vec4(1.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f) },// Bottom Left

	{ vec3(0.5f, -0.5f, 0.5f),
	vec4(0.0f, 1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f) }, //Bottom Right

	{ vec3(0.5f, 0.5f, 0.5f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f) },// Top Right


	//back
	{ vec3(-0.5f, 0.5f, -0.5f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f) },// Top Left

	{ vec3(-0.5f, -0.5f, -0.5f),
	vec4(1.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f) },// Bottom Left

	{ vec3(0.5f, -0.5f, -0.5f),
	vec4(0.0f, 1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f) }, //Bottom Right

	{ vec3(0.5f, 0.5f, -0.5f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f) },// Top Right

};

GLuint indices[] = {
	//front
	0, 1, 2,
	0, 3, 2,

	//left
	4, 5, 1,
	4, 1, 0,

	//right
	3, 7, 2,
	7, 6, 2,

	//bottom
	1, 5, 2,
	6, 2, 5,

	//top
	4, 0, 7,
	0, 7, 3,

	//back
	4, 5, 6,
	4, 7, 6
};

//matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;
mat4 MVPMatrix;

mat4 UIProjMatrix;
mat4 UIWorldMatrix;
mat4 UIMVPMatrix;

GLuint VBO;
GLuint EBO;
GLuint VAO;
GLuint shaderProgram;

GLuint UIVBO;
GLuint UIEBO;
GLuint UIVAO;
GLuint UIShaderProgram;


GLuint diffuseMap;
GLuint fontTextureMap;

vec4 fontColour=vec4(1.0f,1.0f,1.0f,1.0f);

void initUIScene()
{
	string fontPath =ASSET_PATH+FONT_PATH+"/OratorStd.otf";
	fontTextureMap=loadTextureFromFont(fontPath,20,"Hello");
	glBindTexture(GL_TEXTURE_2D,fontTextureMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	int width, height;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT,&height);

	Vertex spriteData[] = {
		{ vec3(0.0, 0.0f, 0.0f), vec4(1.0f,1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f) },// Top Left

		{ vec3(0.0f, height, 0.0f),vec4(1.0f, 1.0f, 1.0f, 1.0f),vec2(0.0f, 1.0f) },//Bottom Left

		{ vec3(width, height, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f) },//Bottom Right

		{ vec3(width, 0.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f) }//Top Right

	};

	GLuint spriteIndices[]={ 0,1,2, 0,3,2, };

	glGenVertexArrays(1, &UIVAO);
	glBindVertexArray(UIVAO);
	glGenBuffers(1, &UIVBO);
	glBindBuffer(GL_ARRAY_BUFFER, UIVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), spriteData, GL_STATIC_DRAW);

	//create buffer
	glGenBuffers(1, &UIEBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UIEBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), spriteIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec4) + sizeof(vec3)));

	GLuint vertexShaderProgram = 0;
	string vsPath = ASSET_PATH + SHADER_PATH + "/UIVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	checkForCompilerErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	string fsPath = ASSET_PATH + SHADER_PATH + "/UIFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
	checkForCompilerErrors(fragmentShaderProgram);

	UIShaderProgram = glCreateProgram();
	glAttachShader(UIShaderProgram, vertexShaderProgram);
	glAttachShader(UIShaderProgram, fragmentShaderProgram);

	//Link attributes
	glBindAttribLocation(UIShaderProgram, 0, "vertexPosition");
	glBindAttribLocation(UIShaderProgram, 1, "vertexColour");
	glBindAttribLocation(UIShaderProgram, 2, "vertexTexCoords");

	glLinkProgram(UIShaderProgram);
	checkForLinkErrors(UIShaderProgram);
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

}

void initScene()
{
	initUIScene();

	//load texture & bind
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	diffuseMap = loadTextureFromFile(texturePath);

	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Generate Vertex Array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	//create buffer
	glGenBuffers(1, &EBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec4)));

	GLuint vertexShaderProgram = 0;
	string vsPath = ASSET_PATH + SHADER_PATH + "/textureVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	checkForCompilerErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	string fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
	checkForCompilerErrors(fragmentShaderProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);

	//Link attributes
	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
	glBindAttribLocation(shaderProgram, 1, "vertexColour");
	glBindAttribLocation(shaderProgram, 2, "vertexTexCoords");

	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}

void cleanUPUI()
{
	glDeleteTextures(1,&fontTextureMap);
	glDeleteProgram(UIShaderProgram);
	glDeleteBuffers(1, &UIEBO);
	glDeleteBuffers(1, &UIVBO);
	glDeleteVertexArrays(1, &UIVAO);
}

void cleanUp()
{
	cleanUPUI();
	glDeleteTextures(1, &diffuseMap);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void update()
{
	projMatrix = perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

	viewMatrix = lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	worldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));

	MVPMatrix = projMatrix*viewMatrix*worldMatrix;

	UIProjMatrix=ortho(0.0f, 640.0f,480.0f,0.0f, 0.1f, 100.0f);
	UIWorldMatrix=translate(mat4(1.0f), vec3(100.0f, 100.0f, 0.0f));;

	UIMVPMatrix=UIProjMatrix*viewMatrix*UIWorldMatrix;
}

void renderUI()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(UIShaderProgram);

	GLint MVPLocation = glGetUniformLocation(UIShaderProgram, "MVP");
	GLint texture0Location = glGetUniformLocation(UIShaderProgram, "texture0");
	GLint colourLocation=glGetUniformLocation(UIShaderProgram, "textColour");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fontTextureMap);

	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(UIMVPMatrix));
	glUniform4fv(colourLocation,1,glm::value_ptr(fontColour));
	glUniform1i(texture0Location, 0);

	glBindVertexArray(UIVAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisable(GL_BLEND);
}

void render3D()
{
	glUseProgram(shaderProgram);

	GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	GLint texture0Location = glGetUniformLocation(shaderProgram, "texture0");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
	glUniform1i(texture0Location, 0);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void render()
{
	//old imediate mode!
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	render3D();
	renderUI();
}

int main(int argc, char * arg[])
{

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
