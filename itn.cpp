
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

class klasa_ITN
{
 public:
 float posX;
 float posY;
 float predkosc;

 void int()
 {
     posX=1280;
     posY=100+rand()%520;
 }
 void update(SDL_Texture * tekstura)
 {
     SDL_Rect rect;
     rect.x=posX;
     rect.y=posY-20;
     rect.w=80;
     rect.h=40;
     SDL_RenderCopy(render,tekstura,NULL,&rect2);
 }
};
