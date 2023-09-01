/*
Adedoyin Adelabu
A program to try and recreate the standard game tetris in C using the SDL library
First started August 20th 2023
*/
#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdbool.h>
#include<stdlib.h>
#include<math.h>


const int width = 640;
const int height = 480;
const int grid=22;
const int framex = (width/2 - 320/2);
const int framex2 = (framex+220); 
const int framey = 444;
bool start = false;
bool blockmade = false;
int b;
Uint32 diff;
Uint32 Currenttime;
Uint32 prevtime;
SDL_Event WindowEvent;

int randomnumber()
{
    return rand() % (6+1-0)+0;
};






struct Block
    {   char name[12];
        SDL_Point Aor;
        int x,y;
        double angl;
        int w,h;

    } Blocks[6];
    
    void update(float elapsed, SDL_Renderer *renderer, struct Block Blocks[]);

void FirstBlock(struct Block Blocks[], SDL_Renderer *  renderer);
 void UpdateBlock(struct Block Blocks[], float elapsed);

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        fprintf(stderr, "SDL initialization failed %s\n", SDL_GetError());
        return 1;
    };

    struct Block Blocks[] = { 
        "i-block.png\0",
        {44,0},
        framex + 66, 
        20,
        0,
        0,
        0,
        "o-block.png\0",
        {22,22},
        framex + 88, 
        20,
        0,
        0,
        0,
        "s-block.png\0",
        {33,11},
        framex + 66, 
        20,
        0,
        0,
        0,
        "l-block.png\0",
        {33,11},
        framex+66, 
        20,
        0,
        0,
        0,
        "z-block.png\0",
        {33,11},
        framex+88, 
        20,
        0,
        0,
        0,
        "j-block.png\0",
        {33,11},
        framex+66, 
        20,
        0,
        0,
        0,
        "t-block.png\0",
        {33,33},
        framex+66, 
        20, 
        0,
        0,
        0,
        };


    SDL_Window * window = SDL_CreateWindow
        (
        "TehTriss", // Window TITLE
        SDL_WINDOWPOS_CENTERED, // Window position
        SDL_WINDOWPOS_CENTERED, // 
        640,   //Pixel sizes
        480,    //
        SDL_WINDOW_SHOWN
        );

        if (!window) {
    fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
    SDL_Quit();
    return 1; 
    };

     SDL_Renderer *renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);
    
    
    
     prevtime = SDL_GetTicks();

    while(1)
    {
        if(SDL_PollEvent(&WindowEvent))
        {
            if(SDL_QUIT== WindowEvent.type)
            {
                break;
            }
        }
        Currenttime = SDL_GetTicks();
        diff = Currenttime - prevtime;
        float elapsed = diff/1000.0f;
        if(diff>=1000)
        {
            Blocks[b].y += 22;
             prevtime=Currenttime; 
        };
        update(elapsed, renderer, Blocks);
        SDL_Delay(floor(33.333f-elapsed));        

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}; 

void update(float elapsed, SDL_Renderer * renderer, struct Block Blocks[])
{
    
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    UpdateBlock(Blocks, elapsed);
     FirstBlock(Blocks,renderer);
   

    for(int y = 20; y <= 460; y+=grid )
    {
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderDrawLine(renderer,framex,y,framex+220,y);

    }; 

    for(int x = framex; x <= framex+220; x+=grid )
    {
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderDrawLine(renderer,x,20,x,460);

   };
     
    
    SDL_RenderPresent(renderer);
};

/*void UpdatePlayer(float elapsed)
{
    const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);

    if(keyboardstate[SDL_SCANCODE_SPACE])
        start = true;
}; */

//void RenderPlayer(void);

    void FirstBlock(struct Block Blocks[], SDL_Renderer * renderer)
    {
        
        if(blockmade==false)
        {
         b = 6;  
        };  
        SDL_Surface *imageSurface = IMG_Load(Blocks[b].name);
        Blocks[b].w=imageSurface->w;
        Blocks[b].h=imageSurface->h;
        SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect imageRect = { Blocks[b].x, Blocks[b].y, imageSurface->w, imageSurface->h };
        SDL_RenderCopyEx(renderer, imageTexture, NULL, &imageRect,Blocks[b].angl,&Blocks[b].Aor,SDL_FLIP_NONE);
        blockmade = true;

    };

    void UpdateBlock(struct Block Blocks[], float elapsed)
    {
        
        const Uint8 *input = SDL_GetKeyboardState(NULL);

         if (WindowEvent.type == SDL_KEYDOWN) {
             if(input[SDL_SCANCODE_D] || input[SDL_SCANCODE_RIGHT])
            {  
                    
                    if((Blocks[b].x-(framex+66))<=88)
                    {
                        Blocks[b].x += 22;

                        
                    }
                    
            }
                
             if(input[SDL_SCANCODE_A] || input[SDL_SCANCODE_LEFT])
            {   
                    
                    if(Blocks[b].x>=framex)
                    {
                        Blocks[b].x-=22;
                    }
            }

             if(input[SDL_SCANCODE_W] || input[SDL_SCANCODE_UP])
            {   
                    Blocks[b].angl+=90;
                    if(Blocks[b].angl>270)
                    {
                    Blocks[b].angl=0;
                    };

                    if(Blocks[b].y<1)
                    {
                        Blocks[b].y+=22;
                    }
                    if(Blocks[b].x>framex2-66)
                    {
                        Blocks[b].x -= 22;
                        
                    }
                    if(Blocks[b].x<framex)
                    {
                        Blocks[b].x += 22;
                        
                    }
                    
            }
                if(input[SDL_SCANCODE_S] || input[SDL_SCANCODE_DOWN])
            { 
                Blocks[b].y += 22;
            } 
        }
        
         /*   if(input[SDL_SCANCODE_D] || input[SDL_SCANCODE_RIGHT])
            {  
                    
                    if(Blocks[b].x<framex2)
                    {
                        Blocks[b].x += 22;
                        
                    }
            }
                
             if(input[SDL_SCANCODE_A] || input[SDL_SCANCODE_LEFT])
            {   
                    
                    if(Blocks[b].x>framex)
                    {
                        Blocks[b].x-=22;
                    }
            }

             if(input[SDL_SCANCODE_W] || input[SDL_SCANCODE_UP])
            {   
                    Blocks[b].angl+=90;
                    if(Blocks[b].angl>270)
                    {
                    Blocks[b].angl=0;
                    };

                    if(Blocks[b].y<=20)
                    {
                        Blocks[b].y+=22;
                    }
                    
            }
                if(input[SDL_SCANCODE_S] || input[SDL_SCANCODE_DOWN])
            { 
                Blocks[b].y += 22;
            } 
            */
        
    }
