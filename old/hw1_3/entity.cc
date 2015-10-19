#include <entity.h>

struct Vertex{
	vec4 position;
	vec4 normal;
	vec2 texture;
}

class Entity{	
  protected:
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	
	vec3 rotation;
	vec3 angular_velocity;
	vec3 angular_acceleration;
	
	part base_part;
	
  public:
	Entity(vec3 _position);
	void render();
	void update();
}

Entity::Entity(vec3 _position);{
	position = position;
}

Entity::render(){
	
}

Entity::update(){
	position += velocity;
	velocity += acceleration;
	
	rotation += angular_velocity;
	angular_velocity += angular_acceleration;
	
	base_part.update();
}









