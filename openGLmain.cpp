#include "openGLmain.h"







void framebuffer_size_callback (GLFWwindow* window, int width, int height)
{
    glViewport (0,0,width,height);
}

float tab[3] = {0.0f,0.0f,-3.0f};



void processInput (GLFWwindow* window)
{

    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
    if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS)
    {
        tab[2]--;
    }
    if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS)
    {
        tab[2]++;
    }
    if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS)
    {
        tab[1]++;
    }
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS)
    {
        tab[1]--;
    }



}




int main_ogl(unsigned int WIDTH, unsigned int HEIGHT, unsigned int ELEMENTS)
{
    srand(time(NULL));
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

    Shader myShader("..\\shader.vert", "..\\fragment.frag");

    unsigned int size = ELEMENTS*3;

    std::vector<GLfloat> vertices;

    for (int i =0; i<size; i++)
    {
        float a = ((rand()%20)+(-10));
        a = a/10;
        if((i+1)%3==0)
        {
            vertices.push_back(0.0f);
        } else{
            vertices.push_back(a);
        }
    }

    std::vector<GLuint> indices;
    GLuint first = 0;
    for (GLuint i =0; i<ELEMENTS; i++)
    {
        indices.push_back(i);
        if((i+1)%3==0)
        {
            indices.push_back(first);
            first+=3;
        }
        else {
            indices.push_back(i + 1);
        }
    }


    std::vector<int> range_from_center;
    for (int i =0 ;i<size;i++)
    {

        if(i%3==0)
        {
           // std::cout<<i<<std::endl;
        }
        else if((i-1)%3==0)
        {
            //std::cout<<i<<std::endl;
        }
        else if((i+1)%3==0)
        {
            range_from_center.push_back(sqrt(pow(vertices[i-2],2)+pow(vertices[i-1],2)) * 100);
        }

    }


    std::vector<int>::iterator max = std::max_element(range_from_center.begin(),range_from_center.end());
    int max_at = std::distance(range_from_center.begin(),max);
    //std::cout<<max_at;

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //bind vertex array set buffers
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLint), &indices[0], GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    //color attribute //tex
    // glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5 * sizeof(float),(void*)(3* sizeof(float)));
    //glEnableVertexAttribArray(1);

    //unbind array
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);

        //clear color buffer
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myShader.use();
        glPointSize(10.0f);
        glBindVertexArray(VAO);

        for(unsigned int i = 0 ; i<10; i++)
        {
            glDrawArrays(GL_POINTS,0,vertices.size());
            glDrawElements(GL_LINES,indices.size(),GL_UNSIGNED_INT,0);
        }

        //swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}