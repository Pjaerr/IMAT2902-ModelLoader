#include "Scene.h"
#include "cmath"

Scene::Scene()
{
	m_modelLoader = ModelLoader();
	camera = Camera(glm::vec3(165, 60, 160), glm::vec3(0, 0, 0));
}
Scene::~Scene()
{

}

void Scene::loadModels()
{

	testPlane = m_modelLoader.loadFromObj("./Models/plane_ah24.obj", "./Textures/plane_ah24.bmp");

	m_numberOfHangars = sizeof(hangars) / sizeof(hangars[0]);

	for (int i = 0; i < m_numberOfHangars; i++)
	{
		hangars[i] = m_modelLoader.loadFromObj("./Models/Hangar.obj", "./Textures/Hangar.bmp");
	}

	controlBuilding = m_modelLoader.loadFromObj("./Models/ControlBuilding.obj", "./Textures/ControlBuilding.bmp");

	ground = m_modelLoader.loadFromObj("./Models/Ground.obj", "./Textures/Ground.bmp");

	

}

void Scene::keyIsPressed(unsigned char key)
{
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

void Scene::mouseIsMoved(int xPos, int yPos)
{
	camera.rotate((float)xPos, -((float)yPos));
}


/*Abritrary Scene Positioning Values:

	:Assuming the ground is positioned at (340, -6.3, 200).
	:Any model at (0, 0, 0) will be at the top left of the ground.

	:The maximum distance on the X a model can be moved whilst staying within the bounds of the ground
	is 330.

	:The maximum distance on the Z a model can be moved whilst staying within the bounds of the ground
	is 400.

	:Therefore, a model positioned at (165, 0, 200) will be at the center of the ground.
*/


void Scene::setModelTransformations()
{
	//ground.setColour(0.8, 1, 0.8);

	for (int i = 0; i < m_numberOfHangars; i++)
	{
		//hangars[i].setColour(1, 0.6, 0.6);
	}

	ground.setPosition(340, -6.3f, 200);

	hangars[0].setPosition(300, 0, 390);
	hangars[1].setPosition(240, 0, 390);


	hangars[2].setPosition(320, 0, 180);
	hangars[2].setRotation(0, 90, 0);

	//testPlane.setColour(0.6, 0.6, 1);
	testPlane.setPosition(165, -4.8f, 200);
	testPlane.setScaleFactor(0.65f, 0.65f, 0.65f);

	//controlBuilding.setColour(0.7, 0.1, 0.3);
	controlBuilding.setPosition(100, 0, 100);
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

}

/*! The Render function calls the draw function of every Model being used
*	in the scene.
*/
void Scene::Render(GLuint &program)
{
	ground.draw(program);
	
	for (int i = 0; i < m_numberOfHangars; i++)
	{
		hangars[i].draw(program);
	}

	testPlane.draw(program);

	controlBuilding.draw(program);

	//Send the camera's view matrix to the shader.
	Win32OpenGL::SendUniformMatrixToShader(program, camera.viewMatrix, "view_matrix");
}