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
    glEnable(GL_DEPTH_TEST);

    Shader myShader("..\\shader.vert", "..\\fragment.frag");

//    float vertices[] =  {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//                         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//                         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//                         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//                         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//                         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//                         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//                         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//                         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//                         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//                         -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//                         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//                         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//                         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//                         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//                         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//                         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//                         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//                         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//                         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//                         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//                         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//                         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//                         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//                         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//                         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//                         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//                         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//                         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//                         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//                         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//                         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//                         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//                         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//                         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//                         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    unsigned int size = ELEMENTS;
    srand(time(NULL));
    glm::vec3 * cubePositions = new glm::vec3 [size];
    for (unsigned int i = 0; i<ELEMENTS; i++)
    {
        float x = (rand()%18) + (-9);
        float y = (rand()%20) + (-10);
        float z = (rand()%20) + (-10);
        x=x/10; y=y/10; z=z/10;
      //  std::cout<<x<<" "<<y<<" "<<z<<std::endl;
        cubePositions[i] = glm::vec3(x,y,0.0f);
    }
//    float vertices1[]=
//            {
//                    0.0f, 0.0f, 0.0f,
//                    0.5f, 1.0f, 0.0f,
//            };
        float vertices1[6];
    for (int i =0; i<6; i++)
    {
        float a = ((rand()%18)+(-9));
        a = a/10;
        if((i+1)%3==0)
        {

            vertices1[i]=0.0f;
        } else{

            vertices1[i] = a;
        }
        std::cout<<vertices1[i]<<std::endl;

    }


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //bind vertex array set buffers
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
   //position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //color attribute //tex
   // glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5 * sizeof(float),(void*)(3* sizeof(float)));
    //glEnableVertexAttribArray(1);
//    //tex coords
//    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)(6* sizeof(float)));
//    glEnableVertexAttribArray(2);
    //unbind array
    glBindVertexArray(0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);


    int width_w, height_h, nrChannels;
    unsigned char *data = stbi_load("..\\container.jpg", &width_w, &height_h, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_w, height_h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout<<"FAILED TO LOAD TEX"<<std::endl;
    }
    stbi_image_free(data);


    while(!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);

        //clear color buffer
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glActiveTexture(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, texture);
        myShader.use();

        glm::mat4 view = glm::mat4(1.0f);
        view  = glm::translate(view, glm::vec3(tab[0], tab[1], tab[2]));

        glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
//        model = glm::rotate(model, (float)glfwGetTime()*glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        myShader.setMat4("view",view);
        myShader.setMat4("projection",projection);

        glBindVertexArray(VAO);

        for(unsigned int i = 0 ; i<ELEMENTS; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            //float angle = 20.0f * i;
            //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f,0.3f,0.5f));
            myShader.setMat4("model",model);

            //glDrawArrays(GL_TRIANGLES, 0, 36);
            //glLineWidth(10.0f);
            glPointSize(10.0f);
            //glDrawArrays(GL_LINES,0,2);
            glDrawArrays(GL_POINTS,0,3);
           // glDrawArrays(GL_LINES,0,3);
        }

        //swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    delete [] cubePositions;

    return 0;
}