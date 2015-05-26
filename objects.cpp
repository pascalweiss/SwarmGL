// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    DrahtWuerfel-Objekt
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint VertexArrayIDWireCube = 0;

static void createWireCube()
{
	// Vertexarrays kapseln ab OpenGL3 Eckpunkte, Texturen und Normalen
	glGenVertexArrays(1, &VertexArrayIDWireCube);
	glBindVertexArray(VertexArrayIDWireCube);

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, -1.0f,-1.0f, 1.0f, 
		-1.0f, 1.0f,-1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,  1.0f,-1.0f, 1.0f,  
		 1.0f, 1.0f,-1.0f,  1.0f, 1.0f, 1.0f, 
		-1.0f,-1.0f,-1.0f, -1.0f, 1.0f,-1.0f, 
		-1.0f,-1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,  1.0f, 1.0f,-1.0f, 
		 1.0f,-1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  
		-1.0f,-1.0f,-1.0f,  1.0f,-1.0f,-1.0f,  
		-1.0f,-1.0f, 1.0f,  1.0f,-1.0f, 1.0f, 
		-1.0f, 1.0f,-1.0f,  1.0f, 1.0f,-1.0f, 
		-1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f
	};

	// Vertexbuffer-Daten z.B. auf Grafikkarte kopieren
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Erklären wie die Vertex-Daten zu benutzen sind
	glEnableVertexAttribArray(0); // Kein Disable ausführen !
	glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

	glBindVertexArray(0);
}

void drawWireCube()
{
	if (!VertexArrayIDWireCube)
	{
		createWireCube();
	}

	glBindVertexArray(VertexArrayIDWireCube);
	glDrawArrays(GL_LINES, 0, 24); // 12 Linien haben 24 Punkte
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Wuerfel-Objekt Bunt
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint VertexArrayIDSolidCube = 0;

static void createCube()
{
	GLuint vertexbuffer;
	GLuint colorbuffer;
	
	glGenVertexArrays(1, &VertexArrayIDSolidCube);
	glBindVertexArray(VertexArrayIDSolidCube);

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

	// coordinaten für die dreiecke
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, -1.0f,-1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f, -1.0f,-1.0f,-1.0f, -1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f, -1.0f,-1.0f,-1.0f,  1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,  1.0f,-1.0f,-1.0f, -1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f, -1.0f,-1.0f, 1.0f, -1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f, -1.0f,-1.0f, 1.0f,  1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,  1.0f,-1.0f,-1.0f,  1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,  1.0f, 1.0f, 1.0f,  1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,-1.0f, -1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f, -1.0f, 1.0f,-1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,  1.0f,-1.0f, 1.0f
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// One color for each vertex. They were generated randomly.
	static const GLfloat g_color_buffer_data[] = { 
		0.583f,  0.771f,  0.014f,   0.609f,  0.115f,  0.436f,   0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,   0.435f,  0.602f,  0.223f,   0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,   0.559f,  0.436f,  0.730f,   0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,   0.559f,  0.861f,  0.639f,   0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,   0.771f,  0.328f,  0.970f,   0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,   0.971f,  0.572f,  0.833f,   0.140f,  0.616f,  0.489f,   
		0.997f,  0.513f,  0.064f,   0.945f,  0.719f,  0.592f,	0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,	0.167f,  0.620f,  0.077f,	0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,	0.714f,  0.505f,  0.345f,	0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,	0.302f,  0.455f,  0.848f,	0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,	0.053f,  0.959f,  0.120f,	0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,	0.820f,  0.883f,  0.371f,	0.982f,  0.099f,  0.879f
	};

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Kein Disable ausführen !
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
	glEnableVertexAttribArray(1); // Kein Disable ausführen !
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

void drawCube()
{
	if (!VertexArrayIDSolidCube)
	{
		createCube();
	}

	// Draw the triangles !
	glBindVertexArray(VertexArrayIDSolidCube);
	glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Kugel-Objekt
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint VertexArrayIDSphere = 0;
GLuint lats;
GLuint longs;


// Dieser Code  basiert auf http://ozark.hendrix.edu/~burch/cs/490/sched/feb8/
static void createSphere()
{
	glGenVertexArrays(1, &VertexArrayIDSphere);
	glBindVertexArray(VertexArrayIDSphere);

	static GLuint sphereVertexBuffer = 0;
	static GLfloat* sphereVertexBufferData = NULL;
	static GLfloat* sphereNormalBufferData = NULL;

	sphereVertexBufferData = new GLfloat [6 * (lats + 1) * (longs + 1)];
	sphereNormalBufferData = new GLfloat [6 * (lats + 1) * (longs + 1)];
	int index = 0;

    for (int i = 0; i <= lats; i++) 
	{
          GLfloat lat0 = (GLfloat) M_PI * ((GLfloat) -0.5 + (GLfloat) (i - 1) / (GLfloat) lats);
          GLfloat z0  = sin(lat0);
          GLfloat zr0 =  cos(lat0);
    
          GLfloat lat1 = (GLfloat) M_PI * ((GLfloat) -0.5 + (GLfloat) i / (GLfloat) lats);
          GLfloat z1 = sin(lat1);
          GLfloat zr1 = cos(lat1);
    
		  for (int j = 0; j <= longs; j++)
		  {
              GLfloat lng = (GLfloat) 2 * (GLfloat) M_PI * (GLfloat) (j - 1) / (GLfloat) longs;
              GLfloat x = cos(lng);
              GLfloat y = sin(lng);

			  sphereNormalBufferData[index] = x * zr0;
			  sphereVertexBufferData[index++] = x * zr0;
			  sphereNormalBufferData[index] = y * zr0;
			  sphereVertexBufferData[index++] = y * zr0;
			  sphereNormalBufferData[index] = z0;
			  sphereVertexBufferData[index++] = z0;
			  sphereNormalBufferData[index] = x * zr1;
			  sphereVertexBufferData[index++] = x * zr1;
			  sphereNormalBufferData[index] = y * zr1;
			  sphereVertexBufferData[index++] = y * zr1;
			  sphereNormalBufferData[index] = z1;
			  sphereVertexBufferData[index++] = z1;
          }
     }

	GLuint vertexbuffer;
	GLuint normalbuffer;
	
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * (lats + 1) * (longs + 1), sphereVertexBufferData, GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * (lats + 1) * (longs + 1), sphereNormalBufferData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Kein Disable ausführen !
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : normals
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glEnableVertexAttribArray(2); // Kein Disable ausführen !
	glVertexAttribPointer(
			2,                                // attribute. No particular reason for 2, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
	);

	glBindVertexArray(0);
}

// Nur die Angabe bei der ersten Kugel ist relevant
void drawSphere(GLuint slats, GLuint slongs)
{
	if (!VertexArrayIDSphere)
	{
		lats = slats;
		longs = slongs;
		createSphere();
	}

	glBindVertexArray(VertexArrayIDSphere);
	// Draw the triangles !
	glDrawArrays(GL_QUAD_STRIP, 0, 2 * (lats + 1) * (longs + 1)); 
}