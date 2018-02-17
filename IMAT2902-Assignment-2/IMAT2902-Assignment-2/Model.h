#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include "Win32OpenGL.h"
#include "Resource.h"
#include <iostream>
#include <vector>
#include <fstream>

class Model
{
private:
	//Model Loader Stuff
	vector<float> m_indexedVertices;
	vector<unsigned int> m_faceIndices;

	GLuint m_vao;
	GLuint m_vboVertices;
	glm::vec3 m_colour;
	std::vector<float> m_vertices;

	float xRot = 0;
	float yRot = 0;
	float zRot = 0;

	float xPos = 0;
	float yPos = 0;
	float zPos = 0;


	void loadModel();
	glm::mat4 m_modelMatrix;

public:
	Model();
	void readModelFromFile(std::string filePath);
	void setColour(float r, float g, float b);
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z, bool degrees = false);
	void draw(GLuint &program);
};