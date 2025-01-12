#include "Graphics\window.h"
#include "Camera\camera.h"
#include "Shaders\shader.h"
#include "Model Loading\mesh.h"
#include "Model Loading\texture.h"
#include "Model Loading\meshLoaderObj.h"






// variables for player controls
glm::vec3 playerPos = glm::vec3(-5.0f, 11.0f, -5.0f);
float playerSpeed = 0.1f;
float playerAngle = 0.0f;





float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Window window("Game Engine", 800, 800);
Camera camera(glm::vec3(25.0f, -10.0f, 25.0f));		// pozitia camerei

glm::vec3 lightColor = glm::vec3(1.0f);
glm::vec3 lightPos = glm::vec3(-180.0f, 100.0f, -200.0f);




// variables for camera perspective
//glm::vec3 thrid_person_offset = glm::vec3(0.0f, -10.0f, -10.0f);	// VEZI: constructorul, cameraPosition
float distanceFromCube = 10.0f;
float heightAboveCube = 5.0f;

float cameraControlMultiplier = 1.5f;


//////// AXA Y E NEGATIVA IN JOS /////// (-9 e mai sus decat -11)


// variabile din 2D

bool jumping = 0;
bool whipping = 0;	// bici in mana/lansat
bool swinging = 0;	// barna
bool dead = 0;


//jump stuff
float deltaJumpTime = 0.0f;
float firstJumpFrame = 0.0f;
float shortjumpDuration = 1.0f;		// seconds
float longjumpDuration = 2.7f;		// seconds
float jumpDuration = shortjumpDuration;
float jumpHeight = 5.0f;
float initialJumpHeight = 0.0f;

float razaBiciului = 0.5f;
float swingDuration = 1.0f; // seconds

const float gravity = 0.02f;

bool collisionCheckREPLACEME = 1;







class Obiect
{

// HITBOX SI CHESTII GENERALE

	// hitboxul o sa fie un mesh facut din rectangle-uri si poti sa il lasi asa daca nu vrei un model anume (e.g. pentru pereti)
	// daca vrei un model anume, mesh-ul hitboxului nu o sa fie randat, o sa fie randat numai meshul din argument

	// nume ID unic
	int Obiect_id;
	// pozitia coltului din: stanga, jos, front
	glm::vec3 position;
	// marime: width, height, depth
	glm::vec3 size;

	std::vector<Vertex> vertices;

// MESH -- va primi fie valoarea marginilor hitboxului, fie mesh-ul specific din argument, i.f.s.d. constructor
	Mesh mesh;
	// or sa trebuiasca si offseturi si rotatii si scalari pt asta... doar inregistreaza-le in niste variabile,
	// le ajustezi in constructor, si le transmiti sa fie facute in rendering loop


	// Rotation angles in radians
	glm::vec3 rotation;

// TEXTURA
	std::vector<Texture> textura;

// SHADERE (optional?)
	//



public:

	// pentru mesh-ul hitbox-ului cu textura peste
	Obiect(int id, glm::vec3 auxposition, glm::vec3 auxsize, std::vector<Texture> textura)
	{
		Obiect_id = id;
		position = auxposition;
		size = auxsize;


/*
		// "compile" all vertices and indices of defined objects:
			// retrieve the x and y coords of the top left corner
		float tl_x = position.x;
		float tl_y = position.y;

		// compute the other 3 corners using the size and
		// insert them into the vertices array in the following order: TR, BR, BL, TL
		float width = size.x;
		float height = size.y;



		// BR
		vertices[0] = tl_x + width;  // x
		vertices[1] = tl_y;          // y
		vertices[2] = 0.0f;          // z

		// TR
		vertices[3] = tl_x + width;  // x
		vertices[4] = tl_y + height; // y
		vertices[5] = 0.0f;          // z

		// TL
		vertices[6] = tl_x;         // x
		vertices[7] = tl_y + height;// y
		vertices[8] = 0.0f;         // z

		// BL
		vertices[9] = tl_x;         // x
		vertices[10] = tl_y;         // y
		vertices[11] = 0.0f;         // z

		// Define indices for two triangles that form the rectangle
		indices[0] = 0; // BR // 0
		indices[1] = 3; // BL // 3
		indices[2] = 2; // TL // 2

		indices[3] = 1; // TR
		indices[4] = 0; // BR
		indices[5] = 2; // TL
*/


		float x = position.x;
		float y = position.y;
		float z = position.z;

		float w = size.x;
		float h = size.y;
		float d = size.z;

		if(Obiect_id == 0)
			std::cout << "player y: " << playerPos.y << " | player y + h: " << playerPos.y + h << std::endl;

		std::cout << Obiect_id << ": " << std::endl;
		std::cout << y << std::endl;
		std::cout << y + h << std::endl;
		std::cout << std::endl;

		std::vector<Vertex> vertices = {

			// Front face
			Vertex(x,       y,       z + d,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f),
			Vertex(x + w,   y,       z + d,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f),
			Vertex(x + w,   y + h,   z + d,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f),
			Vertex(x,       y + h,   z + d,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f),

			// Back face
			Vertex(x,       y,       z,      0.0f, 0.0f, -1.0f,  1.0f, 0.0f),
			Vertex(x + w,   y,       z,      0.0f, 0.0f, -1.0f,  0.0f, 0.0f),
			Vertex(x + w,   y + h,   z,      0.0f, 0.0f, -1.0f,  0.0f, 1.0f),
			Vertex(x,       y + h,   z,      0.0f, 0.0f, -1.0f,  1.0f, 1.0f),

			// Left face
			Vertex(x,       y,       z,      -1.0f, 0.0f, 0.0f,  0.0f, 0.0f),
			Vertex(x,       y,       z + d,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f),
			Vertex(x,       y + h,   z + d,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f),
			Vertex(x,       y + h,   z,      -1.0f, 0.0f, 0.0f,  0.0f, 1.0f),

			// Right face
			Vertex(x + w,   y,       z,      1.0f, 0.0f, 0.0f,   0.0f, 0.0f),
			Vertex(x + w,   y,       z + d,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f),
			Vertex(x + w,   y + h,   z + d,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f),
			Vertex(x + w,   y + h,   z,      1.0f, 0.0f, 0.0f,   0.0f, 1.0f),

			// Top face
			Vertex(x,       y + h,   z,      0.0f, 1.0f, 0.0f,   0.0f, 0.0f),
			Vertex(x + w,   y + h,   z,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f),
			Vertex(x + w,   y + h,   z + d,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f),
			Vertex(x,       y + h,   z + d,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f),

			// Bottom face
			Vertex(x,       y,       z,      0.0f, -1.0f, 0.0f,  0.0f, 0.0f),
			Vertex(x + w,   y,       z,      0.0f, -1.0f, 0.0f,  1.0f, 0.0f),
			Vertex(x + w,   y,       z + d,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f),
			Vertex(x,       y,       z + d,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f)
		};

		std::vector<int> indices = {

			// Front face
			0, 1, 2, 2, 3, 0,
			// Back face
			4, 5, 6, 6, 7, 4,
			// Left face
			8, 9, 10, 10, 11, 8,
			// Right face
			12, 13, 14, 14, 15, 12,
			// Top face
			16, 17, 18, 18, 19, 16,
			// Bottom face
			20, 21, 22, 22, 23, 20

		};

/*
		std::vector<int> indices = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3
		};
*/

		// Create the Mesh object for the cube
		mesh = Mesh(vertices, indices, textura);

/*
		// hitbox loading
		vert.push_back(Vertex());
		vert[0].pos = glm::vec3(10.5f, 10.5f, 0.0f);
		vert[0].textureCoords = glm::vec2(1.0f, 1.0f);

		vert.push_back(Vertex());
		vert[1].pos = glm::vec3(10.5f, -10.5f, 0.0f);
		vert[1].textureCoords = glm::vec2(1.0f, 0.0f);

		vert.push_back(Vertex());
		vert[2].pos = glm::vec3(-10.5f, -10.5f, 0.0f);
		vert[2].textureCoords = glm::vec2(0.0f, 0.0f);

		vert.push_back(Vertex());
		vert[3].pos = glm::vec3(-10.5f, 10.5f, 0.0f);
		vert[3].textureCoords = glm::vec2(0.0f, 1.0f);

		vert[0].normals = glm::normalize(glm::cross(vert[1].pos - vert[0].pos, vert[3].pos - vert[0].pos));
		vert[1].normals = glm::normalize(glm::cross(vert[2].pos - vert[1].pos, vert[0].pos - vert[1].pos));
		vert[2].normals = glm::normalize(glm::cross(vert[3].pos - vert[2].pos, vert[1].pos - vert[2].pos));
		vert[3].normals = glm::normalize(glm::cross(vert[0].pos - vert[3].pos, vert[2].pos - vert[3].pos));

		Mesh mesh(vert, ind, textura);*/
	}

