#include <SDL.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "display.h"
using namespace std;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT= 600;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* score_texture[10000], *note, *score_text_texture, *highscore_text_texture;
SDL_Texture* vatcan_texture[5];
SDL_Texture *map_texture,*dino1_texture,*dino2_texture,*dino3_texture,*dino4_texture,*dino5_texture,*dino6_texture,*menu_texture,*button_texture;
double k=0;
void init()
{
   TTF_Init();
    window = SDL_CreateWindow( "Dino In Sahara", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
}
void render_map(SDL_Texture *texture,SDL_Rect rect)
{
    SDL_Rect ScrR;
    ScrR = {k,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_RenderCopy( renderer, texture, &ScrR, &rect );
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

void game_play()
{
    SDL_Event  event;
    SDL_Rect posobj={100,420,40,50};
    SDL_Rect pos_note={200,100,40,50};
    SDL_Rect pos_score={1150,0,40,50};
    SDL_Rect pos_highscore={1150,60,40,50};
    SDL_Rect pos_score_text={1000,0,80,50};
    SDL_Rect pos_highscore_text={1000,60,120,50};
    TTF_Font *font = TTF_OpenFont("font.ttf", 75);
    string s="ban da thua, an SPACE de choi lai, an ESC de thoat";
    TTF_SizeText(font,s.c_str(), &pos_note.w,&pos_note.h);
    SDL_Color color = {0, 0, 0, 0};
    SDL_Surface* message = TTF_RenderText_Solid(font, s.c_str(), color);
    note = SDL_CreateTextureFromSurface( renderer, message);
    SDL_FreeSurface(message);
    int y_obj_max=250;
    int y_obj_min=420;
    bool check_move;
    bool is_flying;
    bool collison=false;
    double speed=1;
    int cong=0;
    int diem=0;
    int random=rand()% 2;
    int highscore=0;
    int kc_random=rand()%(450 -150+ 1)+150;
    while(k<SCREEN_WIDTH*2)
    {
    SDL_Rect r={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_RenderClear(renderer);
    render_map(map_texture,r);
    SDL_Rect barrier1={1200-k,400,50,75};
    SDL_Rect barrier2={2400-kc_random-k,400,50,75};
    cong++;
     if (collison==false)
     {
      if (is_flying==false)
      while (SDL_PollEvent( &event) != 0)
        if (event.type == SDL_KEYUP)
         switch( event.key.keysym.sym )
      {
         case SDLK_SPACE:
             check_move=true;
             is_flying=true;
             break;
      }
      if (is_flying)
        if(check_move) posobj.y-=1;
      if (posobj.y==y_obj_max) check_move= false;
      if (is_flying)
       if (check_move==false) posobj.y+=2;
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
        if (k<1200) render_image(vatcan_texture[random],barrier1);
        render_image(vatcan_texture[random],barrier2);
        render_score(score_text_texture,pos_score_text);
        render_score(highscore_text_texture,pos_highscore_text);
        render_score(score_texture[diem/10],pos_score);
        render_score(score_texture[highscore],pos_highscore);
    if (check_collison(posobj,barrier1)||check_collison(posobj,barrier2))
    {
        collison=true;
    }
    if (collison==true)
    {
        posobj.y+=1;
        is_flying=true;
        render_score(note,pos_note);
    }
    while (posobj.y>=700)
    {
        while (SDL_PollEvent( &event) != 0)
        if (event.type == SDL_KEYUP)
        switch( event.key.keysym.sym )
        {
        case SDLK_ESCAPE:
             exit(0);
        case SDLK_SPACE:
            k=0;
            speed=1;
            diem=0;
            collison=false;
            is_flying=false;
            posobj={100,420,40,50};
        }
    }
    SDL_RenderPresent(renderer);
    if (collison==false)
    {
        k+=speed;
        diem++;
        if (diem/10 > highscore ) highscore=diem/10;
    }
    if (k>=SCREEN_WIDTH*2)
    {
        k=0;
        if (speed>=2.8) speed+=0.01;
            else
             speed+=0.2;
        kc_random=rand()%(450 -150+ 1)+150 ;
        random=rand()%2;

    }
    SDL_Delay(2);
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
