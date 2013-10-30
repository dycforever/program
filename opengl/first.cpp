#include <iostream> 

#include <GL/glut.h> 

void display() 
{ 
    glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POLYGON); 
    glVertex2f(-0.5, -0.5); 
    glVertex2f(-0.5, 0.5); 
    glVertex2f( 0.5, 0.5); 
    glVertex2f( 0.5, -0.5); 
    glEnd(); 
    glFlush(); 
} 

using namespace std;

string errorToString() {
    if (glGetError() == GL_NO_ERROR) {
        return "no error";
    }
    return "has error";
}

int main(int argc, char** argv) 
{ 
    glutInit(&argc, argv); 
    glutCreateWindow("simple"); 
    glutDisplayFunc(display); 

    const unsigned char* oglVersion = glGetString(GL_VERSION);

    if (oglVersion == NULL) {
        cout << "get string failed:" << errorToString() << endl;
        exit(0);
    }
    std::cout << "version:" << oglVersion << " ." << std::endl;

    glutMainLoop(); 

} 