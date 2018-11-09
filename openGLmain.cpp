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


    std::vector<GLfloat> range_from_center;
    for (GLint i =0 ;i<size;i++)
    {
        if((i+1)%3==0)
        {
            range_from_center.push_back(sqrt(pow(vertices[i-2],2)+pow(vertices[i-1],2)));
        }

    }


    std::vector<GLfloat>::iterator max = std::max_element(range_from_center.begin(),range_from_center.end());
    GLint max_at = std::distance(range_from_center.begin(),max);

    GLint tab = max_at*3;
    std::vector<GLfloat> point;
    for(GLint i =tab;i<tab+3;i++)
    {
        point.push_back(vertices[i]);

    }
    std::vector<GLfloat> range_from_point;
    for (GLint i =0 ;i<size;i++)
    {
        if((i+1)%3==0)
        {
            range_from_point.push_back(sqrt(pow(vertices[i-2]-point[0],2)+pow(vertices[i-1]-point[1],2)));
        }

    }
    std::vector<GLfloat>::iterator maxx = std::min_element(range_from_point.begin(),range_from_point.end());
    GLint max_att = std::distance(range_from_point.begin(),maxx);
    std::cout<<*maxx;

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
    //position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);

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

        glDrawArrays(GL_POINTS,0,vertices.size());
        glDrawElements(GL_LINES,indices.size(),GL_UNSIGNED_INT,0);


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