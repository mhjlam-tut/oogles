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
			"#version 450 core 													\n"
			"																	\n"
			"layout (location = 0) in vec4 offset;								\n"
			"layout (location = 1) in vec4 color;								\n"
			"																	\n"
			"out VS_TO_FS														\n"
			"{																	\n"
			"	vec4 color;														\n"
			"} vs_out;															\n"
			"																	\n"
			"void main()														\n"
			"{																	\n"
			"	const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25, 0.5, 1.0),	\n"
			"									 vec4(-0.25, -0.25, 0.5, 1.0),	\n"
			"									 vec4( 0.25,  0.25, 0.5, 1.0)); \n"
			"	gl_Position = vertices[gl_VertexID] + offset;					\n"
			"																	\n"
			"	vs_out.color = color;											\n"
			"}																	\n"
		};

		static const GLchar* fragment_shader_source[] =
		{
			"#version 450 core						\n"
			"										\n"
			"in VS_TO_FS							\n"
			"{										\n"
			"	vec4 color;							\n"
			"} fs_in;								\n"
			"										\n"
			"out vec4 color;						\n"
			"										\n"
			"void main()							\n"
			"{										\n"
			"	color = fs_in.color;				\n"
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
		const GLfloat clear_color[] = 
		{
			(float)sin(currentTime) * 0.5f + 0.5f,
			(float)cos(currentTime) * 0.5f + 0.5f,
			0.0f, 1.0f
		};

		const GLfloat triangle_color[] = 
		{
			1.0f - clear_color[0],
			1.0f - clear_color[1],
			0.0f, 1.0f
		};
		
		GLfloat triangle_offset[] =
		{
			(float)sin(currentTime) * 0.5f,
			(float)cos(currentTime) * 0.6f,
			0.0f, 0.0f
		};

		glClearBufferfv(GL_COLOR, 0, clear_color);
		glUseProgram(rendering_program);
		glVertexAttrib4fv(0, triangle_offset);
		glVertexAttrib4fv(1, triangle_color);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};

DECLARE_MAIN(application);
