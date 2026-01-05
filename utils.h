#ifndef LEARNOPENGL_UTILS_H
#define LEARNOPENGL_UTILS_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

inline unsigned int WINDOW_WIDTH = 800;
inline unsigned int WINDOW_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void initGLFW();
void initGLAD();

GLFWwindow* createWindow(char* title);
void checkForErrors(GLuint shader, std::string type);

#endif //LEARNOPENGL_UTILS_H