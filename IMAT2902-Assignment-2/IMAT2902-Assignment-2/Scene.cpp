#include "Scene.h"
#include "cmath"

Scene::Scene()
{
	m_modelLoader = ModelLoader();
	camera = Camera(glm::vec3(0, 60, 280), glm::vec3(0, 0, 0));
}
Scene::~Scene()
{

}

void Scene::loadModels()
{
	m_numberOfPlainGrassTiles = sizeof(plainGrassTiles) / sizeof(plainGrassTiles[0]);
	m_numberOfRunwayTiles = sizeof(runwayTiles) / sizeof(runwayTiles[0]);
	m_numberOfAirStripTiles = sizeof(airStripTiles) / sizeof(airStripTiles[0]);
	m_numberOfCarParkTiles = sizeof(carParkTiles) / sizeof(carParkTiles[0]);
	m_numberOfHangars = sizeof(hangars) / sizeof(hangars[0]);
	m_numberOfBuses = sizeof(buses) / sizeof(buses[0]);
	m_numberOfCars = sizeof(cars) / sizeof(cars[0]);

	for (int i = 0; i < m_numberOfPlainGrassTiles; i++)
	{
		plainGrassTiles[i] = m_modelLoader.loadFromObj("./Models/grass_tile.obj", "./Textures/grass_tile.bmp");
	}

	for (int i = 0; i < m_numberOfRunwayTiles; i++)
	{
		runwayTiles[i] = m_modelLoader.loadFromObj("./Models/runway_tile.obj", "./Textures/runway_tile.bmp");
	}

	for (int i = 0; i < m_numberOfAirStripTiles; i++)
	{
		airStripTiles[i] = m_modelLoader.loadFromObj("./Models/airstrip_tile.obj", "./Textures/airstrip_tile.bmp");
	}

	for (int i = 0; i < m_numberOfCarParkTiles; i++)
	{
		carParkTiles[i] = m_modelLoader.loadFromObj("./Models/carpark_tile.obj", "./Textures/carpark_tile.bmp");
	}

	hangars[0] = m_modelLoader.loadFromObj("./Models/Hangar_withDoors.obj", "./Textures/Hangar_withDoors.bmp");
	hangars[1] = m_modelLoader.loadFromObj("./Models/Hangar_withoutDoors.obj", "./Textures/Hangar_withoutDoors.bmp");

	smallStorageBuildings = m_modelLoader.loadFromObj("./Models/small_storage_buildings.obj", "./Textures/small_storage_buildings.bmp");

	for (int i = 0; i < m_numberOfBuses; i++)
	{
		buses[i] = m_modelLoader.loadFromObj("./Models/bus.obj", "./Textures/bus.bmp");
	}

	for (int i = 0; i < m_numberOfCars - 6; i++)
	{
		cars[i] = m_modelLoader.loadFromObj("./Models/red_car.obj", "./Textures/red_car.bmp");
	}

	cars[3] = m_modelLoader.loadFromObj("./Models/blue_car.obj", "./Textures/blue_car.bmp");
	cars[4] = m_modelLoader.loadFromObj("./Models/green_car.obj", "./Textures/green_car.bmp");

	for (int i = 4; i < m_numberOfCars - 4; i++)
	{
		cars[i] = m_modelLoader.loadFromObj("./Models/blue_car.obj", "./Textures/blue_car.bmp");
	}

	cars[9] = m_modelLoader.loadFromObj("./Models/red_car.obj", "./Textures/red_car.bmp");
	cars[10] = m_modelLoader.loadFromObj("./Models/green_car.obj", "./Textures/green_car.bmp");
	cars[11] = m_modelLoader.loadFromObj("./Models/green_car.obj", "./Textures/green_car.bmp");
	cars[12] = m_modelLoader.loadFromObj("./Models/red_car.obj", "./Textures/red_car.bmp");
	cars[13] = m_modelLoader.loadFromObj("./Models/green_car.obj", "./Textures/green_car.bmp");

	entranceBuilding[0] = m_modelLoader.loadFromObj("./Models/Entrance_Building.obj", "./Textures/Entrance_Building.bmp");

	entranceBuilding[1] = m_modelLoader.loadFromObj("./Models/Entrance_Building.obj", "./Textures/Entrance_Building.bmp");

	controlBuilding = m_modelLoader.loadFromObj("./Models/Control_Building.obj", "./Textures/Control_Building.bmp");

	controlTower = m_modelLoader.loadFromObj("./Models/Control_Tower_Building.obj", "./Textures/Control_Tower_Building.bmp");

	cafeArea = m_modelLoader.loadFromObj("./Models/Cafe_Area.obj", "./Textures/Cafe_Area.bmp");

	for (int i = 0; i < 4; i++)
	{
		cessnas[i] = m_modelLoader.loadFromObj("./Models/Cessna.obj", "./Textures/plane_ah24.bmp");
	}

	boeing = m_modelLoader.loadFromObj("./Models/boeing.obj", "./Textures/boeing.bmp");
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

/*
	
	From (0, 0, 0). Max distance is (1386, -1, 756) 

*/


void Scene::setModelTransformations()
{
	for (int i = 0; i < m_numberOfPlainGrassTiles - 8; i++)
	{
			plainGrassTiles[i].setPosition(i * 126, -1, 0);

			if (i >= 11 && i < 22)
			{
				plainGrassTiles[i].setPosition((i - 11) * 126, -1, 2 * 126);
			}
			else if (i >= 22 && i < 33)
			{
				plainGrassTiles[i].setPosition((i - 22) * 126, -1, 3 * 126);
			}
	}

	for (int i = 0; i < m_numberOfRunwayTiles; i++)
	{
		runwayTiles[i].setPosition(i * 126, -1, 126);
		runwayTiles[i].setRotation(0, 90, 0);
	}

	airStripTiles[0].setPosition(0, -1, 4 * 126);

	airStripTiles[1].setPosition(126, -1, 4 * 126);
	airStripTiles[2].setPosition(126, -1, 5 * 126);
	airStripTiles[3].setPosition(126, -1, 6 * 126);

	airStripTiles[4].setPosition(2 * 126, -1, 4 * 126);
	airStripTiles[5].setPosition(2 * 126, -1, 5 * 126);
	airStripTiles[6].setPosition(2 * 126, -1, 6 * 126);

	plainGrassTiles[33].setPosition(3 * 126, -1, 4 * 126);
	plainGrassTiles[34].setPosition(4 * 126, -1, 4 * 126);
	plainGrassTiles[35].setPosition(5 * 126, -1, 4 * 126);
	plainGrassTiles[36].setPosition(6 * 126, -1, 4 * 126);
	plainGrassTiles[37].setPosition(7 * 126, -1, 4 * 126);
	plainGrassTiles[38].setPosition(8 * 126, -1, 4 * 126);
	plainGrassTiles[39].setPosition(8 * 126, -1, 5 * 126);
	plainGrassTiles[40].setPosition(8 * 126, -1, 6 * 126);

	airStripTiles[7].setPosition(3 * 126, -1, 5 * 126);
	airStripTiles[8].setPosition(3 * 126, -1, 6 * 126);

	airStripTiles[9].setPosition(4 * 126, -1, 5 * 126);
	airStripTiles[10].setPosition(4 * 126, -1, 6 * 126);

	airStripTiles[11].setPosition(5 * 126, -1, 5 * 126);
	airStripTiles[12].setPosition(5 * 126, -1, 6 * 126);

	airStripTiles[13].setPosition(6 * 126, -1, 5 * 126);
	airStripTiles[14].setPosition(6 * 126, -1, 6 * 126);

	airStripTiles[15].setPosition(7 * 126, -1, 5 * 126);
	airStripTiles[16].setPosition(7 * 126, -1, 6 * 126);


	carParkTiles[0].setPosition(0, -1, 5 * 126);
	carParkTiles[0].setRotation(0, 90, 0);
	carParkTiles[1].setPosition(0, -1, 6 * 126);
	carParkTiles[1].setRotation(0, 90, 0);

	carParkTiles[2].setPosition(9 * 126, -1, 4 * 126);
	carParkTiles[2].setRotation(0, 90, 0);
	carParkTiles[3].setPosition(9 * 126, -1, 5 * 126);
	carParkTiles[3].setRotation(0, 90, 0);
	carParkTiles[4].setPosition(9 * 126, -1, 6 * 126);
	carParkTiles[4].setRotation(0, 90, 0);

	carParkTiles[5].setPosition(10 * 126, -1, 4 * 126);
	carParkTiles[5].setRotation(0, 90, 0);
	carParkTiles[6].setPosition(10 * 126, -1, 5 * 126);
	carParkTiles[6].setRotation(0, 90, 0);
	carParkTiles[7].setPosition(10 * 126, -1, 6 * 126);
	carParkTiles[7].setRotation(0, 90, 0);

	hangars[0].setPosition(126, 0, (6 * 126) - 35);
	hangars[1].setPosition(126, 0, (5 * 126) - 35);

	smallStorageBuildings.setPosition(0, 0, 4 * 126);
	smallStorageBuildings.setRotation(0, 80, 0);

	buses[0].setPosition(126, 0, (4 * 126) + 20);
	buses[0].setRotation(0, 40, 0);
	buses[0].setScaleFactor(0.4f, 0.4f, 0.4f);

	buses[1].setPosition(126, 0, (4 * 126) - 30);
	buses[1].setRotation(0, -60, 0);
	buses[1].setScaleFactor(0.4f, 0.4f, 0.4f);

	for (int i = 0; i < 5; i++)
	{
		cars[i].setPosition(40, 0, ((5 * 126)) + i * 30);

		if (i > 2)
		{
			cars[i].setPosition(-40, 0, ((5 * 126)) + i * 30);
			cars[i].setRotation(0, 180, 0);
		}

		cars[i].setScaleFactor(0.4f, 0.4f, 0.4f);
	}

	for (int i = 5; i < m_numberOfCars; i++)
	{
		cars[i].setPosition((10 * 126) + 40, 0, ((3 * 126)) + i * 32); //go 60 along

		cars[i].setScaleFactor(0.4f, 0.4f, 0.4f);
	}

	entranceBuilding[0].setPosition(3 * 126, 0, (6 * 126) + 25);
	entranceBuilding[0].setRotation(0, 180, 0);
	entranceBuilding[0].setScaleFactor(0.9f, 0.9f, 0.9f);

	controlBuilding.setPosition((4 * 126) + 20, 0, (6 * 126) + 25);
	controlBuilding.setRotation(0, 180, 0);

	cafeArea.setPosition((4 * 126) + 113, 0, (6 * 126) + 5);
	cafeArea.setRotation(0, 180, 0);

	controlTower.setPosition((5 * 126) + 140, 0, (6 * 126) + 25);
	controlTower.setRotation(0, 180, 0);

	entranceBuilding[1].setPosition((6 * 126) + 140, 0, (6 * 126) - 10);
	entranceBuilding[1].setRotation(0, 45, 0);


	cessnas[0].setPosition((4 * 126), -9, (5 * 126));
	cessnas[0].setScaleFactor(1.2f, 1.2f, 1.2f);


	boeing.setPosition((1.5 * 126), 180, 126);
	boeing.setRotation(0, 290, 0);
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
	for (int i = 0; i < m_numberOfPlainGrassTiles; i++)
	{
		plainGrassTiles[i].draw(program);
	}

	for (int i = 0; i < m_numberOfRunwayTiles; i++)
	{
		runwayTiles[i].draw(program);
	}

	for (int i = 0; i < m_numberOfAirStripTiles; i++)
	{
		airStripTiles[i].draw(program);
	}
	
	for (int i = 0; i < m_numberOfCarParkTiles; i++)
	{
		carParkTiles[i].draw(program);
	}

	for (int i = 0; i < m_numberOfHangars; i++)
	{
		hangars[i].draw(program);
	}

	smallStorageBuildings.draw(program);

	for (int i = 0; i < m_numberOfBuses; i++)
	{
		buses[i].draw(program);
	}

	for (int i = 0; i < m_numberOfCars; i++)
	{
		cars[i].draw(program);
	}

	for (int i = 0; i < 4; i++)
	{
		cessnas[i].draw(program);
	}

	boeing.draw(program);

	entranceBuilding[0].draw(program);
	entranceBuilding[1].draw(program);
	controlBuilding.draw(program);
	controlTower.draw(program);
	cafeArea.draw(program);

	//Send the camera's view matrix to the shader.
	Win32OpenGL::SendUniformMatrixToShader(program, camera.viewMatrix, "view_matrix");
}