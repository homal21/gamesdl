
#include <SDL.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
SDL_Window* window = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* renderer = NULL;
void init()
{
   TTF_Init();
    window = SDL_CreateWindow( "game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

}
void render_image(SDL_Renderer *renderer,string path,SDL_Rect rect)
{

    SDL_Surface *surface = SDL_LoadBMP(path.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_RenderCopy( renderer, texture, NULL, &rect );
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

}
void render_text(SDL_Renderer *renderer,string path,SDL_Rect rect,int font_size)
{
    TTF_Font *font = TTF_OpenFont("font.ttf",font_size);
    TTF_SizeText(font,path.c_str(),&rect.w,&rect.h);
    SDL_Color color = {0, 125, 125, 0};
    SDL_Surface *message=TTF_RenderText_Solid(font, path.c_str(), color);
    message->w=rect.w;message->h=rect.h;
    SDL_Texture* texture=SDL_CreateTextureFromSurface( renderer, message);
    SDL_RenderCopy( renderer, texture, NULL, &rect );
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(message);
}
int main(int argc, char* args[])
{
    init();
    SDL_RenderClear(renderer);
    SDL_Rect r={400,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    render_image(renderer,"image/a.bmp",r);
    r={600,300,200,100};
    render_text(renderer,"ccccc",r,20);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
}
