#include <gl/glew.h>
#include <gl/glut.h>
#include <stdio.h>

static void RenderSceneCB() {
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

int main(int argv, char **argc) {
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("GLEW Test");

	glutDisplayFunc(RenderSceneCB);
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	GLclampf red = 1.0f, green = 0.0f, blue = 0.0f, alpha = 0.0f;
	glClearColor(red, green, blue, alpha);
	glutMainLoop();
}