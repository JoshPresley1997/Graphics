#include "InitialState.h"
#include "TestState2.h"
#include "Application.h"

//controls how fast the look speed is. increase to turn faster.
const float MOUSE_SPEED = 0.05f;

//constructor just calls the parent class constructor.
InitialState::InitialState(Application* app): GameState(app)
{
}

//initialises this state
bool InitialState::Init()
{	
	SDL_ShowCursor(0);
	glClearColor(1, 1, 1, 1);
	this->shader = new Shader("object_shader.vert", "object_shader.frag");
	//this->textureShader = new Shader("texture_shader.vert", "texture_shader.frag");
	
	this->shader->Use();
	//this->testShape = new Shape(this->shader);	
	this->room = new RoomCube(this->shader);
	this->camera = new Camera(this->shader, 640, 480);
	this->camRotation = glm::vec3(0, 0, 0);
	
	SDL_WarpMouseGlobal(950, 540);	
	this->camVelocity = glm::vec3(0.1f, 0.1f, 0.1f);
	
	return true;
}



//While the program is running, this method is called so that 
bool InitialState::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//handle any input from the user
	this->Move();
	//redraw as necessary
	this->CreateShapes();
	//redraw the room
	this->room->Draw();
	//finally, update the camera to accurately display the room
	this->camera->Update();
	return true;
}