	// pentru mesh in argument si hitbox transparent
	//

	// pentru obiect cu shadere?
	//



	Mesh getMesh()
	{
		return mesh;
	}

	int getID()
	{
		return Obiect_id;
	}

	glm::vec3 getPosition()
	{
		return position;
	}

	glm::vec3 getSize()
	{
		return size;
	}

	void setPosition(glm::vec3 newpos)
	{
		position = newpos;
	}

	/*
	void setRotation(glm::vec3 newrot)
	{
		rotation = newrot;

		// Create rotation matrices for each axis
		glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), radians.x, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), radians.y, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), radians.z, glm::vec3(0.0f, 0.0f, 1.0f));

		// Combine rotations (order matters)
		glm::mat4 rotationMatrix = rotationZ * rotationY * rotationX;

		for (auto& vertex : vertices) {
			glm::vec4 pos = glm::vec4(vertex.pos, 1.0f);	// Convert to 4D vector
			pos = rotationMatrix * pos;                     // Apply rotation
			vertex.pos = glm::vec3(pos);               // Convert back to 3D vector
		}
	}
	*/
};

// aici tinem toate obiectele pe care le randam, simulam, etc
std::vector<Obiect> vector_obiecte;


// obiectul player e tinut la id 0, pozitia 0

// ca sa poti sa cauti in vectoru de obiecte dupa id
Obiect* getObiectByID(int id)
{
	for (int i = 0; i < vector_obiecte.size(); i++)
	{
		if (vector_obiecte.at(i).getID() == id)
		{
			return &(vector_obiecte.at(i));
		}
	}
}
// DE STERS? ca poti sa le iei direct din vector












void processKeyboardInput();
void processPlayerMovement();
bool checkPlayerCollision(std::vector<Obiect>& vector_obiecte);
bool isColliding(Obiect& a, Obiect& b);













