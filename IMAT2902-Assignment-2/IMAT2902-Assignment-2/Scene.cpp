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
	m_numberOfHangars = sizeof(hangars) / sizeof(hangars[0]);

	m_numberOfPlainGrassTiles = sizeof(plainGrassTiles) / sizeof(plainGrassTiles[0]);

	for (int i = 0; i < m_numberOfHangars; i++)
	{
		hangars[i] = m_modelLoader.loadFromObj("./Models/Hangar_withDoors.obj", "./Textures/Hangar_withDoors.bmp");
	}

	for (int i = 0; i < m_numberOfPlainGrassTiles; i++)
	{
		plainGrassTiles[i] = m_modelLoader.loadFromObj("./Models/grass_tile.obj", "./Textures/grass_tile.bmp");
	}

	test = m_modelLoader.loadFromObj("./Models/Control_Tower_Building.obj", "./Textures/Control_Tower_Building.bmp");
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
	hangars[0].setPosition(300, 0, 390);
	hangars[1].setPosition(240, 0, 390);


	hangars[2].setPosition(320, 0, 180);
	hangars[2].setRotation(0, 90, 0);

	plainGrassTiles[0].setPosition(165, 0, 200);

	test.setPosition(165, 10, 200);
	//test.setScaleFactor(0.5f, 0.5f, 0.5f);
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
	for (int i = 0; i < m_numberOfHangars; i++)
	{
		hangars[i].draw(program);
	}

	for (int i = 0; i < m_numberOfPlainGrassTiles; i++)
	{
		plainGrassTiles[i].draw(program);
	}

	test.draw(program);

	//Send the camera's view matrix to the shader.
	Win32OpenGL::SendUniformMatrixToShader(program, camera.viewMatrix, "view_matrix");
}