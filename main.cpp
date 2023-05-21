#include <iostream> //biblioteca padão de entrada e saida de terminal.
#include <SDL2/SDL.h> //biblioteca para janela de contexto OpenGL.
#include <glad/glad.h> //biblioteca para uso de funções OpenGL.

using namespace std;

/*
					MAIN FUNCTION
*/



//-------------------------------- GLOBAL
	
	//criando o ponteiro que vai receber a janela(window). criar contexto OpenGL.
	SDL_Window* 	window_application = nullptr;
	SDL_GLContext   OpenGLContext = nullptr;
	
	bool close_program = false;
	
	
	
	
	
//--------------------------------\\

//-------------------------------- FUNCTIONS


void OpenglVersion(){
	
	cout << "OpenGL Version" << endl;
	cout << "vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "render: " << glGetString(GL_RENDERER) << endl;
	cout << "version: " << glGetString(GL_VERSION) << endl;
	cout << "shading language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	
}


void InitProgram(){
	
	//iniciar o sistema de video.			se a função retornar um valor menor que 1, quer dizer que não pode ser iniciado.
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "video init error.\nError INFO: " << SDL_GetError();
		exit(1);
	} else{
		cout << "video init successful\n";
	}
	
	
	
	//pondo atributos GL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	cout << "opengl specifications\n";
	
	
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
						1080, 720,
						SDL_WINDOW_OPENGL);
	cout << "window_application defined\n";
	
	if(window_application == nullptr){
		cout << "SDL window in OpenGL context cannot be created\n";
		exit(1);
	} else{
		cout << "SDL OpenGL window context created\n";
	}
	
	
	OpenGLContext = SDL_GL_CreateContext(window_application);
	if(OpenGLContext == nullptr){
		cout << "OpenGl context to window_application do not executed\n";
		exit(1);
	} else{
		cout << "OpenGL context created\n";
	}
	
	
	
	//iniciar o glad.
	if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
		cout << "glad cannot be initialized\n";
		exit(1);
	} else{
		cout << "glad init\n";
	}
	
	
	OpenglVersion();
	
}



void Input(){
	cout << "\ninput reading\n";
	SDL_Event event_queue;
	while(SDL_PollEvent(&event_queue) != 0){
		
		if(event_queue.type == SDL_QUIT){
			close_program = true;
		}
		
	}
	cout << "endind input reading\n";
}



void PreDraw(){
	cout << "\nPreDraw\n";
}


void Draw(){
	cout << "\nDraw\n";
}


void MainLoop(){
	
	cout << "\nstart main loop\n";
	
	while(close_program !=true){
		
		Input();
		PreDraw();
		Draw();
		
		//atualiza a tela.
		SDL_GL_SwapWindow(window_application);
		
	}
	cout << "main loop killed\n";
}


void CleanUP(){
	
	cout << "\ncleanup function\n";
	
	//destruir janela.
	SDL_DestroyWindow(window_application);
	
	
	//e fechamos o programa.
	SDL_Quit();
	
	cout << "ending cleanup functino\n";
}
//--------------------------------\\










//-------------------------------- MAIN


int main(int argc, char * argv[]){
	
	cout << "start program\n\n";
	
	InitProgram();
	MainLoop();
	CleanUP();
	
	
	cout << "\n\nProgram Ended\n\n";
	cout << "teste de compilacao\n";
	system("pause");
	return 0;
}
