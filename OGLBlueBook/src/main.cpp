#include <gl/glew.h>
#include <gl/glut.h>
#include <stdio.h>


int main(int argv, char **argc) {
	glutInit(&argv, argc);
	glutCreateWindow("GLEW Test");
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 0.0f, };

	while (1) {
		glClearBufferfv(GL_COLOR, 0, red);
	}
}