#include "Particle.h"

Particle::Particle(void)
{
	this->vertexArrayIDParticle = 0;
	this->positionVector[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	this->positionVector[1] = glm::vec3(0.0f, 100.0f, 0.0f);
	this->positionVector[2] = glm::vec3(200.0f, 50.0f, 0.0f);
}

void Particle::draw() 
{
	//if (!vertexArrayIDParticle)
	generateParticle();
	// Draw the triangles ! 
	glBindVertexArray(vertexArrayIDParticle);//-> Daten zum Würfel, VertexArrayObjekt wird an Shader weitergegeben
	glDrawArrays(GL_TRIANGLES, 0, 3*3); // 12*3 indices starting at 0 -> 12 triangles
}

void Particle::move()
{
	std::vector<glm::vec3> tmp = Particle::getNextPosition();
	for (int i = 0; i < 3; i++)
		this->positionVector.at(i) = tmp.at(i);
}

std::vector<glm::vec3> Particle::getNextPosition() //NR
{
	std::vector<glm::vec3> ret;
	for (int i = 0; i < 3; i++)
	{
		ret.at(i) *= directionVector;
	}
	return ret;
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
		positionVector.at(0).x, positionVector.at(0).y, positionVector.at(0).z,
		positionVector.at(1).x, positionVector.at(1).y, positionVector.at(1).z,
		positionVector.at(2).x, positionVector.at(2).y, positionVector.at(2).z,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//Farbwerte des Partikels, mal sehen wies wird
	static const GLfloat g_color_buffer_data[] = 
	{ 
		0.999f,  0.999f,  0.999f,   
		0.999f,  0.999f,  0.999f,   
		0.999f,  0.999f,  0.999f
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

void Particle::setPositionVector(std::vector<glm::vec3> vector)
{
	this->positionVector = vector;
}

void Particle::setVelocity(double velocity)
{
	this->velocity = velocity;
}

void Particle::toggleReadyForDraw() 
{
	(this->readyForDraw) ? this->readyForDraw = false : this->readyForDraw = true;
}

Particle::~Particle(void)
{
}
