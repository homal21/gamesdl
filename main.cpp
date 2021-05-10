#include <SDL.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "display.h"
#include "gameplay.h"
using namespace std;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT= 600;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* score_texture[10000], *note, *score_text_texture, *highscore_text_texture;
SDL_Texture* vatcan_texture[5];
SDL_Texture *map_texture,*dino1_texture,*dino2_texture,*dino3_texture,*dino4_texture,*dino5_texture,*dino6_texture,*menu_texture,*button_texture;
//double k=0;
void init()
{
   TTF_Init();
    window = SDL_CreateWindow( "Dino In Sahara", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
}
int show_menu()
{
    SDL_Rect menu_background = {0,0,1200,600};
    SDL_Rect play_button_Dest = {500,250,120,60};
    SDL_Rect play_button_Scr = {0,0,120,60};
    SDL_Rect play_button_bright_Scr = {0,60,120,60};
    SDL_Rect exit_button_Dest = {500,450,120,60};
    SDL_Rect exit_button_Scr = {240,0,120,60};
    SDL_Rect exit_button_bright_Scr = {240,60,120,60};
    SDL_RenderCopy(renderer,menu_texture,NULL,&menu_background);
    SDL_RenderCopy(renderer,button_texture,&play_button_Scr,&play_button_Dest);
    SDL_RenderCopy(renderer,button_texture,&exit_button_Scr,&exit_button_Dest);
    int x,y;
    bool selected[2]={0,0};
    SDL_Rect pos_menu[2];
    pos_menu[0] = play_button_Dest;
    pos_menu[1] = exit_button_Dest;
    SDL_Event event;
    while(1)
    while(SDL_PollEvent(&event))
    {
     if (event.type == SDL_MOUSEMOTION)
     {
        x = event.motion.x;
        y = event.motion.y;
            if (check_click(pos_menu[0],x,y))
            {
                if (selected[0]==0)
                {
                    selected[0] = 1;
                    SDL_RenderCopy(renderer,button_texture,&play_button_bright_Scr,&play_button_Dest);
                }
            }
            else
            {
                if (selected[0]==1)
                {
                    selected[0] = 0;
                    SDL_RenderCopy(renderer,button_texture,&play_button_Scr,&play_button_Dest);
                }

            }
            if (check_click(pos_menu[1],x,y))
            {
                if (selected[1]==0)
                {
                    selected[1] = 1;
                    SDL_RenderCopy(renderer,button_texture,&exit_button_bright_Scr,&exit_button_Dest);
                }
            }
            else
            {
                if(selected[1])
                {
                    selected[1] = 0;
                    SDL_RenderCopy(renderer,button_texture,&exit_button_Scr,&exit_button_Dest);
                }

            }
        }
        x = event.button.x;
        y = event.button.y;
        for (int i = 0; i <2; i++)
         if (check_click(pos_menu[i],x,y))
          if (event.type == SDL_MOUSEBUTTONDOWN) return i;
        SDL_RenderPresent(renderer);
    }
}

int main(int argc, char* argv[])
{
    init();
    setup_score_text();
    setup_texture();
    int showmenu = show_menu();
    if (showmenu==0) game_play();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}
