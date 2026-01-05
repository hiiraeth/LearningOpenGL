#include "shader.h"
#include "utils.h"
#include "stb_image.h"

int main() {
// initialization
//---------------------------------------------------------------------------//
	// glfw: init
	initGLFW();
	// create window
	GLFWwindow* window = createWindow("textures");
	// set context, fb size cb
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glad: init
	initGLAD();

// shaders
//---------------------------------------------------------------------------//
	// create shader
	Shader shader = Shader("vertex.glsl", "fragment.glsl");

// buffers
//---------------------------------------------------------------------------//
	// declare VAO, VBO, and data
	GLuint VAO, VBO;
	GLfloat z = 0.0f;

	GLfloat vertices[] = {
	  // positions		   colors
		 0.5f, -0.5f, z,   1.0f, 0.0f, 0.0f, // bottom right
		-0.5f, -0.5f, z,   0.0f, 1.0f, 0.0f, // bottom left
		 0.0f,  0.5f, z,   0.0f, 0.0f, 1.0f  // top
	};

	// set up VAO and buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// copy in data to buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set vertex attribute pointers
	//-----------------------------------------------------------------------//
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT,
		GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, 3, GL_FLOAT,
		GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

// loading texture
//---------------------------------------------------------------------------//

	// gen texture in openGL
	GLuint texture;
	glGenTextures(1, &texture);

	// bind texture to state
	glBindTexture(GL_TEXTURE_2D, texture);

	// set texture parameters
	//-----------------------------------------------------------------------//
	// sets wrap to repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// sets mag and min to linear interpolation
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load texture into program
	int width, height, nrChannels;
	unsigned char* data = stbi_load("../texturefiles/container.jpg",
		&width, &height, &nrChannels, 0);

	// copy data into texture
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture!" << std::endl;
	}

	// free image memory
	stbi_image_free(data);

// rendering logic
//---------------------------------------------------------------------------//
	while (!glfwWindowShouldClose(window)) {
		// set screen color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// process input from user
		processInput(window);

		// enable shader
		shader.use();

		// draw the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// glfw: poll events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}