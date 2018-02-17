#include "Scene.h"

Scene::Scene()
{

}
Scene::~Scene()
{

}

/*! The Start function gets called once when Main is preparing to be drawn. Anything
*	that only needs to happen once, such as creating a Model should occur here.
*/
void Scene::Start()
{
	simpleCube = Model();
	simpleCube.readModelFromFile("./Models/simpleCube.obj");
}

/*! The Update function runs every tick and is used to manage Model transformations
*	and other actions that need to occur every tick that aren't directly related
*	to the drawing of a model.
*/
void Scene::Update()
{

}

/*! The Render function calls the draw function of every Model being used
*	in the scene.
*/
void Scene::Render(GLuint &program)
{
	simpleCube.draw(program);
}