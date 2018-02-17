#include "stdafx.h"
#include "Model.h"

Model::Model()
{

}

/**Takes a filepath for an obj model file and assigns the vertices in the file to the m_vertices vector.
*Working directory is where the Model.cpp file is.
*/
void Model::readModelFromFile(std::string filePath)
{
	std::fstream modelFile(filePath, std::ios_base::in);

	if (modelFile.is_open())
	{
		std::fstream modelfile(filePath, std::ios_base::in);

		string line = "";

		if (modelfile.is_open())
		{
			while (getline(modelfile, line))
			{
				string s;
				istringstream iss(line);

				iss >> s; // read to first whitespace

				/*Each vertex listed in a set of vertices (v):
				v 0.0 0.0 0.0
				v 1.0 0.0 0.0
				v 1.0 1.0 1.0 ..etc*/
				if (s == "v")
				{
					float vertex;

					while (iss >> vertex)
					{
						m_indexedVertices.push_back(vertex);
					}
				}

				/*Each face listed in a set of faces, each number representing a set of vertices. (f):
				f 1 7 5
				f 5 6 8
				f 2 3 4 ..etc*/
				else if (s == "f")
				{
					unsigned int faceIndex;

					while (iss >> faceIndex)
					{
						faceIndex--;   // change to zero based indices

						/*Get the faceIndex (the set of vertices to use) and then 
						multiply it by 3 to arrive at that set within the indexed vertices,
						as each element in the aformentioned vector is itself + 2 (x,y,z).*/
						faceIndex = 3 * faceIndex;

						/*Push the x, y and z vertices to the m_vertices vector.*/
						m_vertices.push_back(m_indexedVertices[faceIndex]);
						m_vertices.push_back(m_indexedVertices[faceIndex + 1]);
						m_vertices.push_back(m_indexedVertices[faceIndex + 2]);
					}
				}
			}

			modelFile.close();
		}

		loadModel();
	}
}

/**Creates a VBO using the member vector m_vertices and then creates a VAO using that previously created VBO.*/
void Model::loadModel()
{
	/*Create the Vertex Buffer Object (VBO)*/
	glGenBuffers(1, &m_vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);

	/*Create the Vertex Array Object (VAO)*/
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0); //Vertices are element 0 in the VAO.
}	 

void Model::setColour(float r, float g, float b)
{
	m_colour = { r, g, b };
}

void Model::setPosition(float x, float y, float z)
{
	xPos = x;
	yPos = y;
	zPos = z;
}

/**Change the angle by which the model will be rotated every Model::draw() call.
* The default sits at 0. Optional parameter degrees will take the angle[s] in
* degrees instead of radians if true. False default.
*/
void Model::setRotation(float x, float y, float z, bool degrees)
{
	if (degrees)
	{
		xRot = ((x * M_PI) / 180);
		yRot = ((y * M_PI) / 180);
		zRot = ((z * M_PI) / 180);
	}
	else
	{
		xRot = x;
		yRot = y;
		zRot = z;
	}
	
}

/**Draws the model and performs any transformations as per the member variable values.
* Takes a program parameter, taken as a reference to allow multiple models to send
their data to the shader using the same program.
*/
void Model::draw(GLuint &program)
{
	Win32OpenGL::SendUniformVector3ToShader(program, m_colour, "surface_colour"); //Let the shaders alter this colour.

	m_modelMatrix = glm::mat4(1.0f); //Initialise model matrix as a 4x4 identity matrix.
	
	/*Rotate the model matrix by the x, y and z Rot variables.*/
	if (xRot > 0)m_modelMatrix = glm::rotate(m_modelMatrix, (float)glm::radians((float)yRot), glm::vec3(1, 0, 0));
	
	if (yRot > 0)m_modelMatrix = glm::rotate(m_modelMatrix, (float)glm::radians((float)yRot), glm::vec3(0, 1, 0));
	
	if (zRot > 0)m_modelMatrix = glm::rotate(m_modelMatrix, (float)glm::radians((float)zRot), glm::vec3(0, 0, 1));
	
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(xPos, yPos, zPos));

	Win32OpenGL::SendUniformMatrixToShader(program, m_modelMatrix, "model_matrix"); //Send the model matrix to the shaders.
	
	glBindVertexArray(m_vao);
	GLuint numberOfElements = m_vertices.size() / 3;
	glDrawArrays(GL_TRIANGLES, 0, numberOfElements);
	glBindVertexArray(0);
}