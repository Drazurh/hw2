#include <GL/glut.h>
#include <part.h>
#include <Angel.h>


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
	
	part* parts;
	part* base_part;
	int part_count;
	
  public:
	Entity(vec4 _position);
	void render();
	void update();
}
