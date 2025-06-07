#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <stdlib>

void errorCallback(int code, const char* description)
{
	std::cout << "CODE: " << code << " ERROR: " << &description;
}

int main() {
	int windowCreateErrorCode, windowMakeContextCurErroCode;

	glfwSetErrorCallback(errorCallback);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "OpenGL Workshop", nullptr, nullptr);
	windowCreateErrorCode = glfwGetError(NULL);//using null and no const char* because usage of error callback
	if (windowCreateErrorCode != GLFW_NO_ERROR) {
		glfwTerminate();
		return windowCreateErrorCode;
	}

	glfwMakeContextCurrent(window);
	windowMakeContextCurErroCode = glfwGetError(NULL);
	//To utilize glad, we have to call the function to intialize
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Cannot initalize GLAD!\n";
		glfwTerminate();
		return windowMakeContextCurErroCode;
	}

	glViewport(0, 0, 1024, 768);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.9, 0.1, 0.9, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwPollEvents();
		glfwSwapBuffers(window); //We have to swap buffers so we don't actually have any flickering. We draw left to right, up to down, because the displaying is not instant, we may see flickering, which is why we "swap" to a back buffer so that we can make these displays instant

	}
	
	glfwTerminate(); //clean GL's resources
	return EXIT_SUCCESS;
}
