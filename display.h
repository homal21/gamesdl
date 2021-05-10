#ifndef _DISPLAY_H
#define _DISPLAY_H
#include<SDL.h>
extern SDL_Renderer *renderer;
extern SDL_Texture* score_texture[10000], *note, *score_text_texture, *highscore_text_texture;
extern SDL_Texture *vatcan_texture[5];
extern SDL_Texture *map_texture,*dino1_texture,*dino2_texture,*dino3_texture,*dino4_texture,*dino5_texture,*dino6_texture,*menu_texture,*button_texture;
void render_image(SDL_Texture *texture,SDL_Rect rect);

void render_score(SDL_Texture *texture,SDL_Rect rect);

void setup_score_text();

void setup_texture();

bool check_click(SDL_Rect rect, int x, int y);

bool check_collison(SDL_Rect &posobj, SDL_Rect &barrier);
#endif // _DISPLAY_H
