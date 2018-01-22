#include "include/sb7.h"
#include <cmath>

class application : public sb7::application
{
private:
    GLuint program;
    GLuint vao;

public:
    void startup()
    {
        static const GLchar* vs_source[] = // vertex shader
        {
            "#version 450 core                                                  \n"
            "                                                                   \n"
            "out vec4 vs_color;                                                 \n"
            "                                                                   \n"
            "void main()                                                        \n"
            "{                                                                  \n"
            "   const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
            "                                    vec4(-0.25, -0.25, 0.5, 1.0),  \n"
            "                                    vec4( 0.25,  0.25, 0.5, 1.0)); \n"
            "   const vec4 colors[3] = vec4[3](vec4(1.0, 0.0, 0.0, 1.0),        \n"
            "                                  vec4(0.0, 1.0, 0.0, 1.0),        \n"
            "                                  vec4(0.0, 0.0, 1.0, 1.0));       \n"
            "                                                                   \n"
            "   gl_Position = vertices[gl_VertexID];                            \n"
            "   vs_color = colors[gl_VertexID];                                 \n"
            "}                                                                  \n"
        };

        static const GLchar* fs_source[] = // fragment shader
        {
            "#version 450 core                                                  \n"
            "                                                                   \n"
            "in vec4 vs_color;                                                  \n"
            "out vec4 color;                                                    \n"
            "                                                                   \n"
            "void main()                                                        \n"
            "{                                                                  \n"
            "   color = vs_color;                                               \n"
            "}                                                                  \n"
        };

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, vs_source, NULL);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, fs_source, NULL);
        glCompileShader(fs);

        program = glCreateProgram();
        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }

    void render(double currentTime)
    {
        const GLfloat clear_color[] = { 0.25f, 0.25f, 0.25f, 1.00f };
        glClearBufferfv(GL_COLOR, 0, clear_color);

        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void shutdown()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(program);
    }
};

DECLARE_MAIN(application);