//Creates a list of shapes using vertex and edge data and draws them to the screen.
void InitialState::CreateShapes()
{
	//make sure the shader is in use
	this->shader->Use();
	this->camera->SetShader(this->shader);
	Shape * wallFrontLeft;
	Shape * wallFrontRight;
	Shape * wallRear;
	Shape * wallLeft;
	Shape * wallRight;
	Shape * wallRoof;
	//these shapes have been separated for readability.
	//technically, the Shape class could draw any set of vertices so long as it is provided with edge data 
	//color data, light data

	//these are the sizes when drawing cubes, which the walls will be
	size_t sizeV = 72;
	size_t sizeE = 36;

	//this will stay the same for the rectanguloids
	GLuint eData[] = {
		0, 1, 2,
		2, 3, 0, //front wall

		4, 5, 6,
		6, 7, 4, //back wall

		4, 0, 3,
		3, 7, 4, //left wall

		1, 5, 6,
		6, 2, 1, // right wall

		2, 6, 7,
		7, 3, 2,  // floor 

		0, 4, 5,
		5, 1, 0 //ceiling
	};

	//the below sets of vertices will create shapes.
	//the color of the ambient light is set in each shape.
	//it probably should be separated and loaded as it's own 
	//array for efficiency but for this small scene it's easier to 
	//do here
	//the intensity of the light is set in the shader.
		//vertex data			//color data			//light data
	GLfloat vData[] = {
		0.5f, 0.5f, 0.0f,		1.0f, 0.8f, 1.0f,		0.5f, 0.5f, 0.5f,		//top-left-front 0 
		2.5f, 0.5f, 0.0f,		1.0f, 0.8f, 1.0f,		0.5f, 0.5f, 0.5f,	//top-right-front 1
		2.5f, -0.5f, 0.0f,		1.0f, 0.8f, 1.0f,		0.5f, 0.5f, 0.5f,	//bottom-right-front 2
		0.5f, -0.5f, 0.0f,		1.0f, 0.8f, 1.0f,		0.5f, 0.5f, 0.5f,	//bottom-left-front 3

		0.5f, 0.5f, -0.5f,		1.0f, 0.8f, 1.0f,		0.5f, 0.5f, 0.5f,	//top-left-back 4
		2.5f, 0.5f, -0.5f,		1.0f, 0.8f, 1.0f,		0.5f, 0.5f, 0.5f,	//top-right-back 5 
		2.5f, -0.5f, -0.5f,		1.0f, 0.8f, 1.0f,		0.5f, 0.5f, 0.5f,	//bottom-right-back 6
		0.5f, -0.5f, -0.5f,		1.0f, 0.8f, 1.0f,		0.5f, 0.5f, 0.5f,	//bottom-left-back 7

	};

	wallFrontRight = new Shape(this->shader, vData, eData, sizeV, sizeE);
	wallFrontRight->Draw();

	GLfloat vData1[] = {
		1.2f, 0.5f, -0.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-left-front 0 
		2.5f, 0.5f, -0.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-right-front 1
		2.5f, -0.5f, -0.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-right-front 2
		1.2f, -0.5f, -0.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-left-front 3

		1.2f, 0.5f, -2.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-left-back 4
		2.5f, 0.5f, -2.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-right-back 5 
		2.5f, -0.5f, -2.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-right-back 6
		1.2f, -0.5f, -2.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-left-back 7

	};
	wallRight = new Shape(this->shader, vData1, eData, sizeV, sizeE);
	wallRight->Draw();


	GLfloat vData2[] = {
		-2.5f, 0.5f, 0.0f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-left-front 0 
		-0.5f, 0.5f, 0.0f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-right-front 1
		-0.5f, -0.5f, 0.0f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-right-front 2
		-2.5f, -0.5f, 0.0f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-left-front 3

		-2.5f, 0.5f, -0.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-left-back 4
		-0.5f, 0.5f, -0.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-right-back 5 
		-0.5f, -0.5f, -0.5f,	1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-right-back 6
		-2.5f, -0.5f, -0.5f,	1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-left-back 7

	};
	wallFrontLeft = new Shape(this->shader, vData2, eData, sizeV, sizeE);
	wallFrontLeft->Draw();

	GLfloat vData3[] = {
		-1.2f, 0.5f,-0.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,//top-left-front 0 
		-2.5f, 0.5f, -0.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-right-front 1
		-2.5f, -0.5f, -0.5f,	1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-right-front 2
		-1.2f, -0.5f,-0.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-left-front 3

		-1.2f, 0.5f, -2.5f,		0.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-left-back 4
		-2.5f, 0.5f, -2.5f,		1.0f, 0.5f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-right-back 5 
		-2.5f, -0.5f, -2.5f,	1.0f, 0.0f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-right-back 6
		-1.2f, -0.5f, -2.5f,	1.0f, 0.2f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-left-back 7

	};
	wallLeft = new Shape(this->shader, vData3, eData, sizeV, sizeE);
	wallLeft->Draw();

	GLfloat vData4[] = {
		-2.5f, 0.5f, -2.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-left-front 0 
		2.5f, 0.5f, -2.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-right-front 1
		2.5f, -0.5f, -2.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-right-front 2
		-2.5f, -0.5f, -2.5f,	1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-left-front 3

		-2.5f, 0.5f, -2.8f,		0.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-left-back 4
		2.5f, 0.5f, -2.8f,		1.0f, 0.5f, 1.0f,	0.5f, 0.5f, 0.5f,	//top-right-back 5 
		2.5f, -0.5f, -2.8f,		1.0f, 0.0f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-right-back 6
		-2.5f, -0.5f, -2.8f,	1.0f, 0.2f, 1.0f,	0.5f, 0.5f, 0.5f,	//bottom-left-back 7

	};
	wallRear = new Shape(this->shader, vData4, eData, sizeV, sizeE);
	wallRear->Draw();

	GLfloat vData5[] = {
		-2.5f, 0.5f, 0.0f,		0.1f, 0.5f, 0.3f,	0.5f, 0.5f, 0.5f,	//top-left-front-0
		2.5f, 0.5f, 0.0f,		0.2f, 0.3f, 0.2f,	0.5f, 0.5f, 0.5f,	//top-right-front-1
		-2.5f, 0.5f, -2.8f,		0.3f, 0.9f, 0.6f,	0.5f, 0.5f, 0.5f,	//back-left-front-2
		2.5f, 0.5f, -2.8f,		0.4f, 0.4f, 0.7f,	0.5f, 0.5f, 0.5f,	//back-right-front-3
		0.0f, 2.5f, -1.4,		0.6f, 0.1f, 0.2f,	0.5f, 0.5f, 0.5f,	//point-5
	};
	
	GLuint eData1[] = {
		0, 1, 4,
		0, 2, 4,
		1, 3, 4,
		2, 3, 4
	};
	
	size_t sizeV1 = 45;
	size_t sizeE1 = 12;


	wallRoof = new Shape(this->shader, vData5, eData1, sizeV1, sizeE1);
	wallRoof->Draw();

		//position				//color				//light color		//uv for texture
	GLfloat vData6[] = {
		-2.5f, -0.5f, -2.5f,	1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	0.0f, 0.0f, //top-left-front 0 
		2.5f, -0.5f, -2.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	1.0f, 0.0f, //top-right-front 1
		2.5f, -0.5f, -2.5f,		1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	1.0f, 1.0f, //bottom-right-front 2
		-2.5f, -0.5f, -2.5f,	1.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	0.0f, 1.0f, //bottom-left-front 3

		-2.5f, -0.5f, -2.8f,	0.0f, 0.8f, 1.0f,	0.5f, 0.5f, 0.5f,	0.0f, 0.0f, //top-left-back 4
		2.5f, -0.5f, -2.8f,		1.0f, 0.5f, 1.0f,	0.5f, 0.5f, 0.5f,	1.0f, 0.0f, //top-right-back 5 
		2.5f, -0.5f, -2.8f,		1.0f, 0.0f, 1.0f,	0.5f, 0.5f, 0.5f,	1.0f, 1.0f, //bottom-right-back 6
		-2.5f, -0.5f, -2.8f,	1.0f, 0.2f, 1.0f,	0.5f, 0.5f, 0.5f,	0.0f, 1.0f, //bottom-left-back 7

	};
	//done drawing all the shapes here.

	//below was an attempt at texturing but it kept crashing
	/*this->textureShader->Use();
	this->camera->SetShader(textureShader);
	size_t sizetv = 88;
	TexturedShape* floor = new TexturedShape(this->textureShader, vData6, eData, sizetv, sizeE);
	floor->Draw();*/
	
	

}


