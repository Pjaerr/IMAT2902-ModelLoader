#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include "Win32OpenGL.h"
#include <iostream>
#include <vector>

class Model
{
  private:
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
	glm::vec3 m_scaleFactor = glm::vec3(1.0f, 1.0f, 1.0f);

	GLuint m_textureDataID;

	void loadModel();
	void createVBO();
	void createVAO();

  public:
	Model();
	Model(std::vector<float> vertices, std::vector<float> textureUVs, std::vector<float> normals, GLuint textureID);
	void setColour(float r, float g, float b);
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScaleFactor(float x, float y, float z);
	void draw(GLuint &program);
	glm::mat4 m_modelMatrix;
};