#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include "Win32OpenGL.h"
#include <iostream>
#include <vector>


class Model
{
private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_textureUVs;
	std::vector<glm::vec3> m_normals;

	std::vector<float> m_fVertices;
	std::vector<float> m_fTextureUVs;
	std::vector<float> m_fNormals;
	
	GLuint m_vao;
	GLuint m_vboVertices;
	GLuint m_vboTextureUVs;
	GLuint m_vboNormals;


	glm::vec3 m_colour;

	glm::vec3 m_rotation;
	glm::vec3 m_postion;

	void loadModel();
	

public:
	Model();
	Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textureUVs, std::vector<glm::vec3> normals);
	Model(std::vector<float> vertices, std::vector<float> textureUVs, std::vector<float> normals);
	void setColour(float r, float g, float b);
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z, bool degrees = false);
	void draw(GLuint &program);
	glm::mat4 m_modelMatrix;
};