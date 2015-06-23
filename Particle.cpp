#include "Particle.h"

Particle::Particle(void)
{
	this->vertexArrayIDParticle = 0;
}

void Particle::draw() 
{
}

glm::vec3 Particle::getNextPosition() //NR
{
	/*float polygonArray[] = 
	{
		0.0f,  0.5f, // Vertex 1 (X, Y)
		0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};
	GLuint vertexBuffer;
	
	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(polygonArray), polygonArray, GL_STATIC_DRAW); 
	*/
	
	
	return glm::vec3(0,0,0);
}

void Particle::generateParticle()
{
	GLuint vertexbuffer;
	GLuint colorbuffer;
	
	glGenVertexArrays(1, &vertexArrayIDParticle); //Erzeuge VertexArrayObjekt
	glBindVertexArray(vertexArrayIDParticle); //Binde das erzeugte Objekt

	//Muss noch variabel angepasst werden..
	static const GLfloat g_vertex_buffer_data[] = 
	{ 
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		2.0f, 0.5f, 0.0f
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//Farbwerte des Partikels, mal sehen wies wird
	static const GLfloat g_color_buffer_data[] = 
	{ 
		0.583f,  0.771f,  0.014f,   
		0.822f,  0.569f,  0.201f,   
		0.597f,  0.770f,  0.761f		
	};

	glGenBuffers(1, &colorbuffer); //Adresse des Buffers anfordern
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer); //Aufruf: angeforderten Buffer benutzen
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW); //Daten für den Buffer definieren, Größe, Flag: Daten werden sich wohl nicht ändern

	glEnableVertexAttribArray(0); // Kein Disable ausführen ! In Sepeicherbereich 0 des Shaders schreiben
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer); 
	glEnableVertexAttribArray(1); // Kein Disable ausführen ! In Speicherbereich 2 des Shaders schreiben
	glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
	);
	
	glBindVertexArray(0);
}

void Particle::setDirectionVector(glm::vec3 vector)
{
	this->directionVector = vector;
}

void Particle::setPositionVector(glm::vec3 vector)
{
	this->positionVector = vector;
}

void Particle::setVelocity(double aVelocity)
{
	this->velocity = aVelocity;
}

void Particle::toggleReadyForDraw() 
{
	(this->readyForDraw) ? this->readyForDraw = false : this->readyForDraw = true;
}

Particle::~Particle(void)
{
}
