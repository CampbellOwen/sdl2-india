#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class mTexture
{
	public:
		mTexture(SDL_Renderer* renderer);

		~mTexture();

		bool loadFromFile( std::string path );

		void free();

		void render(int x, int y);

		int getWidth();
		
		int getHeight();
	
	private:
		SDL_Texture* tex;
		SDL_Renderer* ren;
		int mWidth;
		int mHeight;
};