//handles movement and mouse input
void InitialState::Move()
{
	//gets the keypress.
	const uint8_t* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A])
	{
		//we want to move in the direction we are looking. this means
		//we need the cos of the angle for x
		//and the sin of the angle for y.
		//all below buttons follow this with minor adjustment
		this->camera->Translate(this->camVelocity.x * cos(glm::radians(this->camRotation.y))
			, 0
			, this->camVelocity.z * sin(glm::radians(this->camRotation.y)));
	}
	if (state[SDL_SCANCODE_D])
	{
		this->camera->Translate(-this->camVelocity.x * cos(glm::radians(this->camRotation.y))
			, 0
			, -this->camVelocity.z * sin(glm::radians(this->camRotation.y)));
	}

	//cos(0) = 1, cos(90) = 0, cos (180) = -1, cos(270) = 0, cos(360) = 0
	if (state[SDL_SCANCODE_W])
	{
		this->camera->Translate(-this->camVelocity.x * sin(glm::radians(this->camRotation.y))
			, 0
			, this->camVelocity.z * cos(glm::radians(this->camRotation.y)));
	}
	if (state[SDL_SCANCODE_S])
	{
		this->camera->Translate(this->camVelocity.x * sin(glm::radians(this->camRotation.y))
			, 0
			, -this->camVelocity.z * cos(glm::radians(this->camRotation.y)));
	}


	//grab the mouse position and subtract it from the current rotation
	int xPos, yPos;
	SDL_GetGlobalMouseState(&xPos, &yPos);
	camRotation.y -= MOUSE_SPEED * float(500 - xPos);
	camRotation.x -= MOUSE_SPEED * float(500 - yPos);
	SDL_WarpMouseGlobal(500, 500); //reset the mouse so you don't fly all over the room


	//reset the camera if you get lost
	if (state[SDL_SCANCODE_SPACE])
	{
		this->camera->SetTranslation(0, 0, -2);
		this->camera->SetRotation(0, 0, 0, -2);
		this->camRotation.x = 0;
		this->camRotation.y = 0;
		this->camRotation.z = 0;

	}


	this->camera->SetRotation(0, 1, 1, 1);
	this->camera->Rotate(camRotation.x, 1, 0, 0); //make sure you rotate along the correct axis
	this->camera->Rotate(camRotation.y, 0, 1, 0);

}
//free the memory
bool InitialState::Destroy()
{
	
	delete this->shader;
	return true;
}

InitialState::~InitialState()
{
	delete this->shader;
}
