#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Graph.h"
#include "mTexture.h"

class Game 
{
	private:
	       bool Running;
	       bool Paused;
	       SDL_Renderer* renderer;
	       SDL_Window* window;

	       std::vector<mTexture> textures;
	       SDL_Texture* img;
	       SDL_Texture* background;
	       Graph graph;
	       std::vector<int> nodes;
	       std::vector<int> edges;
	public:
	       Game();
	       void logSDLError(std::ostream &os, const char* msg);
	       SDL_Texture* loadTexture(const char* file, SDL_Renderer* ren);
		void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h);
	       void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y);

	       int OnExecute();
	       bool OnInit();
	       void OnEvent(SDL_Event* Event);
	       void OnLoop();
	       void OnRender();
	       void OnCleanup();

};
