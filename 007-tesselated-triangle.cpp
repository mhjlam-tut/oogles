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
			"#version 450 core 													\n"
			"																	\n"
			"void main()														\n"
			"{																	\n"
			"	const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),	\n"
			"								   vec4(-0.25, -0.25, 0.5, 1.0),	\n"
			"								   vec4( 0.25,  0.25, 0.5, 1.0)); 	\n"
			"																	\n"
			"	gl_Position = vertices[gl_VertexID];							\n"
			"}																	\n"
		};

		static const GLchar* tcs_source[] = // tesselation control shader
		{
			"#version 450 core													\n"
			"																	\n"
			"layout (vertices = 3) out;											\n"
			"																	\n"
			"void main()														\n"
			"{																	\n"
			"	if (gl_InvocationID == 0)										\n"
			"	{																\n"
			"		gl_TessLevelInner[0] = 5.0;									\n"
			"		gl_TessLevelOuter[0] = 5.0;									\n"
			"		gl_TessLevelOuter[1] = 5.0;									\n"
			"		gl_TessLevelOuter[2] = 5.0;									\n"
			"	}																\n"
			"																	\n"
			"	gl_out[gl_InvocationID].gl_Position = 							\n"
			"		gl_in[gl_InvocationID].gl_Position;							\n"
			"}																	\n"
		};

		static const GLchar* tes_source[] = // tesselation evaluation shader
		{
			"#version 450 core													\n"
			"																	\n"
			"layout (triangles, equal_spacing, cw) in;							\n"
			"																	\n"
			"void main()														\n"
			"{																	\n"
			"	gl_Position =	(gl_TessCoord.x * gl_in[0].gl_Position) +		\n"
			"					(gl_TessCoord.y * gl_in[1].gl_Position) +		\n"
			"					(gl_TessCoord.z * gl_in[2].gl_Position);		\n"
			"}																	\n"
		};

		static const GLchar* fs_source[] = // fragment shader
		{
			"#version 450 core													\n"
			"																	\n"
			"out vec4 color;													\n"
			"																	\n"
			"void main()														\n"
			"{																	\n"
			"	color = vec4(1, 1, 1, 1);										\n"
			"}																	\n"
		};

		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, vs_source, NULL);
		glCompileShader(vs);

		GLuint tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(tcs, 1, tcs_source, NULL);
		glCompileShader(tcs);

		GLuint tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(tes, 1, tes_source, NULL);
		glCompileShader(tes);

		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, fs_source, NULL);
		glCompileShader(fs);

		program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, tcs);
		glAttachShader(program, tes);
		glAttachShader(program, fs);

		glLinkProgram(program);

		glDeleteShader(vs);
		glDeleteShader(tcs);
		glDeleteShader(tes);
		glDeleteShader(fs);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void render(double currentTime)
	{
		const GLfloat clear_color[] = { 0.25f, 0.25f, 0.25f, 1.00f };
		glClearBufferfv(GL_COLOR, 0, clear_color);

		glUseProgram(program);
		glPatchParameteri(GL_PATCH_VERTICES, 3); // default behavior, can be omitted
		glDrawArrays(GL_PATCHES, 0, 3);
	}

	void shutdown()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteProgram(program);
	}
};

DECLARE_MAIN(application);
