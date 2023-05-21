#include <iostream> //biblioteca padão de entrada e saida de terminal.
#include <SDL2/SDL.h> //biblioteca para janela de contexto OpenGL.
#include <glad/glad.h> //biblioteca para uso de funções OpenGL.

using namespace std;

/*
					MAIN FUNCTION
*/

int main(int argc, char * argv[]){
	
	//criando o ponteiro que vai receber a janela(window).
	SDL_Window* window = nullptr;
	
	
	//iniciar o sistema de video.			se a função retornar um valor menor que 1, quer dizer que não pode ser iniciado.
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "video init error.\nError INFO: " << SDL_GetError();
	} else{
		cout << "video init successful\n";
	}
	
	
	//requisitando a criação da janela.
	/* PARAMETROS
	titulo: "titulo"
	posição: x, y int
	resolução: x, y
	contexto(OpenGL por exemplo): SDL_WINDOW_SHOW
	*/
	window = SDL_CreateWindow("Janela do Programa", 15, 15, 640, 480, SDL_WINDOW_SHOWN);
	
	//Um Delay para vermos a janela.
	SDL_Delay(3000);
	
	
	//destruimos a janela para não ocupar mais espaço na memória.
	SDL_DestroyWindow(window);
	
	
	//e fechamos o programa.
	SDL_Quit();
	
	cout << "\n\nPrograma finalizado\n\n";
	system("pause");
	return 0;
}
