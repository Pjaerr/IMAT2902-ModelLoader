/*! \file ModelLoader.h
*	Loads a model from an OBJ file and returns it as a Model object that can be drawn and transformed.
*/

#pragma once
#include "Model.h"

class ModelLoader
{
private:


public:
	/*! ModelLoader default constructor.*/
	ModelLoader();

	/*! ModelLoader deconstructor.*/
	~ModelLoader();

	/*! Loads a model from an OBJ file.
	*\param filePath The filepath containing the OBJ file.
	*/
	Model loadFromObj(std::string filePath);
};