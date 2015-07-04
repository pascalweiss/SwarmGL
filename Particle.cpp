#include "Particle.h"
#include <iostream>

Particle::Particle(glm::vec3 basePosVector, glm::vec3 aDirectionVector, glm::vec3 normVector, float aLen)
{
	this->init(basePosVector, aDirectionVector, normVector, aLen);
	
}
<<<<<<< HEAD
				
Particle::Particle()
=======

Particle::Particle(glm::vec3 basePosVector, glm::vec3 aDirectionVector, float aLen)
>>>>>>> 7e3b7e6aa83def76f0475e0c130c5ccb23a81486
{
	this->init(basePosVector, aDirectionVector, getUprightNormVector(aDirectionVector),
		aLen);
		
}

void Particle::init(glm::vec3 basePosVector, glm::vec3 aDirectionVector, glm::vec3 normVector, float aLen)
{
	this->vertexArrayIDParticle = 0;
	this->positionVector.resize(3);
	this->directionVector = normalizeVector(aDirectionVector);
	this->len = aLen;
	setPeak(basePosVector);
	setBasePositions(basePosVector, normVector);
}

void Particle::draw() 
{
	if (!vertexArrayIDParticle)
		generateParticle();
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
		0.999f,  0.777f,  0.666f,   
		0.333f,  0.444f,  0.555f,   
		0.222f,  0.111f,  0.123f
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

void Particle::setPeak(glm::vec3 basePosVector)
{
	this->positionVector[2] = basePosVector + this->directionVector * len;
}

void Particle::setBasePositions(glm::vec3 basePosVector, glm::vec3 normVector)
{
	normVector = this->normalizeVector(normVector);
	this->positionVector[0] = basePosVector + normVector * (len / 2);
	this->positionVector[1] = basePosVector + normVector * (-len / 2);
}

glm::vec3 Particle::normalizeVector(glm::vec3 toNormalize)
{
	return glm::normalize(toNormalize);
}

glm::vec3 Particle::getUprightNormVector(glm::vec3 toNorm)
{
	return glm::vec3(0.0f, -(toNorm.z), toNorm.y);
}

Particle::~Particle(void)
{
}


