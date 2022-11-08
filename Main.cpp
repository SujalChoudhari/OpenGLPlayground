# include <iostream>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

// Dimentions for Screen
# define WIDTH 600
# define HEIGHT 400


// Shaders
// Vertex Shader (runs for each vertex)
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){\n"
"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0f);\n"
"}\0";

// Fragmant Shader (runs for each fragment which is generated during rasterisation)
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"	FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
"}\0";

int main() {

	glfwInit();								// Initiate GLFW Library
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);				// Hint GLFW with the Major version (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);				// Hint GLFW with the Minor version (3.3)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// Hint GLFW with the Opengl Profile (This case: core)


	GLfloat vertices[] = {						// Vertices of a triangle.
		-0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,			// Lower Left Corner
		 0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,			// Lower Rignt Corner
		 0.5f, 0.5f * float(sqrt(3)) * 2 / 3,0.0f,		// Upper Rignt Corner
	};

	GLFWwindow* window = glfwCreateWindow(WIDTH, 400, "Hello World", NULL, NULL);	// Create a window object (get its refrence)

	if (window == NULL) {							// Possible error check
		glfwTerminate();						// Terminate GLFW if window not Created
		return -1;							// Return status code as -1
	}

	glfwMakeContextCurrent(window);						// Ask GLFW to Make the created Window current.

	gladLoadGL();								// Load Glad
	glViewport(0, 0, WIDTH, HEIGHT);					// Set ViewPort Dimentions for GLAD

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);			// Create a new Shader (Vertex Shader)
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);		// Assign the Source Code to the Shader
	glCompileShader(vertexShader);						// Compile the Shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// Create a new Shader (Fragment Shader)
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);	// Assign the Source Code to the Shader
	glCompileShader(fragmentShader);								// Compile the Shader

	GLuint shaderProgram = glCreateProgram();							// Create A new Shader Program (Only 1 type available)
	glAttachShader(shaderProgram, vertexShader);							// Attact both shaders to it
	glAttachShader(shaderProgram, fragmentShader);							// ...
	glLinkProgram(shaderProgram);									// Link the Shader Program with GLAD

	glDeleteShader(vertexShader);									// Both Shaders are linked (in GPU). Thus 
	glDeleteShader(fragmentShader);									// ... delete the Shaders from memory


	GLuint VAO, VBO;					// Create VertexArrayObjects (1 for now)

	glGenVertexArrays(1, &VAO);				// Generate VAO
	glGenBuffers(1, &VBO);					// Generate VBO  (different from GPU Front and Back Buffers)

	glBindVertexArray(VAO);					// Bind the VAO with GPU
	glBindBuffer(GL_ARRAY_BUFFER, VBO);			// Bind VBO using (since it is a array of points, using ArrayBuffer)

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		// Assign data to the buffer.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);		// Since the data is in array format, Schemas
																					// ... are needed for shaders

	glEnableVertexAttribArray(0);					// Reset
	glBindBuffer(GL_ARRAY_BUFFER, 0);				// Reset
	glBindVertexArray(0);						// Reset


	glClearColor(0.17f, 0.13f, 0.17f, 1.0f);		// Set the clear color for Clearing screen
	glClear(GL_COLOR_BUFFER_BIT);				// Clear the Screen Right away.
	glfwSwapBuffers(window);				// Swap the buffers to make changes visible

	// Loop (Consider One Iteration as one frame)
	while (!glfwWindowShouldClose(window)) {		// Keep window open (handle closing)
		glClear(GL_COLOR_BUFFER_BIT);			// Clear the Screen 
		glUseProgram(shaderProgram);			// Use the shader program generated
		glBindVertexArray(VAO);				// Bind vertex array with GPU

		glDrawArrays(GL_TRIANGLES, 0, 3);		// Draw the given array in for of Triangles.

		glfwSwapBuffers(window);			// Swap buffers to make changes live.
		glfwPollEvents();				// Hanfle Events if any
	}

	glDeleteVertexArrays(1, &VAO);				// Delete the VAOs and VBOs
	glDeleteBuffers(1, &VBO);				// ...
	glDeleteProgram(shaderProgram);				// Delete the Shader Programe (Delete 
								//... every thing and prepare for termination) (related to GLAD)

	glfwDestroyWindow(window);				// Destroy the window object
	glfwTerminate();					// Terminate GLFW 
	return 0;						// Exit with status code 0
}
