// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

float xTriangulo = 0.0f;
float yTriangulo = 0.0f;

float velocidad = 0.05f;

void dibujarTraingulo(){
	glPushMatrix();
	glTranslatef(xTriangulo, yTriangulo, 0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0.2, 0);
	glVertex3f(0.2, -0.2, 0);
	glVertex3f(-0.2, -0.2, 0);
	glEnd();
	glPopMatrix();
}

void dibujar() {
	dibujarTraingulo();
}

void actualizar() {

}

void teclado_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		xTriangulo += velocidad;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		xTriangulo -= velocidad;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		yTriangulo += velocidad;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		yTriangulo -= velocidad;
	}
}

int main()
{
	//Declaramos apuntador de ventana
	GLFWwindow *window;

	//si no se pudo inicializar glfw terminamos ejecución
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//si se pudo iniciar GLFW entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//si no podemos iniciar la ventana entonces terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//establecemos el contexto
	glfwMakeContextCurrent(window);

	//UNa vez establecido el contexto activamos funciones modernas (CPU/GPU)
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	glfwSetKeyCallback(window, teclado_callback);

	//Cilco de dibijo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Esctablece el color de borrado
		glClearColor(0.25, 0, 0.3, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

