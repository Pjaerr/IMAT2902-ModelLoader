/*! \file Scene.h
*	Controls all of the Models in a scene including their drawing and transformations.
*/

#pragma once
#include "ModelLoader.h"
#include "Model.h"

class Scene
{
private:

	Model simpleCube; //!< Temporary cube model for testing.

public:
	/*! Scene default constructor.*/
	Scene();

	/*!Scene deconstructor.*/
	~Scene();

	/*! The Start function gets called once when Main is preparing to be drawn. Anything
	*	that only needs to happen once, such as creating a Model should occur here.
	*/
	void Start();

	/*! The Update function runs every tick and is used to manage Model transformations 
	*	and other actions that need to occur every tick that aren't directly related
	*	to the drawing of a model.
	*/
	void Update();

	/*! The Render function calls the draw function of every Model being used
	*	in the scene.
	*/
	void Render(GLuint &program);
};