int main()
{
	glClearColor(0.2f, 0.8f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	// Compiling shader program
	Shader shader("Shaders/vertex_shader.glsl", "Shaders/fragment_shader.glsl");
	Shader sunShader("Shaders/sun_vertex_shader.glsl", "Shaders/sun_fragment_shader.glsl");



// Textures

	GLuint tex = loadBMP("Resources/Textures/wood.bmp");
	GLuint tex2 = loadBMP("Resources/Textures/rock.bmp");
	GLuint tex3 = loadBMP("Resources/Textures/orange.bmp");

	std::vector<Texture> textures;
	textures.push_back(Texture());
	textures[0].id = tex;
	textures[0].type = "texture_diffuse";

	std::vector<Texture> textures2;
	textures2.push_back(Texture());
	textures2[0].id = tex2;
	textures2[0].type = "texture_diffuse";

	std::vector<Texture> textures3;
	textures3.push_back(Texture());
	textures3[0].id = tex3;
	textures3[0].type = "texture_diffuse";



// Meshes

	MeshLoaderObj loader;
	Mesh sun = loader.loadObj("Resources/Models/sphere.obj");
	Mesh suz = loader.loadObj("Resources/Models/suzanne.obj", textures);
	Mesh plane = loader.loadObj("Resources/Models/plane1.obj", textures2);
	Mesh playercube = loader.loadObj("Resources/Models/cube.obj");







// Obiecte

	// daca nu incepe playerul la -20 se buleste absolut tot legat de coliziunile pe Y
	// daca nu incepe de la x=0 si z=0, se strica de la offsetul din clasa de camera (dar nu stau sa-l automatizez)
	vector_obiecte.push_back(Obiect(0, glm::vec3(0.0f, -20.0f, 0.0f), glm::vec3(3.0f, 10.0f, 3.0f), textures3));
	vector_obiecte.push_back(Obiect(1, glm::vec3(-30.0f, 0.0f, -30.0f), glm::vec3(70.0f, 10.0f, 70.0f), textures));
	vector_obiecte.push_back(Obiect(2, glm::vec3(20.0f, -30.0f, 20.0f), glm::vec3(10.0f, 70.0f, 30.0f), textures2));


	vector_obiecte.push_back(Obiect(10, glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(52.0f, 20.0f, 4.0f), textures2));
	vector_obiecte.push_back(Obiect(11, glm::vec3(48.0f, 10.0f, 5.0f), glm::vec3(4.0f, 20.0f, 28.0f), textures2));
	vector_obiecte.push_back(Obiect(12, glm::vec3(10.0f, 10.0f, 19.0f), glm::vec3(38.0f, 20.0f, 4.0f), textures2));
	vector_obiecte.push_back(Obiect(13, glm::vec3(5.0f, 10.0f, 10.0f), glm::vec3(38.0f, 20.0f, 4.0f), textures2));
	vector_obiecte.push_back(Obiect(14, glm::vec3(0.0f, 10.0f, 5.0f), glm::vec3(5.0f, 20.0f, 47.0f), textures2));
	vector_obiecte.push_back(Obiect(15, glm::vec3(10.0f, 10.0f, 25.0f), glm::vec3(5.0f, 20.0f, 20.0f), textures2));











// Rendering loop
	//check if we close the window or press the escape button
	while (!window.isPressed(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(window.getWindow()) == 0)
	{
		window.clear();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processKeyboardInput();

		processPlayerMovement();
	/*
		//test mouse input
		if (window.isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			std::cout << "Pressing mouse button" << std::endl;
		}
	*/





		 //// Code for the light ////

		sunShader.use();

		glm::mat4 ProjectionMatrix = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 10000.0f);
		glm::mat4 ViewMatrix = glm::lookAt(camera.getCameraPosition(), camera.getCameraPosition() + camera.getCameraViewDirection(), camera.getCameraUp());



		GLuint MatrixID = glGetUniformLocation(sunShader.getId(), "MVP");

		//Test for one Obj loading = light source

		glm::mat4 ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, lightPos);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		sun.draw(sunShader);

		//// End code for the light ////

		shader.use();









		// rendering for objects, i.e. not for player, with id==0
		for (int v = 1; v < vector_obiecte.size(); v++)
		{
			vector_obiecte.at(v).getMesh().draw(shader);
		}



		GLuint MatrixID2 = glGetUniformLocation(shader.getId(), "MVP");
		GLuint ModelMatrixID = glGetUniformLocation(shader.getId(), "model");

// player mesh

		ModelMatrix = glm::mat4(1.0);
		// translate according to where the controls have moved the player
		ModelMatrix = glm::translate(ModelMatrix, playerPos);
		// rotate according to the angle given by controls
		ModelMatrix = glm::rotate(ModelMatrix, playerAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		vector_obiecte.at(0).getMesh().draw(shader);










		///// Test Obj files for suz ////

		for (int i = 0; i < 3; i++)
		{
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(10.0f * i, 0.0f, 10.0f * i));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
			glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
			glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
			glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

			suz.draw(shader);
		}



		///// plane Obj file //////


		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -20.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);


		//plane.draw(shader);

		window.update();
	}

}








// collision between any 2 objects
bool isColliding(Obiect& a, Obiect& b)
{
	// check for overlap along each axis	
	bool xOverlap = (a.getPosition().x < b.getPosition().x + b.getSize().x)
		&& (b.getPosition().x < a.getPosition().x + a.getSize().x);

	bool yOverlap = (a.getPosition().y < b.getPosition().y + b.getSize().y)
		&& (b.getPosition().y < a.getPosition().y + a.getSize().y);

	bool zOverlap = (a.getPosition().z < b.getPosition().z + b.getSize().z)
		&& (b.getPosition().z < a.getPosition().z + a.getSize().z);

	// collision if all three axes overlap
	return xOverlap && yOverlap && zOverlap;
}

// anticipate collision for player object's future position and an object
// uses a specified future_position, not the current one of Obiect& player
bool anticipateCollision(glm::vec3 future_position, Obiect& player, Obiect& obiect)
{
	// check for overlap along each axis	
	bool xOverlap = (future_position.x < obiect.getPosition().x + obiect.getSize().x)
		&& (obiect.getPosition().x < future_position.x + player.getSize().x);

	bool yOverlap = (future_position.y < obiect.getPosition().y + obiect.getSize().y)
		&& (obiect.getPosition().y < future_position.y + player.getSize().y);

	bool zOverlap = (future_position.z < obiect.getPosition().z + obiect.getSize().z)
		&& (obiect.getPosition().z < future_position.z + player.getSize().z);

	// collision if all three axes overlap
	return xOverlap && yOverlap && zOverlap;
}



// check collisions between player and objects
bool checkPlayerCollision(std::vector<Obiect>& vector_obiecte)
{
	Obiect& player = vector_obiecte.at(0);

	for (int i = 1; i < vector_obiecte.size(); i++)
	{
		// return true if it's colliding
		if (isColliding(player, vector_obiecte.at(i)))
		{
			return true;
		}
	}

	return false;
}




