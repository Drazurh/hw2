#include "entity.h"

Entity::Entity(vec3 _position){
	position = _position;
}

void Entity::render(){
	
}

void Entity::update(){
	position += velocity;
	velocity += acceleration;
	
	rotation += angular_velocity;
	angular_velocity += angular_acceleration;
}









