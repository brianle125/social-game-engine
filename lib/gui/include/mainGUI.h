#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600


static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
float* makeQuad(float x, float y, float h, float w);