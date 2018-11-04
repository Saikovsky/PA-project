#include "shader_loader.h"


std::string loadShader (const char *filePath)
{
    std::string content;
    std::ifstream fileStream(filePath,std::ios::in);

    if(!fileStream.is_open())
    {
        std::cerr << "Could not read file "<<filePath<<" Jeb sie na ryj"<<std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line+"\n");
    }

    fileStream.close();
    return content;
}

unsigned int shaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource (vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];


    glGetShaderiv(vertexShader, GL_COMPILE_STATUS,&success);
    if(!success)
    {
    glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
    std::cout<<"Vertex Shader ERROR"<<infoLog<<std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
    glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
    std::cout<<"Fragment Shader Error"<<infoLog<<std::endl;
    }


    unsigned int _shaderProgram;
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram,vertexShader);
    glAttachShader(_shaderProgram,fragmentShader);
    glLinkProgram(_shaderProgram);


    glGetProgramiv(_shaderProgram,GL_LINK_STATUS,&success);
    if(!success)
    {
    glGetProgramInfoLog(_shaderProgram,512,NULL,infoLog);
    std::cout<<"Shader Program ERROR"<<infoLog<<std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return _shaderProgram;
}
