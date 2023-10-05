#include "ObjectGroup.h"
#include <iostream>

#include "EventBroadcaster.h"
#include "EventNames.h"
#include "Debug.h"

ObjectGroup::ObjectGroup(String name) : GameObject(name, PrimitiveType::OBJECT_GROUP)
{

}

void ObjectGroup::addModel(std::shared_ptr<Assets::Model> model)
{
	this->modelList.push_back(model);
}

void ObjectGroup::clearModelGroup()
{
	this->modelList.clear();
}

int ObjectGroup::getSize() const
{
	return this->modelList.size();
}

std::shared_ptr<Assets::Model> ObjectGroup::getModelAt(int index)
{
	return this->modelList[index];
}

void ObjectGroup::performModelTransform()
{
	for(int i  = 0; i < this->modelList.size(); i++)
	{
		mat4 translateOp = glm::translate(mat4(1), this->transform - this->origin);
		this->modelList[i]->Transform(translateOp);
	}
	this->origin = this->transform;

	Debug::Log("Performed group model transform on object: " + this->name + "\n");
	EventBroadcaster::getInstance()->broadcastEvent(EventNames::ON_MARK_SCENE_DIRTY);
}

void ObjectGroup::performModelRotate()
{
	for(int i = 0; i < this->modelList.size(); i++)
	{
		vec3 rotOffset = this->rotAngles - this->originRot;
		mat4 rotateXOp = glm::rotate(mat4(1), glm::radians(rotOffset.x), vec3(1, 0, 0));
		mat4 rotateYOp = glm::rotate(mat4(1), glm::radians(rotOffset.y), vec3(0, 1, 0));
		mat4 rotateZOp = glm::rotate(mat4(1), glm::radians(rotOffset.z), vec3(0, 0, 1));

		this->modelList[i]->Transform(rotateXOp);
		this->modelList[i]->Transform(rotateYOp);
		this->modelList[i]->Transform(rotateZOp);
	}
	this->originRot = this->rotAngles;

	EventBroadcaster::getInstance()->broadcastEvent(EventNames::ON_MARK_SCENE_DIRTY);
}

void ObjectGroup::performModelScale()
{
	for (int i = 0; i < this->modelList.size(); i++)
	{
		mat4 scaleOp = glm::scale(mat4(1), this->scale);
		this->modelList[i]->Transform(scaleOp);
	}
	this->scale = VectorUtils::ones(); //TODO: Workaround. Reset to identity

	EventBroadcaster::getInstance()->broadcastEvent(EventNames::ON_MARK_SCENE_DIRTY);
}
