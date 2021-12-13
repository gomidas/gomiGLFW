#include "MyGeometry.h"

void GeometryObject::AddAnimation(float sequencetime, GeometryAnimation::AnimAttribute attribute, string name)
{
	Animations.push_back(new GeometryAnimation(sequencetime, attribute, name));
	cout << "Added one animation to " << this->Name << "\n";

};
void GeometryObject::DeleteAnimation(string name)
{
	auto anims = Animations.begin();


	for (int i = 0; i < Animations.size(); i++)
	{
		advance(anims, i);
		GeometryAnimation* ga = dynamic_cast<GeometryAnimation*>(*anims);
		if (ga->Name == name)
		{
			Animations.remove(ga);
		}
	}

};
void GeometryObject::DeleteAllAnimations()
{
	auto anims = Animations.begin();

	for (int i = 0; i < Animations.size(); i++)
	{
		advance(anims, i);
		GeometryAnimation* ga = dynamic_cast<GeometryAnimation*>(*anims);
		Animations.remove(ga);
	}
};
GeometryObject::~GeometryObject() {
	//FREE OTHER RESOURCES
	auto anims = Animations.begin();
	for (int i = 0; i < Animations.size(); i++)
	{
		advance(anims, i);
		dynamic_cast<GeometryAnimation*>(*anims)->~GeometryAnimation();
	}
}

void Circle::Render(GLFWwindow* window) {

	glfwGetFramebufferSize(window, &fb_W, &fb_H);
	glUseProgram(0);
	float ratio;

	ratio = fb_W / (float)fb_H;
	glViewport(0, 0, fb_W, fb_H);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glOrtho(0, fb_W, 0, 0, fb_H, 1);
	glMatrixMode(GL_MODELVIEW);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glColor3f(Color.r, Color.g, Color.b);

	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float degInRad = i + DEG2RAD;
		glVertex2f(cos(degInRad) / ratio * (Radius), sin(degInRad) * (Radius));

	}
	glEnd();

	if (BorderThickness != 0.0f)
	{
		glColor3f(BorderColor.r, BorderColor.g, BorderColor.b);
		glLineWidth(BorderThickness);
		glBegin(GL_LINE_STRIP);

		for (int i = 0; i <= 360; i++)
		{
			float degInRad =  (i)*DEG2RAD;
	
			glVertex2f(cos(degInRad) / ratio * (Radius), sin(degInRad) * (Radius));

		}
	}
	glEnd();
}
void Rectangle::Render(GLFWwindow* window) {

	glfwGetFramebufferSize(window, &fb_W, &fb_H);

	//glUseProgram(0);

	float ratio;
	mat4x4 m, p, mvp;

	ratio = fb_W / (float)fb_H;

	glViewport(0, 0, fb_W, fb_H);

	mat4x4_identity(m);
	mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	mat4x4_mul(mvp, p, m);

	glDisable(GL_TEXTURE_2D);

	glColor3f(Color.r, Color.g, Color.b);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float degInRad = i + DEG2RAD;
		glVertex2f(cos(degInRad) / ratio * (Radius), sin(degInRad) * (Radius));

	}
	glEnd();

	if (BorderThickness != 0.0f)
	{
		glColor3f(BorderColor.r, BorderColor.g, BorderColor.b);
		glLineWidth(BorderThickness);
		glBegin(GL_LINE_STRIP);

		for (int i = 0; i <= 360; i++)
		{
			float degInRad = (i)*DEG2RAD;

			glVertex2f(cos(degInRad) / ratio * (Radius), sin(degInRad) * (Radius));

		}
	}
	glEnd();
}

//ANIM
void GeometryAnimation::Start() {};
void GeometryAnimation::Stop() {};
void GeometryAnimation::Pause() {};
GeometryAnimation::~GeometryAnimation() {};