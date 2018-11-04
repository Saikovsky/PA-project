#include "openGLmain.h"

void framebuffer_size_callback (GLFWwindow* window, int width, int height)
{
    glViewport (0,0,width,height);
}

void processInput (GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}


int main_ogl(unsigned int WIDTH, unsigned int HEIGHT)
{
//    const char *vertex_path = "..\\shader.vert";
//    const char *fragment_path = "..\\fragment.frag";
//    std::string vertString = loadShader(vertex_path);
//    std::string fragString = loadShader(fragment_path);
//    const char *vertexShaderSource = vertString.c_str();
//    const char *fragmentShaderSource = fragString.c_str();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window =glfwCreateWindow(WIDTH,HEIGHT,"LearnOpenGL",NULL, NULL);
    if(window==NULL)
    {
        std::cout<<"Failed to create window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"Failed to initialize GLAD"<<std::endl;
        return -1;
    }

    //unsigned int shaderProgram_final = shaderProgram(vertexShaderSource, fragmentShaderSource);

    Shader myShader("..\\shader.vert", "..\\fragment.frag");

    float vertices[] = {
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, .5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    //bind vertex array set buffers
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    //unbind array
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);

        //clear color buffer
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //activating shader and drawing triangles
        myShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}