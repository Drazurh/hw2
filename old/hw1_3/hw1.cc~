#include <GL/glew.h> 
#include <GL/glut.h> 
#include <Angel.h>

#include <pthread.h>
#define NUM_THREADS 2
#define GLUT_THREAD 0
#define SIMULATION_THREAD 1

#include <sys/time.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;


// initial window size
GLfloat wh = 500;
GLfloat ww = 500;

GLfloat ticks_per_second = 100;
GLfloat max_fps = 60;

enum controls {LEFT,RIGHT,UP,DOWN,W,A,S,D};

bool controller[8] = {false};

GLint colorLoc;
GLint windowSizeLoc;
GLint sizeLoc;
GLint positionLoc;
GLint rotationLoc;
GLint quadcopterPositionLoc;
GLint quadcopterRotationLoc;

struct Part{
	vec2 position;
	vec4 color;
	int num_triangles;
	int index;
};

class Quadcopter{
  public:
	Part body;
	Part arms[4];
	Part blades[4];
	
	vec2* points;
	GLint num_points;
	vec3* indices;
	
	GLfloat scale;
	
	vec2 position;
	vec2 velocity;
	vec2 acceleration;
	
	GLfloat angle;
	GLfloat angle_velocity;
	GLfloat angle_acceleration;
	
	GLfloat blade_angles[4];
	GLfloat blade_speed[4];
	
	Quadcopter(vec2 _position, GLfloat _scale, const char *filename){
		position = _position;
		velocity = vec2(0,0);
		acceleration = vec2(0,0);
		scale = _scale;
		angle = 0;
		angle_velocity =0;
		angle_acceleration =0;
		for(int i=0; i<4; i++){
			blade_angles[i] = GLfloat(0.0);
			blade_speed[i] = 0.0;
		}
		
		ifstream fin;
		fin.open(filename);
		
		if (fin.is_open()){

			int i=0;
			fin >> num_points;
			
			points = new vec2[num_points];
			indices = new vec3[num_points/3];
			
			for(int j=0; j<num_points; j+=3)
				indices[j] = vec3(j, j+1, j+2);
			
			fin >> body.position.x;
			fin >> body.position.y;
			fin >> body.color.x;
			fin >> body.color.y;
			fin >> body.color.z;
			fin >> body.color.w;
			fin >> body.num_triangles;
			body.index = i;
			
			for(int j=0; j<body.num_triangles; j++){
				for(int q=0; q<3; q++){
					fin >> points[i].x;
					fin >> points[i].y;
					i++;
				}
			}
			
			
			for(int j=0; j<4; j++){
				fin >> arms[j].position.x;
				fin >> arms[j].position.y;
				fin >> arms[j].color.x;
				fin >> arms[j].color.y;
				fin >> arms[j].color.z;
				fin >> arms[j].color.w;
				fin >> arms[j].num_triangles;
				arms[j].index = i;
				for(int n=0; n<arms[j].num_triangles; n++){
					for(int q=0; q<3; q++){
						fin >> points[i].x;
						fin >> points[i].y;
						i++;
					}
				}
			}
			for(int j=0; j<4; j++){
				fin >> blades[j].position.x;
				fin >> blades[j].position.y;
				fin >> blades[j].color.x;
				fin >> blades[j].color.y;
				fin >> blades[j].color.z;
				fin >> blades[j].color.w;
				fin >> blades[j].num_triangles;
				blades[j].index = i;
				for(int n=0; n<blades[j].num_triangles; n++){
					for(int q=0; q<3; q++){
						fin >> points[i].x;
						fin >> points[i].y;
						i++;
					}
				}
			}
			
			fin.close();

		} else {

			cout << "Unable to open file\n"; 

		}
		
		fin.close();
		
	};
	
