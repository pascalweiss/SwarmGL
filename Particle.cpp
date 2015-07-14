#include "Particle.h"
#include "Globals.h"
#include <iostream>

Particle::Particle(glm::vec3 basePosVector, glm::vec3 aDirectionVector, glm::vec3 normVector, float aLen)
{
	this->init(basePosVector, aDirectionVector, normVector, aLen);
	this->normVector = normVector;
	
}

Particle::Particle(glm::vec3 basePosVector, glm::vec3 aDirectionVector, float aLen)
{
	this->init(basePosVector, aDirectionVector, getUprightNormVector(aDirectionVector),
		aLen);
		
}

void Particle::init(glm::vec3 basePosVector, glm::vec3 aDirectionVector, glm::vec3 normVector, float aLen)
{
	this->basePositionVector = basePosVector;
	this->vertexArrayIDParticle = 0;
	this->positionVector.resize(3);
	this->directionVector = normalizeVector(aDirectionVector);
	this->len = aLen;
	setPeak(basePosVector);
	setBasePositions(basePosVector, normVector);
	this->velocity = VELOCITY;
}

void Particle::draw() 
{
	//if (!vertexArrayIDParticle)
		generateParticle();
	glBindVertexArray(vertexArrayIDParticle);//-> Daten zum Würfel, VertexArrayObjekt wird an Shader weitergegeben
	glDrawArrays(GL_TRIANGLES, 0, 3*3); // 12*3 indices starting at 0 -> 12 triangles
}

void Particle::move()
{
	/*std::vector<glm::vec3> tmp = Particle::getNextPosition();
	for (int i = 0; i < 3; i++)
		this->positionVector.at(i) = tmp.at(i);*/
	/*for (int i = 0; i < 3; i++) 
	{
		this->positionVector[i] = this->positionVector[i] + this->directionVector * 
																	velocity;
	}*/

	this->basePositionVector += this->directionVector * velocity;
	glm::vec3 norm = getUprightNormVector(this->directionVector);
	setBasePositions(this->basePositionVector, norm);
	setPeak(this->basePositionVector);


	
			
	
}

std::vector<glm::vec3> Particle::getNextPosition() //NR
{
	std::vector<glm::vec3> ret;
	ret.resize(3);
	for (int i = 0; i < 3; i++)
		ret.at(i) = this->positionVector.at(i) + this->directionVector * velocity;
	return ret;
}

void Particle::generateParticle()
{
	glGenVertexArrays(1, &vertexArrayIDParticle); //Erzeuge VertexArrayObjekt
	glBindVertexArray(vertexArrayIDParticle); //Binde das erzeugte Objekt
	
	static GLfloat g_vertex_buffer_data[9];
	/*static GLfloat g_vertex_buffer_data[] = //war mal const
	{ 
		this->positionVector.at(0).x, this->positionVector.at(0).y, this->positionVector.at(0).z,
		this->positionVector.at(1).x, this->positionVector.at(1).y, this->positionVector.at(1).z,
		this->positionVector.at(2).x, this->positionVector.at(2).y, this->positionVector.at(2).z,
	};*/
	for (int i = 0, j = 0; i < 3; i++)
	{
		g_vertex_buffer_data[j++] = this->positionVector[i].x;
		g_vertex_buffer_data[j++] = this->positionVector[i].y;
		g_vertex_buffer_data[j++] = this->positionVector[i].z;
	}
	
	glGenBuffers(1, &vertexbuffer);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);

	//Farbwerte des Partikels, mal sehen wies wird
	static const GLfloat g_color_buffer_data[] = 
	{ 
		0.111f,  0.777f,  0.666f,   
		0.333f,  0.444f,  0.555f,   
		0.222f,  0.333f,  0.777f
	};

	glGenBuffers(1, &colorbuffer); //Adresse des Buffers anfordern
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer); //Aufruf: angeforderten Buffer benutzen
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_DYNAMIC_DRAW); //Daten für den Buffer definieren, Größe, Flag: Daten werden sich wohl nicht ändern

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
	
	//glBindVertexArray(0);
}

void Particle::clearBuffers()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
}

void Particle::addToDirectionVector(glm::vec3 vector)
{
	//this->directionVector += normalizeVector(vector);
	this->directionVector = normalizeVector(vector); 
}

glm::vec3 Particle::getDirectionVector()
{
	return this->directionVector;
}

void Particle::setPositionVector(std::vector<glm::vec3> vector)
{
	this->positionVector = vector;
}

void Particle::setVelocity(float velocity)
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

glm::vec3 Particle::getBasePosition() 
{
	return basePositionVector;
}

void Particle::setBasePositions(glm::vec3 basePosVector, glm::vec3 normVector)
{
	normVector = this->normalizeVector(normVector);
	this->positionVector[0] = basePosVector + normVector * (len / 2);
	this->positionVector[1] = basePosVector + normVector * (-len / 2);	
}

glm::vec3 Particle::normalizeVector(glm::vec3 toNormalize)
{
	if (toNormalize.x == 0 && toNormalize.y == 0 && toNormalize.z == 0) 
		return toNormalize;	
	return glm::normalize(toNormalize);
	
}

glm::vec3 Particle::getUprightNormVector(glm::vec3 toNorm)
{
	glm::vec3 ret = glm::vec3(0.0f, -(toNorm.z), toNorm.y);
	return ret;
}

Particle::~Particle(void)
{
}


