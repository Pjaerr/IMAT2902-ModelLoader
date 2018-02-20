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

	/*Load models*/
	for (int i = 0; i < m_numberOfCubes; i++)
	{
		cubes[i] = m_modelLoader.loadFromObj("./Models/suzanne.obj");
	}
}

void Scene::keyIsPressed(unsigned char key)
{
	//Check for keyboard input here using VK_keyname
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
}