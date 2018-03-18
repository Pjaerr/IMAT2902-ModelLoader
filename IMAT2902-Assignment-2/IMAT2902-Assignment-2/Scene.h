/*! \file Scene.h
*	Controls all of the Models in a scene including their drawing and transformations.
*/

#pragma once
#include "ModelLoader.h"
#include "Model.h"
#include "Camera.h"
#include <map>

class Scene
{
private:
	
	Model plainGrassTiles[41];

	Model runwayTiles[11];

	Model airStripTiles[17];

	Model carParkTiles[8];

	Model hangars[2];

	Model smallStorageBuildings;

	Model buses[2];

	Model cars[14];

	Model entranceBuilding[2];

	Model controlBuilding;
	
	Model controlTower;

	Model cafeArea;

	Model cessnas[4];

	Model boeing;

	int m_numberOfRunwayTiles;
	int m_numberOfPlainGrassTiles;
	int m_numberOfAirStripTiles;
	int m_numberOfCarParkTiles;
	int m_numberOfHangars;
	int m_numberOfBuses;
	int m_numberOfCars;

	/*! Models should be loaded via m_modelLoader in here.*/
	void loadModels();

	/*! Model::setPosition() and Model::setRotation() to be called on models in here when
	only happening once. Constant postion/rotation changes should be placed in Update()*/
	void setModelTransformations();

	//Temporary rotation testing.
	float m_yAngle = 0.0f;

	float m_x = 0;
	float m_y = 0;


	std::vector<Model> models;
	std::map <std::string, std::string> fileNames;

	void loadExternalScene(const char * filePath);
public:
	/*! Scene default constructor.*/
	Scene();

	/*!Scene deconstructor.*/
	~Scene();

	/*! The Start function gets called once when Main is preparing to be drawn. Anything
	*	that only needs to happen once, such as creating a Model should occur here.
	*/
	void Start();

	void keyIsPressed(unsigned char key);

	void mouseIsMoved(int xPos, int yPos);

	/*! The Update function runs every tick and is used to manage Model transformations 
	*	and other actions that need to occur every tick that aren't directly related
	*	to the drawing of a model.
	*/
	void Update();

	/*! The Render function calls the draw function of every Model being used
	*	in the scene.
	*/
	void Render(GLuint &program);

	ModelLoader m_modelLoader;

	Camera camera;

	float m_cameraMovementSpeed = 10.0f;
};