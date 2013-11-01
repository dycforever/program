#include <iostream> 

#include <GLTools.h>	// OpenGL toolkit
#include <GLShaderManager.h>

#include <GL/glut.h> 

using namespace std;

GLfloat movePointX = 0;
GLfloat movePointY = 0;

void display() 
{ 
    glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POLYGON); 
    glVertex2f(movePointX, movePointY); 
    glVertex2f(-0.5, 0.5); 
    glVertex2f( 0.5, 0.5); 
    glVertex2f( 0.5, -0.5); 
    glEnd(); 
    glFlush(); 
} 

void SetupRC()
	{
	// Black background
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f );
    
	}

void SpecialKeys(int key, int x, int y)
    {
	GLfloat stepSize = 0.1f;

	if(key == GLUT_KEY_UP)
		movePointY += stepSize;

	if(key == GLUT_KEY_DOWN)
		movePointY -= stepSize;
	
	if(key == GLUT_KEY_LEFT)
		movePointX -= stepSize;

	if(key == GLUT_KEY_RIGHT)
		movePointX += stepSize;

	// Collision detection
	if(movePointX < -1.0f) movePointX = -1.0f;
	if(movePointX > 1.0f) movePointX = 1.0f;

	if(movePointY > 1.0f) movePointY = 1.0f;
	if(movePointY < -1.0f) movePointY = -1.0f;

	glutPostRedisplay();
	}

string errorToString() {
    if (glGetError() == GL_NO_ERROR) {
        return "no error";
    }
    return "has error";
}

void ChangeSize(int w, int h)
	{
	glViewport(0, 0, w, h);
	}



int main(int argc, char** argv) 
{ 
//	gltSetWorkingDirectory(argv[0]);

    glutInit(&argc, argv); 
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
    glutCreateWindow("simple"); 

    glutDisplayFunc(display); 
    glutSpecialFunc(SpecialKeys);

    const unsigned char* oglVersion = glGetString(GL_VERSION);

    if (oglVersion == NULL) {
        cout << "get string failed:" << errorToString() << endl;
        exit(0);
    }
    std::cout << "version:" << oglVersion << " ." << std::endl;
//	glutReshapeFunc(ChangeSize);

    glutMainLoop(); 

} 