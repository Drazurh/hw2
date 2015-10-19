using namespace std;

enum controls {LEFT,RIGHT,UP,DOWN,W,A,S,D};

bool controller[8] = {false};

extern "C" void gameLoopCallback(){
	
	static const int dt = 20;
	
	static int current_t = 0;
	
	int new_t = glutGet(GLUT_ELAPSED_TIME);
	
	static int accumulator = 0;
	
	int frame_t = new_t - current_t;
	
	current_t = new_t;	
	accumulator += frame_t;
	while(accumulator >= dt){
		update(t,dt);
		accumulator-=dt;
		t+= dt;
	}
	displayCallback();
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
	
	
	//glutInitDisplayMode (GLUT_DEPTH | GLUT_ACCUM | GLUT_RGB);
	//glutInitWindowPosition(100,100);
	//glutInitWindowSize(ww,wh);
	glutInitWindowSize(100,100);
	glutCreateWindow("TEST");
	
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
	// Create a vertex array object on the GPU
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Create and initialize a buffer object for transferring data to
	// the GPU.
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadcopter.points), quadcopter.points, GL_STATIC_DRAW);
	
	
	GLuint program = InitShader("vshaderHw1.glsl", "fshaderHw1.glsl");
	
	windowSizeLoc = glGetUniformLocation(program, "windowSize");
	sizeLoc  = glGetUniformLocation(program, "size");
	colorLoc  = glGetUniformLocation(program, "color");
	positionLoc  = glGetUniformLocation(program, "position");
	rotationLoc  = glGetUniformLocation(program, "rotation");
	quadcopterRotationLoc  = glGetUniformLocation(program, "quadcopterRotation");
	quadcopterPositionLoc  = glGetUniformLocation(program, "quadcopterPosition");
	
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	
}

int main(int argc, char** argv)
{
	             // set window attributes, and initial data
	glutInit(&argc,argv);

	// Initialize the "magic" that glues all the code together.
	glewInit();
	
	myInit();
	init();               // set up shaders and display environment
	
	glutMainLoop();
	
	return(EXIT_SUCCESS); // return successful exit code
}