// basic WASD movement and camera rotation
void processKeyboardInput()
{
	float cameraSpeed = 30 * deltaTime;

	// collisions computed based on player model's center, not the functional playerPos aka coltul stanga, jos, front
	glm::vec3 playerCenterPos = glm::vec3(
		playerPos.x - (vector_obiecte.at(0).getSize().x / 2.0f),
		playerPos.y + (vector_obiecte.at(0).getSize().y / 2.0f),
		playerPos.z - (vector_obiecte.at(0).getSize().z / 2.0f)
	);



	//translation -- playerPos TREB SA TINA CONT de getCameraViewDirection() (nu face miscare din laterale, se misca invers)
	
	if (window.isPressed(GLFW_KEY_W))
	{
		glm::vec3 future_pos_w = playerCenterPos + glm::vec3(1.0f, 0.0f, 1.0f) * camera.getCameraViewDirection() * cameraSpeed * playerSpeed * 20.0f;
		
		bool will_collide = 0;

		// check whether it'll collide with any object
		for (int i = 1; i < vector_obiecte.size(); i++)
		{
			// perform movement if no collision will happen between the player (0th object) and any other object
			if (anticipateCollision(future_pos_w, vector_obiecte.at(0), vector_obiecte.at(i)) == 1)
			{
				will_collide = 1;
				std::cout << "will collide on W" << std::endl;
			}
		}

		// if not, let it move
		if (will_collide == 0)
		{
			playerPos += glm::vec3(1.0f, 0.0f, 1.0f) * camera.getCameraViewDirection() * cameraSpeed * playerSpeed * 20.0f;
			camera.keyboardMoveFront(cameraSpeed);
		}
	}

	if (window.isPressed(GLFW_KEY_S))
	{
		glm::vec3 future_pos_s = playerCenterPos - glm::vec3(1.0f, 0.0f, 1.0f) * camera.getCameraViewDirection() * cameraSpeed * playerSpeed * 20.0f;

		bool will_collide = 0;

		// check whether it'll collide with any object
		for (int i = 1; i < vector_obiecte.size(); i++)
		{
			// perform movement if no collision will happen between the player (0th object) and any other object
			if (anticipateCollision(future_pos_s, vector_obiecte.at(0), vector_obiecte.at(i)) == 1)
			{
				will_collide = 1;
				std::cout << "will collide on S" << std::endl;
			}
		}

		// if not, let it move
		if (will_collide == 0)
		{
			playerPos -= glm::vec3(1.0f, 0.0f, 1.0f) * camera.getCameraViewDirection() * cameraSpeed * playerSpeed * 20.0f;
			camera.keyboardMoveBack(cameraSpeed);
		}
	}

	if (window.isPressed(GLFW_KEY_A))
	{
		glm::vec3 future_pos_a = playerCenterPos - glm::cross(camera.getCameraViewDirection(), camera.getCameraUp()) * cameraSpeed * playerSpeed * 20.0f;

		bool will_collide = 0;

		// check whether it'll collide with any object
		for (int i = 1; i < vector_obiecte.size(); i++)
		{
			// perform movement if no collision will happen between the player (0th object) and any other object
			if (anticipateCollision(future_pos_a, vector_obiecte.at(0), vector_obiecte.at(i)) == 1)
			{
				will_collide = 1;
				std::cout << "will collide on A" << std::endl;
			}
		}

		// if not, let it move
		if (will_collide == 0)
		{
			playerPos -= glm::cross(camera.getCameraViewDirection(), camera.getCameraUp()) * cameraSpeed * playerSpeed * 20.0f;
			camera.keyboardMoveLeft(cameraSpeed);
		}
	}

	if (window.isPressed(GLFW_KEY_D))
	{
		glm::vec3 future_pos_d = playerCenterPos + glm::cross(camera.getCameraViewDirection(), camera.getCameraUp()) * cameraSpeed * playerSpeed * 20.0f;

		bool will_collide = 0;

		// check whether it'll collide with any object
		for (int i = 1; i < vector_obiecte.size(); i++)
		{
			// perform movement if no collision will happen between the player (0th object) and any other object
			if (anticipateCollision(future_pos_d, vector_obiecte.at(0), vector_obiecte.at(i)) == 1)
			{
				will_collide = 1;
				std::cout << "will collide on D" << std::endl;
			}
		}

		// if not, let it move
		if (will_collide == 0)
		{
			playerPos += glm::cross(camera.getCameraViewDirection(), camera.getCameraUp()) * cameraSpeed * playerSpeed * 20.0f;
			camera.keyboardMoveRight(cameraSpeed);
		}
	}
/*
	if (window.isPressed(GLFW_KEY_R))
	{
		camera.keyboardMoveUp(cameraSpeed);
	}
	if (window.isPressed(GLFW_KEY_F))
	{
		camera.keyboardMoveDown(cameraSpeed);
	}
*/



	// enable jumping movement when pressing space
	if (window.isPressed(GLFW_KEY_SPACE) && jumping == 0 /* && (checkCollision() || swinging == 1)*/)
	{
		jumping = 1;
		firstJumpFrame = glfwGetTime();
		initialJumpHeight = playerPos.y;
	}




	// rotatii cu sageti
	if (window.isPressed(GLFW_KEY_LEFT))
	{
		camera.rotateOy(cameraSpeed, playerPos);

		// rotate object in sync with camera (in rendering loop)
		playerAngle += cameraSpeed;
	}
	if (window.isPressed(GLFW_KEY_RIGHT))
	{
		camera.rotateOy(-cameraSpeed, playerPos);

		// rotate object in sync with camera (in rendering loop)
		playerAngle -= cameraSpeed;
	}
	if (window.isPressed(GLFW_KEY_UP))
	{
		camera.rotateOx(cameraSpeed, playerPos);
	}
	if (window.isPressed(GLFW_KEY_DOWN))
	{
		camera.rotateOx(-cameraSpeed, playerPos);
	}


	// record position in player object (for collisions)
	vector_obiecte.at(0).setPosition(playerPos);
}