	void update(double dt){
		position += velocity*dt;
		velocity += acceleration*dt;
		
		angle += angle_velocity*dt;
		angle_velocity += angle_velocity*dt;
		
		for(int i=0; i<4; i++){
			blade_angles[i] += static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
		
	};
	
	void render(){
	
		glUniform2f(windowSizeLoc, wh, ww);
		glUniform1f(sizeLoc, scale);
		glUniform1f(quadcopterRotationLoc, angle);
		glUniform2f(quadcopterPositionLoc, position.x, position.y);
		
		glUniform1f(rotationLoc, 0);
		
		glUniform4f(colorLoc, body.color.x, body.color.y, body.color.z, body.color.w);
		glUniform2f(positionLoc, body.position.x, body.position.y);
		
		glDrawArrays(GL_TRIANGLES, body.index, body.num_triangles);
		
		for(int i=0; i<4; i++){
			glUniform4f(colorLoc, arms[i].color.x, arms[i].color.y, arms[i].color.z, arms[i].color.w);
			glUniform2f(positionLoc, arms[i].position.x, arms[i].position.y);
			glDrawArrays(GL_TRIANGLES, arms[i].index, arms[i].num_triangles);
		}
		for(int i=0; i<4; i++){
			glUniform1f(rotationLoc, blade_angles[i]);
			glUniform4f(colorLoc, blades[i].color.x, blades[i].color.y, blades[i].color.z, blades[i].color.w);
			glUniform2f(positionLoc, blades[i].position.x, blades[i].position.y);
			glDrawArrays(GL_TRIANGLES, blades[i].index, blades[i].num_triangles);
		}
	
	};
};

Quadcopter quadcopter(vec2(0,0), 10,"quadcopter.data");

// The only required callback, it must draw everything when called.
extern "C" void displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	quadcopter.render();
}

void update(long double t, long double dt){
	
	quadcopter.acceleration.x = 0;
	quadcopter.acceleration.y = 0;
	quadcopter.angle_acceleration = 0;
	
	
	if(controller[S] && controller[W])
		quadcopter.acceleration.y = 0;
	else if(controller[W])
		quadcopter.acceleration.y = 1;
	else if(controller[S])
		quadcopter.acceleration.y = -1;
		
	if(controller[D] && controller[A])
		quadcopter.acceleration.x = 0;
	else if(controller[D])
		quadcopter.acceleration.x = 1;
	else if(controller[A])
		quadcopter.acceleration.x = -1;
	
	if(controller[LEFT] && controller[RIGHT])
		quadcopter.angle_acceleration = 0.0;
	else if(controller[LEFT])
		quadcopter.angle_acceleration = 1;
	else if(controller[RIGHT])
		quadcopter.angle_acceleration = -1;
	
	
	quadcopter.update(dt);
}

timeval current_t;

extern "C" void gameLoopCallback(){
	std::cout << std::fixed;
  std::cout << std::setprecision(20);

	static timeval new_t;	

	static double t = 0.0;
	static const double dt = 1000.0/ticks_per_second;
	
	
	static double accumulator = 0.0;
	
	//Accumulates time between frame renders;
	static double r_accumulator = 0.0;
	
	static double r_dt = 1000.0/max_fps;
	

	gettimeofday(&new_t,NULL);

	double frame_t = (new_t.tv_usec - current_t.tv_usec);
	
	current_t = new_t;
	if(frame_t > 0){
		accumulator += frame_t;
		r_accumulator += frame_t;
	}
	//Update loop;
	while(accumulator >= dt){
		update(t,dt);
		accumulator-=dt;
		t+= dt;
	}
	if(r_accumulator >= r_dt){

		displayCallback();
		//Get rid of any extra time in the render accumulator
		//This avoids extra rendering after a slowdown
		r_accumulator = fmod(r_accumulator, r_dt);
	}
	
	
}

extern "C" void keysDownCallback(unsigned char k, int xx, int yy)
{
	switch(k){
		case 'w':
			controller[W] = true;
		break;
		case 'a':
			controller[A] = true;
		break;
		case 's':
			controller[S] = true;
		break;
		case 'd':
			controller[D] = true;
		break;
	}
}
extern "C" void keysUpCallback(unsigned char k, int xx, int yy)
{
	switch(k){
		case 'w':
			controller[W] = false;
		break;
		case 'a':
			controller[A] = false;
		break;
		case 's':
			controller[S] = false;
		break;
		case 'd':
			controller[D] = false;
		break;
	}
}

