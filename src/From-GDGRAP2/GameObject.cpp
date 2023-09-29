#include "GameObject.h"

#include <iostream>

#include "EventBroadcaster.h"

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
	this->performModelTransform();
}

void GameObject::setPosition(vec3 newPos)
{
	this->transform = newPos;
	this->performModelTransform();
}

void GameObject::setRotAngles(float x, float y, float z)
{
	this->rotAngles = vec3(x, y, z);
	this->performModelTransform();
}

void GameObject::setRotAngles(vec3 newRot)
{
	this->rotAngles = newRot;
	this->performModelTransform();
}

void GameObject::setScale(float x, float y, float z)
{
	this->scale = vec3(x, y, z);
	this->performModelScale();
}

void GameObject::setScale(vec3 newScale)
{
	this->scale = newScale;
	this->performModelScale();
}

std::shared_ptr<Assets::Model> GameObject::getModel()
{
	return this->modelRef;
}

/**
 * \brief Performs the model transform via model-view-projection matrix form
 */
void GameObject::performModelTransform()
{
	// lucy0.Transform(
	// 	rotate(
	// 		scale(
	// 			translate(i, vec3(0, -0.08f, 0)),
	// 			vec3(scaleFactor)),
	// 		radians(90.0f), vec3(0, 1, 0)));

	mat4 translateOp = glm::translate(mat4(1), this->transform - this->origin);
	this->origin = this->transform;

	// mat4 rotateXOp = glm::rotate(scaleOp, glm::radians(this->rotAngles.x), vec3(1, 0, 0));
	// mat4 rotateYOp = glm::rotate(rotateXOp, glm::radians(this->rotAngles.y), vec3(0, 1, 0));
	// mat4 rotateZOp = glm::rotate(rotateYOp, glm::radians(this->rotAngles.z), vec3(0, 0, 1));

	// this->modelRef->Transform(rotateZOp);
	this->modelRef->Transform(translateOp);

}

void GameObject::performModelScale()
{
	mat4 scaleOp = glm::scale(mat4(1), this->scale);
	this->scale = VectorUtils::ones(); //TODO: Workaround. Reset to identity

	this->modelRef->Transform(scaleOp);
	EventBroadcaster::getInstance()->broadcastEvent(EventNames::ON_MARK_SCENE_DIRTY);
}
