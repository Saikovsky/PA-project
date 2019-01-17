#include "openGLmain.h"
#include <cmath>

void framebuffer_size_callback (GLFWwindow* window, int width, int height);


void processInput (GLFWwindow* window, std::vector<float>&vertices);

int the_code(std::vector<float>&vertices);

int main_ogl(unsigned int WIDTH, unsigned int HEIGHT, unsigned int ELEMENTS)
{
    const int cWIDTH = WIDTH;
    const int cHEIGHT = HEIGHT;
    srand(time(NULL));
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =glfwCreateWindow(cWIDTH,cHEIGHT,"DOTS AND LINES",NULL, NULL);
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

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    path_algorithm(ELEMENTS,vertices,indices);

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
    int expecto_patronum = the_code(vertices);
    while(!glfwWindowShouldClose(window))
    {
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

        //input
        processInput(window, vertices);

        //clear color buffer
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        myShader.use();
        glPointSize(0.0f);
        glBindVertexArray(VAO);

        glDrawArrays(GL_POINTS,0,vertices.size()/3);
        glDrawElements(GL_LINES,indices.size(),GL_UNSIGNED_INT,0);


        //swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    return expecto_patronum;
}

void framebuffer_size_callback (GLFWwindow* window, int width, int height)
{
    glViewport (0,0,width,height);
}

void processInput (GLFWwindow* window, std::vector<float>&vertices)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
    glfwSetWindowShouldClose(window,true);
    else if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS)
    {
        //
    }
}

int the_code(std::vector<float>&vertices)
{
    float a,b,c,p, _P, sum;
    sum = 0;
    int mod = vertices.size()%3;
    int real_size = vertices.size()-mod;
    //std::cout<<real_size<<std::endl;
    for(int i = 0;i<real_size;i=i+9)
    {
        a = sqrt(pow((vertices[i]-vertices[i+3]),2)+pow((vertices[i+1]-vertices[i+4]),2));
        b = sqrt(pow((vertices[i+3]-vertices[i+6]),2)+pow((vertices[i+4]-vertices[i+7]),2));
        c = sqrt(pow((vertices[i+6]-vertices[i]),2)+pow((vertices[i+7]-vertices[i+1]),2));
        p=(a+b+c)/2;

        _P = sqrt(p*(p-a)*(p-b)*(p-c));
        //std::cout<<a<<" "<<b<<" "<<c<<" "<<p<<" "<<_P<<" "<<"\n";
        sum+=_P;
    }
    sum=sum*1000000;
    float final_number = static_cast<float>(sum);
    //std::cout<<final_number;
    return final_number;
}