// Special Keys events.
// This one only responds to the up arrow key.
extern "C" void specialKeysDownCallback(int k, int xx, int yy)
{
	switch(k){
		case GLUT_KEY_UP:
			controller[UP] = true;
		break;
		case GLUT_KEY_DOWN:
			controller[DOWN] = true;
		break;
		case GLUT_KEY_LEFT:
			controller[LEFT] = true;
		break;
		case GLUT_KEY_RIGHT:
			controller[RIGHT] = true;
		break;
	}
}

extern "C" void specialKeysUpCallback(int k, int xx, int yy)
{
	switch(k){
		case GLUT_KEY_UP:
			controller[UP] = false;
		break;
		case GLUT_KEY_DOWN:
			controller[DOWN] = false;
		break;
		case GLUT_KEY_LEFT:
			controller[LEFT] = false;
		break;
		case GLUT_KEY_RIGHT:
			controller[RIGHT] = false;
		break;
	}
}

void myInit(){
	cout << "myInit\n";
	//initializing time used in game loop function
	gettimeofday(&current_t,NULL);
	
	
	
	//glutInitWindowPosition(100,100);
	//glutInitWindowSize(ww,wh);
	glutInitWindowSize(ww,wh);
	glutCreateWindow("Quadcopter");
	glutInitDisplayMode(GLUT_RGBA);
	
	// Color initializations
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glutDisplayFunc(displayCallback);
	glutIdleFunc(gameLoopCallback);
	
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keysDownCallback);
	glutKeyboardUpFunc(keysUpCallback);
	glutSpecialFunc(specialKeysDownCallback);
	glutSpecialFunc(specialKeysUpCallback);
}

void init()
{
	cout << "init\n";
	// Create a vertex array object on the GPU
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Create and initialize a buffer object for transferring data to
	// the GPU.

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(quadcopter.points),quadcopter.points,GL_STATIC_DRAW);

	cout << "Points loaded from file: ";
	std::cout << std::fixed;
  std::cout << std::setprecision(2);
  
	for(int i=0; i< quadcopter.num_points; i++){
		cout << quadcopter.points[i] << " ";
		if((i+1) % 6 == 0)
			cout << "\n";
	}
	cout << "\n";
	
	
	
	
	GLuint program = InitShader("vshaderHw1.glsl", "fshaderHw1.glsl");
	glUseProgram(program);
	
	windowSizeLoc = glGetUniformLocation(program, "windowSize");
	sizeLoc  = glGetUniformLocation(program, "size");
	colorLoc  = glGetUniformLocation(program, "color");
	positionLoc  = glGetUniformLocation(program, "position");
	rotationLoc  = glGetUniformLocation(program, "rotation");
	quadcopterRotationLoc  = glGetUniformLocation(program, "quadcopterRotation");
	quadcopterPositionLoc  = glGetUniformLocation(program, "quadcopterPosition");
	
	if(windowSizeLoc < 0){
		cout << "Can't find uniform windowSizeLoc\n";
	}
	if(sizeLoc < 0){
		cout << "Can't find uniform sizeLoc\n";
	}
	
	if(colorLoc < 0){
		cout << "Can't find uniform colorLoc\n";
	}
	
	if(positionLoc < 0){
		cout << "Can't find uniform positionLoc\n";
	}
	
	if(rotationLoc < 0){
		cout << "Can't find uniform rotationLoc\n";
	}
	
	if(quadcopterRotationLoc < 0){
		cout << "Can't find uniform windowSizeLoc\n";
	}
	
	if(quadcopterPositionLoc < 0){
		cout << "Can't find uniform quadcopterPositionLoc";
	}
	
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	
}

int main(int argc, char** argv)
{
	cout << "main\n";
	                          // set window attributes, and initial data
	
	glutInit(&argc,argv);
	myInit();
	// Initialize the "magic" that glues all the code together.
	glewInit();
	
	init();               // set up shaders and display environment
	
	glutMainLoop();
	
	return(EXIT_SUCCESS); // return successful exit code
}
