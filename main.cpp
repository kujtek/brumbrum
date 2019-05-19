#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <windows.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>


using namespace std;

#include "fps.cpp"

SDL_Window * okno;
SDL_Renderer * render;
SDL_Event zdarzenie;
SDL_Rect rect1, rect2;

const UINT8 * keystate;

SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
         //SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( render, loadedSurface );
        if( newTexture == NULL )
        {
            //SDL_Log( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}
#include "klasy.cpp"

int main(int argc, char*args[])
{
 SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
 okno = SDL_CreateWindow("Gra",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,720,0);
 render = SDL_CreateRenderer(okno,-1,SDL_RENDERER_ACCELERATED);

 klasa_fps fps;

 TTF_Init();

 TTF_Font * arial = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf",40);


 SDL_Surface * surface_tekst;
 SDL_Texture * texture_tekst;

 int klatka=0;

 float posY = 360;
 float velY = 0;

 int punkty=0;

 vector < klasa_przeciwnik > v_przeciwnik;
       SDL_Texture*droga=loadTexture("GRAFIKA/tlo.bmp");
       SDL_Texture*postac=loadTexture("GRAFIKA/postac.bmp");
       SDL_Texture*przeciwnik=loadTexture("GRAFIKA/ITN.bmp");

 while(true)
 {
    fps.start();
    klatka++;
    keystate = SDL_GetKeyboardState(NULL);



        {//zdarzenie
            while(SDL_PollEvent(&zdarzenie))
            {
                if(zdarzenie.type==SDL_QUIT)
                {
                    exit(0);
                }
            }
            {//wydarzenie
                if(klatka%10==0)
                {
                    punkty=punkty+1;
                }
                if(velY<1&&velY>-1)
                {
                    if(klatka%3==0)
                    {
                        punkty=punkty+1;
                    }
                }

            }
            {//sapwn samochody
                if(klatka%20 == 0)
                {
                    klasa_przeciwnik obj;
                    obj.init();
                    v_przeciwnik.push_back(obj);
                }
                for(int loop=0;loop<v_przeciwnik.size();loop++)
                {
                    if(v_przeciwnik.at(loop).aktywny==false)
                    {
                       //v_przeciwnik(loop).pop_back();
                    }

                }
            }
            {//sterowanie
                if(keystate[SDL_SCANCODE_DOWN])
                {
                    if(velY<12)
                    {
                        velY=velY+1.5;
                    }
                }
                if(keystate[SDL_SCANCODE_UP])
                {
                    if(velY>-12)
                    {
                        velY=velY-1.5;
                    }
                }
                velY=velY*0.9;

            }


            {//fizyka
                posY=posY+velY;

                if(posY<120)
                    {
                        velY=velY+1;
                        velY=velY*0.9;
                    }
                if(posY>560)
                    {
                        velY=velY-1;
                        velY=velY*0.9;
                    }
            }

            {//render / tlo
                {
                 SDL_RenderClear(render);
                }

           {//droga
              for(int loop=0;loop<8;loop++)
            {
                rect2.x=loop*200-(klatka*7)%200;
                rect2.y=0;
                rect2.w=200;
                rect2.h=720;
                SDL_RenderCopy(render,droga,NULL,&rect2);
            }
            {//postac
                rect2.x=100;
                rect2.y=posY;
                rect2.w=80;
                rect2.h=40;
                SDL_RenderCopyEx(render,postac,NULL,&rect2,velY*4,NULL,SDL_FLIP_NONE);
            }
            {//przeciwnik
                for(int loop=0;loop<v_przeciwnik.size();loop++)
                {
                    v_przeciwnik.at(loop).update(przeciwnik,posY);
                }
            }
            {//tekst
                SDL_Color kolor = {255,255,255};
                stringstream ss;
                ss<<punkty;

                surface_tekst = TTF_RenderText_Blended(arial,ss.str().c_str(),kolor);

                texture_tekst = SDL_CreateTextureFromSurface(render,surface_tekst);

                rect2.x=0;rect2.y=0;rect2.w=200;rect2.h=100;

                SDL_RenderCopy(render,texture_tekst,NULL,&rect2);

                SDL_DestroyTexture(texture_tekst);
                SDL_FreeSurface(surface_tekst);


            }
           }
        }
        SDL_RenderPresent(render);
        fps.end();
        }

 }
}

