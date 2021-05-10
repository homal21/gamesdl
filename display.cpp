#include <bits/stdc++.h>
#include"display.h"
#include <SDL_ttf.h>
#include <SDL.h>

using namespace std;
void render_image(SDL_Texture *texture,SDL_Rect rect)
{
    SDL_RenderCopy( renderer, texture, NULL, &rect );
}
void render_score(SDL_Texture *texture,SDL_Rect rect)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect );
}
void setup_score_text()
{
    SDL_Rect pos_score={50,75,40,50};
    TTF_Font *font_score = TTF_OpenFont("font.ttf",50);
    SDL_Color color = {0, 0, 0, 0};
    for (int i=0;i<=10000;i++)
    {
        SDL_Surface* message=TTF_RenderText_Solid(font_score,to_string(i).c_str(), color);
        score_texture[i]=SDL_CreateTextureFromSurface( renderer, message);
        TTF_SizeText(font_score,to_string(i).c_str(),&pos_score.w,&pos_score.h);
    }
    string s1="score:";
    string s2="high score:";
    SDL_Surface* message=TTF_RenderText_Solid(font_score,s1.c_str(), color);
    score_text_texture=SDL_CreateTextureFromSurface( renderer, message);
    message=TTF_RenderText_Solid(font_score,s2.c_str(), color);
    highscore_text_texture=SDL_CreateTextureFromSurface( renderer, message);
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
    vatcan_texture[0]=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/vatcan2.bmp");
    vatcan_texture[1]=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/map.bmp");
    map_texture=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/menu.bmp");
    menu_texture=SDL_CreateTextureFromSurface(renderer,surface);
    surface=SDL_LoadBMP("image/Button.bmp");
    button_texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
}
bool check_click(SDL_Rect rect, int x, int y)
{
    return (x >= rect.x && y >= rect.y && x < rect.x + rect.w && y < rect.y + rect.h);
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
