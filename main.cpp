#include <iostream> //biblioteca padão de entrada e saida de terminal.
#include <SDL2/SDL.h> //biblioteca para janela de contexto OpenGL.
#include <glad/glad.h> //biblioteca para uso de funções OpenGL.
#include <string>
#include <vector>
#include <ctime>

using namespace std;

int start_timer_program = time(NULL);

//-------------------------------- GLOBAL
	//criando o ponteiro que vai receber a janela(window). criar contexto OpenGL.
SDL_Window* 	window_application = nullptr;
SDL_GLContext   OpenGLContext = nullptr;

int screem_w = 640;
int screem_h = 480;

GLuint VAO = 0;
GLuint VBO = 0;
GLuint GPSP = 0; // Graphics Pipeline Shader Program.

//Shaders NOTE: se for fazer algum shader, fazer por leitura de arquivos é melhor, mas se quiser pode deixar no código mesmo,
//já que são string.
const string vertex_shader =
	"#version 410 core\n"
	"in vec4 position;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(position.x, position.y, position.z, position.w);\n"
	"}\n";
	
const string fragment_shader =
	"#version 410 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"	color = vec4(1.0f, 0.5f, 0.0f, 1.0f);\n"
	"}\n";

bool close_program = false;

//-------------------------------- FUNCTIONS
void OpenglVersion(){
	cout << "OpenGL Version" << endl;
	cout << "vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "render: " << glGetString(GL_RENDERER) << endl;
	cout << "version: " << glGetString(GL_VERSION) << endl;
	cout << "shading language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

GLuint CompileShader(GLuint type, const string& source){
	GLuint shader_object;
	
	if(type == GL_VERTEX_SHADER){
		shader_object = glCreateShader(GL_VERTEX_SHADER);
	} else if(type == GL_FRAGMENT_SHADER){
		shader_object = glCreateShader(GL_FRAGMENT_SHADER);
	}
	
	const char* src = source.c_str();
	glShaderSource(shader_object, 1, &src, nullptr);
	glCompileShader(shader_object);
	
	return shader_object;
}

GLuint CreateShaderProgram(const string& vs, const string& fs){
	GLuint program_object = glCreateProgram();
	
	GLuint vert_shader = CompileShader(GL_VERTEX_SHADER, vs);
	GLuint frag_shader = CompileShader(GL_FRAGMENT_SHADER, fs);
	
	glAttachShader(program_object, vert_shader);
	glAttachShader(program_object, frag_shader);
	glLinkProgram(program_object);
	
	glValidateProgram(program_object);
	
	return program_object;
}

void CreateGraphicsPipeline(){
	
	GPSP = CreateShaderProgram(vertex_shader,fragment_shader);
	
}

void VertexSpecification(){
	//Fica na CPU.
	const vector<GLfloat> vertex_position{
			-0.8f, -0.8f, 0.0f, //V1        V = Vertex
			 0.8f, -0.8f, 0.0f, //V2
			 0.0f,  0.8f, 0.0f  //V3
	};
	
	//Começando a confingurar as coisas na GPU.
	//VAO Vertex Array Object.
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	//VBO Vertex Buffer Object.
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glBufferData(GL_ARRAY_BUFFER,
				vertex_position.size() * sizeof(GLfloat),
				vertex_position.data(),
				GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,
				3,
				GL_FLOAT, GL_FALSE,
				0, (void*)0);
	
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}

void InitProgram(){
	//iniciar o sistema de video.			se a função retornar um valor menor que 1, quer dizer que não pode ser iniciado.
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "video init error.\nError INFO: " << SDL_GetError();
		exit(1);
	}
	//pondo atributos GL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	//requisitando a criação da janela.
	/* PARAMETROS
	titulo: "titulo"
	posição: x, y int
	resolução: x, y
	contexto(OpenGL por exemplo): SDL_WINDOW_SHOW
	*/
	window_application = SDL_CreateWindow("window",
						SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED,
						screem_w, screem_h,
						SDL_WINDOW_OPENGL);
	
	if(window_application == nullptr){
		cout << "SDL window in OpenGL context cannot be created\n"; exit(1);
	}
	
	OpenGLContext = SDL_GL_CreateContext(window_application);
	if(OpenGLContext == nullptr){
		cout << "OpenGl context to window_application do not executed\n"; exit(1);
	}
	
	//iniciar o glad.
	if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
		cout << "glad cannot be initialized\n"; exit(1);
	}
	
	OpenglVersion();
}

void Input(){
	
	SDL_Event event_queue;
	while(SDL_PollEvent(&event_queue) != 0){
		if(event_queue.type == SDL_QUIT){
			close_program = true;
		}
	}
}

void PreDraw(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	glViewport(0, 0, screem_w, screem_h);
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	glUseProgram(GPSP);
}

void Draw(){
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MainLoop(){
	while(close_program !=true){
		Input();
		PreDraw();
		Draw();
		
		//atualiza a tela.
		SDL_GL_SwapWindow(window_application);
	}
}

void CleanUP(){
	//destruir janela.
	SDL_DestroyWindow(window_application);
	
	//e fechamos o programa.
	SDL_Quit();
}

//-------------------------------- MAIN
int main(int argc, char * argv[]){
	InitProgram();
	VertexSpecification();
	CreateGraphicsPipeline();
	cout << time(NULL) - start_timer_program << endl;
	MainLoop();
	CleanUP();
	
	//system("pause");
	return 0;
}
