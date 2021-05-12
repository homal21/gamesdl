#include <bits/stdc++.h>
#include"display.h"
#include <SDL_ttf.h>
#include <SDL.h>
#include"gameplay.h"
#include "SDL_mixer.h"

extern const int SCREEN_WIDTH = 1200;
extern const int SCREEN_HEIGHT= 600;
double k=0;
using namespace std;
void render_map(SDL_Texture *texture,SDL_Rect rect)
{
    SDL_Rect ScrR;
    ScrR = {k,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_RenderCopy( renderer, texture, &ScrR, &rect );
}

void game_play()
{
    SDL_Event  event;
    SDL_Rect posobj={300,420,40,50};
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
        render_score(score_texture[diem/20],pos_score);
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
            posobj={300,420,40,50};
        }
    }
    SDL_RenderPresent(renderer);
    if (collison==false)
    {
        k+=speed;
        diem++;
        if (diem/20 > highscore ) highscore=diem/20;
    }
    if (k>=SCREEN_WIDTH*2)
    {
        k=0;
        if (speed>=2.8) speed+=0.01;
            else
             speed+=0.2;
        if (speed>=4) speed = speed;
        kc_random=rand()%(450 -150+ 1)+150 ;
        random=rand()%2;

    }
    SDL_Delay(2);
    }
}