// jumping, falling
void processPlayerMovement()
{
	// collisions computed based on player model's center, not the functional playerPos aka coltul stanga, jos, front
	glm::vec3 playerCenterPos = glm::vec3(
		playerPos.x - (vector_obiecte.at(0).getSize().x / 2.0f),
		playerPos.y + (vector_obiecte.at(0).getSize().y / 2.0f),
		playerPos.z - (vector_obiecte.at(0).getSize().z / 2.0f)
	);


	// jumping movement
	// cosine animation from 1 to 0, and w/o landing again from 0 to -1
	if (jumping == 1) {

		//if (swinging == 1)
		//	jumpDuration = longjumpDuration;

		float currentJumpFrame = glfwGetTime();
		deltaJumpTime = currentJumpFrame - firstJumpFrame;
		float normalizedTime = (deltaJumpTime / jumpDuration) * 3.1456f;

		const float radius =  jumpHeight;
		float cosinus = cos(normalizedTime);							// values (1, 0)
		playerPos.y = initialJumpHeight + (-1.0f + cosinus) * -radius;	// values (0, jumpHeight)

		// adjust camera
		camera.verticalMovement(normalizedTime * 0.005f);
		
		// adjust camera
		//camera.setCameraPosition(glm::vec3(0.0f, 1.0f, 0.0f) * 30.0f);
		//cameraPosition += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed * speedMultiplier;
		//camera.setCameraPosition(
		//	glm::vec3(
		//		camera.getCameraPosition().x,
		//		camera.getCameraPosition().y + (-1.0f + cosinus) * -radius,
		//		camera.getCameraPosition().z
		//	)
		//);

		// stop jumping animation when duration expires
		if (deltaJumpTime > jumpDuration)
		{
			jumping = 0;
			//if (swinging == 1)
			//	swinging = 0;
			jumpDuration = shortjumpDuration;

		}
	}


	// falling (negative gravity because it's descending)
	// like player controls, anticipate whether the fall will be broken by an object below the player.
	// if not, apply gravity
	if (jumping == 0)
	{
		glm::vec3 future_pos_y = playerCenterPos - glm::vec3(0.0f, gravity, 0.0f);

		bool will_collide = 0;

		// check whether it'll collide with any object
		for (int i = 1; i < vector_obiecte.size(); i++)
		{
			if (anticipateCollision(future_pos_y, vector_obiecte.at(0), vector_obiecte.at(i)) == 1)
			{
				will_collide = 1;
				std::cout << "not falling" << std::endl;
			}
		}

		// if not, let it fall
		if (will_collide == 0)
		{
			playerPos.y += -gravity;
			camera.verticalMovement(-gravity * 0.5f);

			std::cout << "FALLING" << std::endl;
		}
	}
}
