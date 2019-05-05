
class klasa_przeciwnik
{
 public:
 float posX;
 float posY;
 float predkosc;

bool aktywny=true;

void init()
 {
     posX=1280;
     posY=100+((rand()%450)/86)*86+40;
 }
 void update(SDL_Texture * tekstura, float postac_y)
 {


     if(aktywny=true)
     {
        posX=posX-10;


     if(posX<0)
     {
         aktywny=false;
     }

     SDL_Rect rect;
     rect.x=posX;
     rect.y=posY-20;
     rect.w=80;
     rect.h=40;
     SDL_RenderCopy(render,tekstura,NULL,&rect);

     if(posX>100&&posX<180&&posY+40>postac_y&&posY<postac_y+40)

   {
       exit(0);
   }

 }
 }
};
