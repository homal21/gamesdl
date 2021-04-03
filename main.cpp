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
SDL_Texture *map_texture,*dino1_texture,*dino2_texture,*dino3_texture,*dino4_texture,*dino5_texture,*dino6_texture,*vatcan1_texture,*vatcan2_texture;
SDL_Event* event ;
double k=0;
void init()
{
   TTF_Init();
    window = SDL_CreateWindow( "ditmecuocdoi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
}
void render_map(SDL_Texture *texture,SDL_Rect rect)
{
    SDL_Rect ScrR;
    ScrR = {k,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_RenderCopy( renderer, texture, &ScrR, &rect );
}
void render_image(SDL_Texture *texture,SDL_Rect rect)
{
    SDL_RenderCopy( renderer, texture, NULL, &rect );
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
void setup_texture()
{
    SDL_Surface *surface;
    surface=SDL_LoadBMP("image/dino1.bmp");
    dino1_texture=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/dino2.bmp");
    dino2_texture=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/dino3.bmp");
    dino3_texture=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/dino4.bmp");
    dino4_texture=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/dino5.bmp");
    dino5_texture=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/dino6.bmp");
    dino6_texture=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/vatcan1.bmp");
    vatcan1_texture=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/vatcan2.bmp");
    vatcan2_texture=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/map.bmp");
    map_texture=SDL_CreateTextureFromSurface(renderer,surface);

}
bool check_collison(SDL_Rect &posobj, SDL_Rect &barrier)
{
  int x1_obj=posobj.x;
  int x4_obj=posobj.x+posobj.w;
  int y1_obj=posobj.y;
  int y4_obj=posobj.y+posobj.h;

  int x1_barrier=barrier.x;
  int x4_barrier=barrier.x+barrier.w;
  int y1_barrier=barrier.y;
  int y4_barrier=barrier.y+barrier.h;
  if (x4_obj>=x1_barrier && x4_obj<=x4_barrier)
    if (y4_obj>=y1_barrier && y4_obj<=y4_barrier)
     return true;
  if (x1_obj>x1_barrier && x1_obj<x4_barrier)
    if (y4_obj>y1_barrier && y4_obj<y4_barrier)
    return true;
  return false;
}

int main(int argc, char* argv[])
{
    init();
    setup_texture();
    SDL_Event  event;
    bool quit=false;
    SDL_Rect posobj={100,420,40,50};
    int y_obj_max=250;
    int y_obj_min=420;
    bool check_move;
    bool is_flying;
    bool collison=false;
    double dem=1;
    int cong=0;
    while(k<SCREEN_WIDTH*2)
    {
    SDL_Rect r={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_RenderClear(renderer);
    render_map(map_texture,r);
    SDL_Rect barrier={1024-k,400,60,75};
    cong++;
     if (collison==false)
     {
      if (is_flying==false)
      while (SDL_PollEvent( &event) != 0)
        if (event.type == SDL_KEYUP)
         switch( event.key.keysym.sym )
      {
         case SDLK_UP:
             check_move=true;
             is_flying=true;
             break;
      }
      if (is_flying)
        if(check_move) posobj.y-=1;
      if (posobj.y==y_obj_max) check_move= false;
      if (is_flying)
       if (check_move==false) posobj.y+=1;
      if (posobj.y==y_obj_min)
      {
          check_move=true;
          is_flying=false;
      }
     }
    if (is_flying) render_image(dino1_texture,posobj);
     else
     {
         if (cong%6==0) render_image(dino1_texture,posobj);
         if (cong%6==1) render_image(dino2_texture,posobj);
         if (cong%6==2) render_image(dino3_texture,posobj);
         if (cong%6==3) render_image(dino4_texture,posobj);
         if (cong%6==4) render_image(dino5_texture,posobj);
         if (cong%6==5) render_image(dino6_texture,posobj);
     }
    if(k<1024) render_image(vatcan1_texture,barrier);
    else
    {
        barrier={2048-k,400,60,75};
        render_image(vatcan2_texture,barrier);
    }
    if (check_collison(posobj,barrier))
    {
        collison=true;
    }
    if (collison==true)
    {
        posobj.y+=1;
        is_flying=true;
    }
    if (posobj.y>=700) SDL_Delay(10000);
    SDL_RenderPresent(renderer);
    if (collison==false) k+=dem;
    if (k>=SCREEN_WIDTH*2)
    {
        k=0;
        dem+=0.05;
    }
    SDL_Delay(2);
    }
}
