#include "ModelManager.h"

#include <iostream>

ModelManager* ModelManager::sharedInstance = nullptr;
ModelManager* ModelManager::getInstance()
{
	return sharedInstance;
}

void ModelManager::initialize()
{
	sharedInstance = new ModelManager();
}

void ModelManager::destroy()
{
	sharedInstance->gameObjectMap.clear();
	sharedInstance->gameObjectList.clear();
	delete sharedInstance;
}

std::shared_ptr<GameObject> ModelManager::findObjectByName(String name)
{
	if (this->gameObjectMap[name] != nullptr) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!";
		return nullptr;
	}
}

ModelManager::List ModelManager::getAllObjects()
{
	return this->gameObjectList;
}

/**
 * \brief Returns associated model representations of objects added.
 * \return 
 */
ModelManager::ModelList ModelManager::getAllObjectModels() const
{
	ModelList models;
	for(int i = 0; i < this->gameObjectList.size(); i++)
	{
		models.push_back(*this->gameObjectList[i]->getModel());
	}

	return models;
}

int ModelManager::activeObjects() const
{
	return this->gameObjectList.size();
}

std::shared_ptr<GameObject> ModelManager::getLastObject()
{
	return this->gameObjectList[this->activeObjects() - 1];
}

void ModelManager::addObject(std::shared_ptr<GameObject> gameObject)
{
	if (this->gameObjectMap[gameObject->getName()] != nullptr) {
		int count = 1;
		String revisedString = gameObject->getName() + " " + "(" + std::to_string(count) + ")";
		while (this->gameObjectMap[revisedString] != nullptr) {
			count++;
			revisedString = gameObject->getName() + " " + "(" + std::to_string(count) + ")";
		}
		gameObject->name = revisedString;
		this->gameObjectMap[revisedString] = gameObject;
	}
	else {
		this->gameObjectMap[gameObject->getName()] = gameObject;
	}
	this->gameObjectList.push_back(gameObject);
	std::cout << "Added game object in manager: " + gameObject->getName() << std::endl;
}

void ModelManager::createObject(GameObject::PrimitiveType type)
{
}

void ModelManager::createObjectFromFile(String name, GameObject::PrimitiveType type, vec3 position, vec3 rotation,
	vec3 scale)
{
}

void ModelManager::deleteObject(std::shared_ptr<GameObject> gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}
}

void ModelManager::deleteObjectByName(String name)
{
	std::shared_ptr<GameObject> object = this->findObjectByName(name);
	if(object != nullptr)
	{
		this->deleteObject(object);
	}
}

void ModelManager::setSelectedObject(String name)
{
	if (this->gameObjectMap[name] != nullptr) {
		this->setSelectedObject(this->gameObjectMap[name]);
	}
}

void ModelManager::setSelectedObject(std::shared_ptr<GameObject> gameObject)
{
	this->selectedObject = gameObject;
}

std::shared_ptr<GameObject> ModelManager::getSelectedObject()
{
	return this->selectedObject;
}

void ModelManager::clearAllObjects()
{
	this->gameObjectList.clear();
	this->gameObjectMap.clear();
}
