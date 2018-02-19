#include "Scene.h"
#include "cmath"

Scene::Scene()
{
	m_modelLoader = ModelLoader();
}
Scene::~Scene()
{

}

/*! The Start function gets called once when Main is preparing to be drawn. Anything
*	that only needs to happen once, such as creating a Model should occur here.
*/
void Scene::Start()
{
	simpleCube = m_modelLoader.loadFromObj("./Models/suzanne.obj");
}

/*! The Update function runs every tick and is used to manage Model transformations
*	and other actions that need to occur every tick that aren't directly related
*	to the drawing of a model.
*/
void Scene::Update()
{
	m_yAngle += 80.0f;
	simpleCube.setColour(1.0f, 1.0f, 1.0f);
	simpleCube.setRotation(0, m_yAngle, 0, true);
	simpleCube.setPosition(0.0f, 0.0f, 0.0f);
	
}

/*! The Render function calls the draw function of every Model being used
*	in the scene.
*/
void Scene::Render(GLuint &program)
{
	simpleCube.draw(program);
}