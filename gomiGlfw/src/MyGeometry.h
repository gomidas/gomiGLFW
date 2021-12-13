#pragma once
#ifndef _MYGEOMETRY_
#define _MYGEOMETRY_

#define DEG2RAD 3.14159/180

#include <stdio.h>
#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include "myMath.h"
#include "myColor.h"
#include <iostream>
#include <linmath.h>
#include <list>
#endif


using namespace std;

class GeometryAnimation
{
public:
	float PlaybackTime=0;
	float SequenceTime = 0;
	string Name="";

	static enum AnimAttribute {
		Width,Height,Opacity,Visiblity, Color
	};
	AnimAttribute Attribute;

	GeometryAnimation() {};
	GeometryAnimation(float sequencetime, AnimAttribute attribute, string name)
	{
		SequenceTime = sequencetime;
		Name = name;
		Attribute = attribute;
	}
	void Start();
	void Stop();
	void Pause();
	~GeometryAnimation();
};

class GeometryObject {
	
public:
	list<GeometryAnimation*> Animations;

	FRGB Color = FRGB(0, 0, 0);
	int fb_W=0, fb_H=0;
	string Name = "";

	GeometryObject() {};
	GeometryObject(string name) { Name = name; };

	void AddAnimation(float sequencetime, GeometryAnimation::AnimAttribute attribute, string name);
	void DeleteAnimation(string name);
	void DeleteAllAnimations();
	~GeometryObject();
};

class Circle :public GeometryObject { //IN ORDER TO USE BASE CLASS VARIABLES WE SHOULD PUT PUBLIC
public:

	float Radius = 0;
	float BorderThickness = 0;

	FRGB BorderColor = FRGB(0, 0, 0);

	Circle() {};
	Circle(float radius, float borderthickness, FRGB color, FRGB border, string name = "") {
		Radius = radius;
		BorderThickness = borderthickness;
		Color = color;
		BorderColor = border;
		Name = name;
	};
	void Render(GLFWwindow* window);
};

class Rectangle :public GeometryObject { 
public:

	float Radius = 0;
	float BorderThickness = 0;
	FRGB BorderColor = FRGB(0, 0, 0);
	Rectangle() {};
	Rectangle(float radius, float borderthickness, FRGB color, FRGB border, string name = "") {
		Radius = radius;
		BorderThickness = borderthickness;
		Color = color;
		BorderColor = border;
		Name = name;
	};
	void Render(GLFWwindow* window);
};
