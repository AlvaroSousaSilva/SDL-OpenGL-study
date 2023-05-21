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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
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
	window_application = SDL_CreateWindow("Janela do Programa", 15, 15, 640, 480, SDL_WINDOW_OPENGL);
	
	if(window_application == nullptr){
		cout << "SDL window in OpenGL context cannot be created\n";
		exit(1);
	}
	
	OpenGLContext = SDL_GL_CreateContext(window_application);
	
	if(OpenGLContext == nullptr){
		cout << "OpenGl context to window_application do not executed\n";
		exit(1);
	}
	
	
}


void MainLoop(){
	
	while(close_program){
		
		Input();
		PreDraw();
		Draw();
		
		//atualiza a tela.					  TEMPO DE VIDEO= 20:42
		SDL_GL_SwapWindow(window_application);
		
	}
}


void CleanUP(){
	
	//destruir janela.
	SDL_Destroy_Window(window_application);
	
	
	//e fechamos o programa.
	SDL_Quit();
	
}
//--------------------------------\\










//-------------------------------- MAIN


int main(int argc, char * argv[]){
	
	
	InitProgram();
	MainLoop();
	CleanUP();
	
	
	cout << "\n\nProgram Ended\n\n";
	system("pause");
	return 0;
}
