#include "ASTest.h"

#include<iostream>

ASTest::ASTest()
{
    // ctor
    running = true;
    frame=0;
//    last = 0;
}

ASTest::~ASTest()
{
    // dtor
}

void ASTest::onEvent(SDL_Event *event)
{
    if (event->type == SDL_QUIT) running = false;
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == 'd') Application::getInstance()->pushState(new ASTest());
}

// ?
void ASTest::onLoop()
{
    frame++;
//    int now = SDL_GetTicks();
//    double fps = 1000.0 / (now - last);
//    if(last) SDL_Log("FPS: %lf\n", fps);
    //SDL_assert(fps<30);
//    last = now;
}

void ASTest::onRender(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 30, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    /*for(int i=0; i<600; i++)
    {
        for(int j=i%10; j<800; j+=20) SDL_RenderDrawPoint(renderer, j, i);
    }*/
    SDL_RenderDrawLine(renderer,0,0,frame%800,600);

    // Finally
    SDL_RenderPresent(renderer);
}

bool ASTest::finished()
{
    return !running;
}

void ASTest::onFreeze()
{
    // when next state happens
}

void ASTest::onWakeUp()
{
    // when comes back to the state again
}
