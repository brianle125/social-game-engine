// sudo apt-get install libglfw3-dev
// sudo apt install libglm-dev
// sudo apt-get install libglew-dev

// g++ lib/gui/mainGUI.cpp -lglfw -lGL

// window initialization code based off of: https://www.glfw.org/documentation.html
// https://www.glfw.org/docs/3.3/quick.html#quick_key_input
// input learned from: https://www.glfw.org/docs/3.3/input_guide.html



#include "include/mainGUI.h"

int main()
{
	// Initialize GLFW
	if ( !glfwInit( ) )
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Social Gaming - Injera", NULL, NULL);

	glfwMakeContextCurrent(window);

    // esc to close the window
    glfwSetKeyCallback(window, key_callback);

    //create shape

	GLint vertices[] =
	{
		-10, -10, 0, // Lower left corner
		10, -10, 0, // Lower right corner
		10, 10, 0, // Upper corner right
        -10, 10, 0 // upper left

	};

    GLfloat vertices2[] =
	{
		0.0f, 0.0f, 0.0f, // Lower left corner
		0.8f, 0.0f, 0.0f, // Lower right corner
		0.8f, 0.8f, 0.0f, // Upper right corner
        0.0f, 0.8f, 0.0f  // upper left corner

	};

    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
        // get changing window size
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // bg colour
        glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.55f, 0.65f, 0.74f, 1.0f);

        // draw a quad
        glEnableClientState(GL_VERTEX_ARRAY); 
        glVertexPointer(3, GL_FLOAT, 0, vertices2); 
        glDrawArrays(GL_QUADS, 0, 4); 
        glDisableClientState(GL_VERTEX_ARRAY); 
        
        glfwSwapBuffers(window);
        glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        std::cout << (char)key << std::endl;
        if(key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

float* makeQuad(float x, float y, float h, float w) 
{
    float vertices[] = {
        x, y, 0.0f, // Lower left corner
		(x + w), y, 0.0f, // Lower right corner
		(x + w), (y + h), 0.0f, // Upper right
        x, (y + h), 0.0f // lower left
    };
    return vertices;
}
