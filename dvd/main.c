#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// struct for the logo information
struct logo
{
    SDL_Rect rect;
    SDL_Surface *dvdLogo;
    SDL_Texture *texture;
    float posX, posY;
    float speedX, speedY;
    int r, g, b;
};

// functions
void renderLogo(SDL_Renderer *rend, struct logo *dvd);
void moveLogo(struct logo *dvd);
int checkHorizontalCollision(struct logo *dvd);
int checkVerticalCollision(struct logo *dvd);

int main(void)
{
    // SDL stuff
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("DVD", SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    SDL_Renderer *rend = SDL_CreateRenderer(win, SDL_RENDERER_ACCELERATED, 0);
    SDL_Event event;
    int running = 1;

    // logo initialization
    struct logo dvd;
    dvd.rect.w = 256;
    dvd.rect.h = 130;
    dvd.posX = SCREEN_WIDTH/2;
    dvd.posY = SCREEN_HEIGHT/2;
    dvd.speedX = -4.75f;
    dvd.speedY = -2.0f;
    dvd.dvdLogo = IMG_Load("logo.png");
    dvd.texture = SDL_CreateTextureFromSurface(rend, dvd.dvdLogo);
    dvd.r = 255;
    dvd.g = 0;
    dvd.b = 0;

    // game loop
    while(running)
    {
        // event processing
        while(SDL_PollEvent(&event))
            running = (event.type != SDL_QUIT);
        
        // processing
        moveLogo(&dvd);

        // rendering
        SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(rend);
        renderLogo(rend, &dvd);
        SDL_RenderPresent(rend);

        SDL_Delay(20);
    }
}

void renderLogo(SDL_Renderer *rend, struct logo *dvd)
{
    // color fading algorithm
    SDL_SetTextureColorMod(dvd->texture, dvd->r, dvd->g, dvd->b);
    if(dvd->r > 0 && dvd->b == 0)
    {
        (dvd->r)--;
        (dvd->g)++;
    }
    if(dvd->g > 0 && dvd->r == 0)
    {
        (dvd->g)--;
        (dvd->b)++;
    }
    if(dvd->b > 0 && dvd->g == 0)
    {
        (dvd->r)++;
        (dvd->b)--;
    }

    // render the logo
    SDL_RenderCopy(rend, dvd->texture, NULL, &(dvd->rect));
}

void moveLogo(struct logo *dvd)
{
    // update logo position
    dvd->posX += dvd->speedX;
    dvd->posY += dvd->speedY;

    // collision detection
    dvd->speedX *= (checkHorizontalCollision(dvd)) ? -1 : 1;
    dvd->speedY *= (checkVerticalCollision(dvd)) ? -1 : 1;

    // update rect position
    dvd->rect.x = dvd->posX;
    dvd->rect.y = dvd->posY;
}

int checkHorizontalCollision(struct logo *dvd)
{
    return ((dvd->posX + dvd->rect.w) >= SCREEN_WIDTH || dvd->posX <= 0);
}

int checkVerticalCollision(struct logo *dvd)
{
    return ((dvd->posY + dvd->rect.h) >= SCREEN_HEIGHT || dvd->posY <= 0);
}
