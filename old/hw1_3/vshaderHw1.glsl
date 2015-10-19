attribute vec2 vPosition;

varying vec4 fcolor;

uniform vec2 windowSize;
uniform vec2 size;
uniform vec4 color;

uniform vec2 quadcopterPosition;
uniform float quadcopterRotation;

uniform vec2 position;
uniform float rotation;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() 
{
	vPosition *= size;
	
	float theta = (rotation+quadcopterRotation);
	mat2 rotationMatrix = mat2(cos(theta),sin(theta),-sin(theta),cos(theta));
	vPosition = rotationMatrix*vPosition;
  vPosition += position;
  vPosition += quadcopterPosition;
	
	vPosition.x=(2.0*vPosition.x)/windowSize.x-1.0;
	vPosition.y=(2.0*vPosition.y)/windowSize.y-1.0;
	
	gl_Position.x=vPosition.x;
	gl_Position.y=vPosition.y;
	
	//gl_Position = rand(vPosition);
	
	gl_Position.z=0.0;
	gl_Position.w=1.0;

	fcolor = color;
}
