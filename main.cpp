#include <SDL.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>

using namespace std;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 600;
SDL_Window* window = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* g_Object = NULL;
int k=0;
void init()
{
   TTF_Init();
    window = SDL_CreateWindow( "game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

}
void render_map(SDL_Renderer *renderer,string path,SDL_Rect rect)
{
    SDL_Surface *surface = SDL_LoadBMP(path.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_Rect ScrR;
    ScrR.x=k;
    ScrR.y=0;
    ScrR.w=SCREEN_WIDTH;
    ScrR.h=SCREEN_HEIGHT;
    SDL_RenderCopy( renderer, texture, &ScrR, &rect );
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

}
void render_image(SDL_Renderer *renderer,string path,SDL_Rect rect)
{

    SDL_Surface *surface = SDL_LoadBMP(path.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_RenderCopy( renderer, texture, NULL , &rect );
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
    int dem=0;
    while (k<=SCREEN_WIDTH)
    {
    SDL_Rect r={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    render_map(renderer,"image/map.bmp",r);
    r={100,450,54,85};
    if (dem%3==0) render_image(renderer,"image/zom1.bmp",r);
    if (dem%3==1) render_image(renderer,"image/zom2.bmp",r);
    if (dem%3==2) render_image(renderer,"image/zom3.bmp",r);

    SDL_RenderPresent(renderer);
    dem++;
    k+=8;
    if (k==SCREEN_WIDTH) k=0;
    SDL_Delay(100);
    }
    SDL_Delay(5000);
}
