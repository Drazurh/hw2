
struct Vertex{
	vec4f position;
	vec4f normal;
	vec2f texture;
}
struct Material{
	
}

class Part{
  protected:
	vec4 position;
	vec4 acceleration;
	vec4 velocity;
	
	Part* parent;
	Part* children;
	Vertex* vertexArray;
  public:
	Part();
	bool loadXML(char*);
	
}