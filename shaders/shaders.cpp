#include <fstream>

#include "../utils.h"
#include "../shader.h"

int main() {
// utility variables
//---------------------------------------------------------------------------//
    GLfloat fadeSpeed = 0.0f;

// initialization
//---------------------------------------------------------------------------//
    // glfw: initialization
    initGLFW();

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw: create window, exit if fails
    GLFWwindow* window = createWindow("shaders");

    // glfw: set context and framebuffer call back
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: initialization
    initGLAD();

// shaders
//---------------------------------------------------------------------------//
    // create vertex and buffer shader
	Shader shader("vertex.glsl", "fragment.glsl");

// buffers
//---------------------------------------------------------------------------//
    // declare buffer objects and data
	GLuint VAO, VBO;
    const GLfloat z = 0.0f;

	// offset is roughly 0.52 between triangles, with some rounding
	// calculated by 2(pi) / 12, 12 being num of steps
    const GLfloat vertices[] = {
    //  positions	       | offset
    //  triangle 1         |
         0.82f, -0.20f, z,   0.00f,  // bottom
         0.82f,  0.20f, z,   0.00f,  // top right
         0.62f,  0.20f, z,   0.00f,  // top left
    //  triangle 2
         0.60f,  0.20f, z,   0.52f, // top
         0.80f, -0.20f, z,   0.52f, // bottom right
         0.60f, -0.20f, z,   0.52f, // bottom left
    //  triangle 3
         0.58f, -0.20f, z,   1.05f, // bottom right
         0.58f, -0.02f, z,   1.05f, // top right
         0.20f, -0.20f, z,   1.05f, // left
    //  triangle 4
         0.58f,  0.00f, z,   1.57f, // right
         0.20f,  0.18f, z,   1.57f, // top left
         0.20f, -0.18f, z,   1.57f, // bottom left
    //  triangle 5
         0.58f,  0.02f, z,   2.09f, // bottom right
         0.20f,  0.20f, z,   2.09f, // left
         0.58f,  0.20f, z,   2.09f, // top right
    //  triangle 6
         0.02f, -0.20f, z,   2.62f, // left
         0.18f,  0.20f, z,   2.62f, // top right
         0.18f, -0.20f, z,   2.62f, // bottom right
    //   triangle 7 (center triangle)
        -0.18f,  0.20f, z,   3.14f, // top left
         0.16f,  0.20f, z,   3.14f, // top right
         0.00f, -0.20f, z,   3.14f, //bottom
    //  triangle 8
        -0.20f,  0.20f, z,   3.66f, // top left
        -0.20f, -0.20f, z,   3.66f, // bottom left
        -0.02f, -0.20f, z,   3.66f, // right
    //  triangle 9
        -0.58f,  0.02f, z,   4.19f, // bottom left
        -0.22f,  0.20f, z,   4.19f, // right
        -0.58f,  0.20f, z,   4.19f, // top left
    //  triangle 10
        -0.58f,  0.00f, z,   4.71f, // left
        -0.22f,  0.18f, z,   4.71f, // top right
        -0.22f, -0.18f, z,   4.71f, // bottom right
    //  triangle 11
        -0.58f, -0.20f, z,   5.23f, // bottom left
        -0.58f, -0.02f, z,   5.23f, // top left
        -0.22f, -0.20f, z,   5.23f, // right
    //  triangle 12
        -0.80f, -0.20f, z,   5.76f, // left
        -0.60f, -0.20f, z,   5.76f, // bottom right
        -0.60f,  0.20f, z,   5.76f, // top right
    //  triangle 13
        -0.82f, -0.20f, z,   6.28f, // bottom left
        -0.82f,  0.20f, z,   6.28f, // top left
        -0.62f,  0.20f, z,   6.28f // right
    };



    // generate vertex arrays and buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind VAO
    glBindVertexArray(VAO);
    // bind buffer, pass in data to buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set attribute pointers
	//-----------------------------------------------------------------------//
    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT,
        GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // enable VA array

	// offset
	glVertexAttribPointer(1, 1, GL_FLOAT,
		GL_FALSE, 4 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1); // enable VA array


// rendering
//---------------------------------------------------------------------------//
    while (!glfwWindowShouldClose(window)) {
        // clear screen w/ black background each frame
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // process input
        processInput(window);

        // render logic
        //-------------------------------------------------------------------//
        // enable alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // enable the shader program
        shader.use();

        // calculate time
        const GLdouble time = glfwGetTime();

    	// set fade speed of the triangles
    	fadeSpeed = 2.0f;

    	// pass in color, time, and fadeSpeed to fragment shader
    	shader.setVec3("ourColor", 1.0f, 1.0f, 1.0f);
        shader.setFloat("uTime", time);
    	shader.setFloat("uSpeed", fadeSpeed);

    	// drawing the triangles
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 52);
        glBindVertexArray(0);

        // glfw
        //------------------------------------------------------------------//
        // check for events and swap buffers to display
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}