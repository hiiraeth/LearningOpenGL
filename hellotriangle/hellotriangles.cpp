#include "../utils.h"

int main() {
    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "out vec4 vertexColor;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
        "vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
        "}\0";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 vertexColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vertexColor;\n"
        "}\0";

    const char* fragmentShaderSource2 =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\0";

    // ---------------------------------------------------------------- INITIALIZATION //
    // init glfw
    initGLFW();

    // create window object
    GLFWwindow* window = createWindow("hello triangle");

    // make the opengl context active, init callback func
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // init glad: load all openGL func pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }

    // ----------------------------------------------------------------- VERTEX SHADER //
    // create the vertex shader
    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // attach shader source code to shader object, compile
    // arg1: shader object | arg2: # of strs passing as src code | arg3: src code
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // error checking
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // -------------------------------------------------------------- FRAGMENT SHADERS //
    //--FRAGMENT SHADER 1--//
    const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // attach src code to shader obj & compile
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // error checking
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //--FRAGMENT SHADER 2--//
    const unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    // error checking
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ---------------------------------------------------------------- SHADER PROGRAM //
    // final linked version of multiple shaders, have to link to shader program and then
    // activate the shader program while rendering objects. linker errors will appear if
    // inputs and outputs between the shaders do not match

    // creates a program, returns ID ref to the program object
    const unsigned int shaderProgram = glCreateProgram();

    // attach compiled shaders to the program object and link
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // error checking
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    const unsigned int shaderProgram2 = glCreateProgram();

    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    // error checking
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete shaders once linked, no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ----------------------------------------------------------------------- BUFFERS //
    // set up vertex data and buffers, config vertex attributes
    // triangle
    float firstTriangle[] = {
        -1.0f, -0.5f, 0.0f, // bottom left
         0.0f, -0.5f, 0.0f, // bottom right
        -0.5f,  0.5f, 0.0f  // top
    };
    float secondTriangle[] = {
         0.0f, -0.5f, 0.0f, // bottom left
         1.0f, -0.5f, 0.0f, // bottom right
         0.5f,  0.5f, 0.0f  // top
    };

    // set up VAOs and VBOs
    unsigned int VAOs[2], VBOs[2];

    // VAOs store: calls to glEnable/DisableVertexAttribArray, and attr. configs and VBOs
    // associated w/ vertex attr by calls to glVertexAttribPointer
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

//---first triangle---//
    // bind VAO first, then bind and set vertex buffers, then config vertex attrib
    glBindVertexArray(VAOs[0]);

    // copy vertices array in buffer for openGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

//---second triangle---//
    // bind VAO for 2nd triangle
    glBindVertexArray(VAOs[1]);

    // copy vertices array into 2nd VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)

    // polygon/wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // --------------------------------------------------------------------- RENDERING //
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // rendering logic
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the triangles! use the shader program, bind the vertex array object, draw the arrays
        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // arg 1: primitive type to draw | arg2: starting index of vertex array | arg3: how many vertices to draw

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);

        // glfw: check/call events, swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // de-allocate resources
    glDeleteVertexArrays(1, &VAOs[0]);
    glDeleteBuffers(1, &VBOs[0]);;
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}