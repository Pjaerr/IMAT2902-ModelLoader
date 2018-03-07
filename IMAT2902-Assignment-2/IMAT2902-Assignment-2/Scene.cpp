#include "Scene.h"
#include "cmath"

Scene::Scene()
{
	m_modelLoader = ModelLoader();
}
Scene::~Scene()
{

}

void Scene::loadModels()
{
	m_numberOfCubes = sizeof(cubes) / sizeof(cubes[0]);

	cubes[0] = m_modelLoader.loadFromObj("./Models/suzanne.obj");
}

void Scene::keyIsPressed(unsigned char key)
{
	//Check for keyboard input here using VK_keyname

	/*Temporary Rotation code with arrow keys.*/
	if (key == VK_LEFT)
	{
		camera.rotate(-2, 0);
	}
	if (key == VK_RIGHT)
	{
		camera.rotate(2, 0);
	}

	if (key == VK_UP)
	{
		camera.rotate(0, 2);
	}
	if (key == VK_DOWN)
	{
		camera.rotate(0, -2);
	}

	if (key == 0x57)
	{
		camera.move(Direction::forwards, m_cameraMovementSpeed);
	}
	else if (key == 0x53)
	{
		camera.move(Direction::backwards, m_cameraMovementSpeed);
	}

	if (key == 0x41)
	{
		camera.move(Direction::left, m_cameraMovementSpeed);
	}
	else if (key == 0x44)
	{
		camera.move(Direction::right, m_cameraMovementSpeed);
	}
}

void Scene::setModelTransformations()
{
	for (int i = 0; i < m_numberOfCubes; i++)
	{
		cubes[i].setPosition(i + i, -2.0f, -4.0f);
		cubes[i].setColour(1.0f, 1.0f, 1.0f);
	}
}

/*! The Start function gets called once when Main is preparing to be drawn. Anything
*	that only needs to happen once, such as creating a Model should occur here.
*/
void Scene::Start()
{
	loadModels();
	setModelTransformations();
}

/*! The Update function runs every tick and is used to manage Model transformations
*	and other actions that need to occur every tick that aren't directly related
*	to the drawing of a model.
*/
void Scene::Update()
{
	m_yAngle += 80.0f;
	for (int i = 0; i < m_numberOfCubes; i++)
	{
		cubes[i].setRotation(0, m_yAngle, 0, true);
	}
}

/*! The Render function calls the draw function of every Model being used
*	in the scene.
*/
void Scene::Render(GLuint &program)
{
	for (int i = 0; i < m_numberOfCubes; i++)
	{
		cubes[i].draw(program);
	}


	//Send the camera's view matrix to the shader.
	Win32OpenGL::SendUniformMatrixToShader(program, camera.viewMatrix, "view_matrix");
}