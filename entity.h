//#include <GL/glut.h>
#include <Angel.h>

struct Vertex{
	vec4 position;
	vec4 color;
};

class Entity{	
  protected:
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	
	vec3 rotation;
	vec3 angular_velocity;
	vec3 angular_acceleration;
	
	
  public:
	Entity(vec3 _position);
	void render();
	void update();
};
