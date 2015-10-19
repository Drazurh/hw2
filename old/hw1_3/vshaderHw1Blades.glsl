attribute  vec4 vPosition;

uniform vec2 windowSize;

varying vec4 color;

void main() 
{
  gl_Position.x=(2.0*(size*(vPosition.x)+float(offset.x)))/windowSize.x-1.0;
  gl_Position.y=(2.0*(size*(vPosition.y)+float(offset.y)))/windowSize.y-1.0;
  gl_Position.z=0.0;
  gl_Position.w=1.0;
}
