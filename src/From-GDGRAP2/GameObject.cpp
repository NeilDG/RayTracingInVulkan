#include "GameObject.h"

GameObject::GameObject()
{
	this->name = "No-name";
	this->type = NONE;
	this->modelRef = nullptr;
}

GameObject::GameObject(String name, PrimitiveType type)
{
	this->name = name;
	this->type = type;
	this->modelRef = nullptr;
}

GameObject::GameObject(String name, PrimitiveType type, std::shared_ptr<Assets::Model> modelRef)
{
	this->name = name;
	this->type = type;
	this->modelRef = modelRef;
}

GameObject::String GameObject::getName()
{
	return this->name;
}

GameObject::PrimitiveType GameObject::getType()
{
	return this->type;
}

bool GameObject::isEnabled()
{
	return this->enabled;
}

void GameObject::setEnabled(bool flag)
{
	this->enabled = flag;
}

GameObject::vec3 GameObject::getTransform() const
{
	return this->transform;
}

GameObject::vec3 GameObject::getScale() const
{
	return this->scale;
}

GameObject::vec3 GameObject::getRotAngles() const
{
	return this->rotAngles;
}

void GameObject::setPosition(float x, float y, float z)
{
	this->transform = vec3(x, y, z);
}

void GameObject::setPosition(vec3 newPos)
{
	this->transform = newPos;
}

void GameObject::setRotAngles(float x, float y, float z)
{
	this->rotAngles = vec3(x, y, z);
}

void GameObject::setRotAngles(vec3 newRot)
{
	this->rotAngles = newRot;
}

void GameObject::setScale(float x, float y, float z)
{
	this->scale = vec3(x, y, z);
}

void GameObject::setScale(vec3 newScale)
{
	this->scale = newScale;
}

std::shared_ptr<Assets::Model> GameObject::getModel()
{
	return this->modelRef;
}
