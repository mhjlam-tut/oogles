#include "include/sb7.h"
#include <cmath>

class application : public sb7::application
{
private:
	GLuint rendering_program;
	GLuint vertex_array_object;

public:
	GLuint compile_shaders()
	{
		static const GLchar* vertex_shader_source[] = 
		{
			"#version 450 core 						\n"
			"										\n"
			"void main()							\n"
			"{										\n"
			"	gl_Position = vec4(0,0,0.5,1);		\n"
			"}										\n"
		};

		static const GLchar* fragment_shader_source[] =
		{
			"#version 450 core						\n"
			"										\n"
			"out vec4 color;						\n"
			"										\n"
			"void main()							\n"
			"{										\n"
			"	color = vec4(1,1,1,1);				\n"
			"}										\n"
		};

		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}

	void startup()
	{
		rendering_program = compile_shaders();
		glCreateVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
	}

	void shutdown()
	{
		glDeleteProgram(rendering_program);
		glDeleteVertexArrays(1, &vertex_array_object);
	}

	void render(double currentTime)
	{
		const GLfloat color[] =
		{
			(GLfloat) sin(currentTime) * 0.5f + 0.5f, 
			(GLfloat) cos(currentTime) * 0.5f + 0.5f, 
			0.0f, 1.0f
		};

		glClearBufferfv(GL_COLOR, 0, color);

		glPointSize(40.0f);

		glUseProgram(rendering_program);
		glDrawArrays(GL_POINTS, 0, 1);
	}
};

DECLARE_MAIN(application);
