#include "ASTest.h"

#include<iostream>

ASTest::ASTest()
{
    // ctor
    last = SDL_GetTicks();
}

ASTest::~ASTest()
{
    // dtor
}

void ASTest::onEvent(SDL_Event *event)
{
    if (event->type == SDL_QUIT) Application::getInstance()->popState();
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == 'd') Application::getInstance()->pushState(new ASTest());
}

// ?
void ASTest::onLoop()
{
    int now = SDL_GetTicks();
    double fps = 1000.0 / (now - last);
    std::cout << "FPS: " << fps << std::endl;
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

void ASTest::onFreeze()
{
    // when next state happens
}

void ASTest::onWakeUp()
{
    // when comes back to the state again
}
