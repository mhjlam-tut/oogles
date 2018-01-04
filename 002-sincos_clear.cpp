#include "sb7.h"
#include <cmath>

class application : public sb7::application
{
public:
	void render(double currentTime)
	{
		const GLfloat color[] =
		{
			(GLfloat) sin(currentTime) * 0.5f + 0.5f, 
			(GLfloat) cos(currentTime) * 0.5f + 0.5f, 
			0.0f, 1.0f
		};
		
		glClearBufferfv(GL_COLOR, 0, color);
	}
};

DECLARE_MAIN(application);
