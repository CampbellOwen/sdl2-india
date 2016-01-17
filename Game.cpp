#include "Game.h"
#include <iostream>
#include <math.h>

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;
const int TILE_SIZE = 40;

void Game::logSDLError(std::ostream &os, const char* msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* Game::loadTexture(const char* file, SDL_Renderer* ren)
{
	SDL_Texture* tex = IMG_LoadTexture(ren, file);

	if (tex == nullptr) {
		logSDLError(std::cout, "LoadTexture");
	}

	return tex;
}

void Game::renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;

	SDL_RenderCopy(ren, tex, NULL, &dst);

}

void Game::renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

Game::Game()
{
	Running = false;
	renderer = NULL;
	window = NULL;
}

int Game::OnExecute()
{
	if (!OnInit()) {
		return -1;
	}
	Running = true;
	Paused = false;

	SDL_Event Event;
	
	while(Running) {
		while(SDL_PollEvent(&Event)) {
			OnEvent(&Event);
		}
		if (!Paused) {
			OnLoop();
			OnRender();
		}
	}

	return 0;
}

bool Game::OnInit() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError(std::cout, "SDL_Init");
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG != IMG_INIT_PNG) {
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return false;
	}
	
	window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	if (window == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	
	//                              LOAD TEXTURES                              //



	
	textures.push_back(mTexture(renderer));
	textures[textures.size()-1].loadFromFile("rsz-india.png");

	textures.push_back(mTexture(renderer));
	textures[textures.size()-1].loadFromFile("circle.png");

	// INIT GRAPH
	
	int basex = 700;
	int basey = 400;
	int base = 0;
	int distance = 100;

	nodes.push_back(graph.addNode("Base", basex, basey));
	int points = 20;
	double slice = 2 * M_PI / points;

	for ( int j = 0; j < 2; j++) {
		for(int i = 0; i < points; i++) {
			double angle = slice*i;
			int newX = (int)(basex + distance * cos(angle));
			int newY = (int)(basey + distance * sin(angle));
			nodes.push_back(graph.addNode("sdf", newX, newY));
			edges.push_back(graph.addEdge(nodes[base], nodes[nodes.size()-1], distance));
			std::cout << "hi" << std::endl;
		}
		base = nodes.size()-1;
		basex = graph.nodes[nodes[rand()%points]].x;
		basey = graph.nodes[nodes[rand()%points]].y;
		distance /= j+2;
		points /= j+2;

	}
	

	return true;
}

void Game::OnEvent(SDL_Event* Event)
{
	if (Event->type == SDL_QUIT) {
		Running = false;
	}

	if (Event->type == SDL_MOUSEBUTTONDOWN) {
		nodes.push_back(graph.addNode("", Event->button.x, Event->button.y));
	}
}

void Game::OnLoop()
{

}

void Game::OnRender()
{
	SDL_RenderClear(renderer);
	
	int bW, bH;
	int bx = SCREEN_WIDTH / 2 - bW / 2;
	int by = SCREEN_HEIGHT / 2 - bH / 2;

	renderTexture(background, renderer, bx, by);

	int iW, iH;
	SDL_QueryTexture(img, NULL, NULL, &iW, &iH);

	for (int i = 0; i < edges.size(); i++) {
		int x1 = graph.nodes[graph.edges[edges[i]].start].x;
		int y1 = graph.nodes[graph.edges[edges[i]].start].y;
		int x2 = graph.nodes[graph.edges[edges[i]].end].x;
		int y2 = graph.nodes[graph.edges[edges[i]].end].y;

		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	}
	for ( int i = 0; i < nodes.size(); i++) {
		int ix = graph.nodes[nodes[i]].x;
		int iy = graph.nodes[nodes[i]].y;
		renderTexture(img, renderer, ix + 7, iy + 7, 15, 15);
		std::cout << i << " x: " << ix << " y: " << iy << std::endl;
	}

	std::cout << "finished" << std::endl;

	SDL_RenderPresent(renderer);

}

void Game::OnCleanup()
{
	SDL_DestroyTexture(img);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	std::cout << "Exiting" << std::endl;
	SDL_Quit();
}

int main(int argc, const char* argv[])
{
	Game game;
	return game.OnExecute();
}
