#include "ASTest.h"

#include<iostream>

ASTest::ASTest()
{
    // ctor
    running = true;
    last = SDL_GetTicks();
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
    int now = SDL_GetTicks();
    double fps = 1000.0 / (now - last);
    SDL_Log("FPS: %lf\n", fps);
    last = now;
}

void ASTest::onRender(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 30, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for(int i=0; i<600; i++)
    {
        for(int j=i%2; j<800; j+=2) SDL_RenderDrawPoint(renderer, j, i);
    }

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
