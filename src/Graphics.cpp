#include "Graphics.h"
#include "Vertices.h"

//Function to initialise OpenGL
void initOpenGL()
{
    //Smooth shading
    glShadeModel( GL_SMOOTH );

    //clear the background to black
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    //Clear the depth buffer
    glClearDepth( 1.0f );

    //Enable depth testing
    glEnable( GL_DEPTH_TEST );

    //The depth test to go
    glDepthFunc( GL_LEQUAL );

    //Turn on best perspective correction
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

//Function to set/reset viewport
void setViewport( int width, int height )
{
    //screen ration
    GLfloat ratio;

    //make sure height is always above 1
    if ( height == 0 ) {
        height = 1;
    }

    //calculate screen ration
    ratio = ( GLfloat )width / ( GLfloat )height;

    //Setup viewport
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

    //Change to poject matrix mode
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    //Calculate perspective matrix, using glu library functions
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    //Swith to ModelView
    glMatrixMode( GL_MODELVIEW );

    //Reset using the Indentity Matrix
    glLoadIdentity( );
}

GLuint createAndFillBuffer(Vertex *pVerts, int count)
{
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), pVerts, GL_STATIC_DRAW);

  return VBO;
}
