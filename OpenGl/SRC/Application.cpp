#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
//#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"






/*static ShaderProgramSourse ParseShader(const std::string& filepath) {

    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };



    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream,line))
    {
        if (line.find("shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos ){
               type= ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
           
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return{ ss[0].str(),ss[1].str() };
}



static unsigned int CompileShaders(unsigned int type,const std::string& source ) {

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result==GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed To Compile "<<(type == GL_VERTEX_SHADER ? "Vertex":"Fragment")<<" Shader -- " << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader,const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShaders(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShaders(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}*/

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit()==GLEW_OK)
    {
        std::cout <<"info - GL VERSION - " << glGetString(GL_VERSION) << std::endl;
    }
    {
        float positions[] = {
        -0.5f,-0.5f,
        0.50f,-0.5f,
        0.5f,0.5f,
        -0.5f,0.5f
        };

        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };

        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));


        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb,layout);

        IndexBuffer ib(indices, 6);

        /* unsigned int buffer;
         GLCall (glGenBuffers(1, &buffer));
         GLCall (glBindBuffer(GL_ARRAY_BUFFER,buffer));
         GLCall (glBufferData(GL_ARRAY_BUFFER, 4 *2* sizeof(float), positions, GL_STATIC_DRAW));*/

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
       
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.UnBind();


        Renderer renderer;

       /* GLCall(int location = glGetUniformLocation(shader, "u_Color"));*/

        float r = 0.5f;
        float increment = 0.01f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            //  GLCall(glUseProgram(shader)); glDrawArrays(GL_TRIANGLES,0, 3);
            shader.Bind();
           shader.SetUniform4f("u_Color",r, 0.3f, 0.8f, 1.0f);
           renderer.Draw(va,ib,shader);

            if (r > 1.0f)
            {
                increment = -0.01f;
            }
            else if (r < 0.1f) {
                increment = 0.01f;
            }
            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        

    }
    glfwTerminate();
    return 0;
}