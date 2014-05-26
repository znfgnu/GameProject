#include "Application.h"
#include "ASTest.h"

Application::Application()
{
    window = NULL;
    renderer = NULL;
}

Application::~Application()
{
    //dtor
}

bool Application::init(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;

    SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
    if (window == NULL || renderer == NULL) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, 800, 600);

    return true;
}

int Application::run(int argc, char** argv)
{
    if (init(argc, argv) == false) return -1;
    // SDL initialized

    pushState(new ASTest());
    SDL_Event event;

    while(!statestack.empty())
    {
        AppState* state = statestack.back();

        int sizebefore = statestack.size();
        while(SDL_PollEvent(&event)) state->onEvent(&event);    // parse events
        int sizeafter = statestack.size();

        if (sizeafter != sizebefore)    // if new state happened or existing removed
        {
            while (!todestroy.empty()) { delete todestroy.back(); todestroy.pop_back(); }
            continue;
        }

        state->onLoop();
        state->onRender(window, renderer);
    }

    //cleaning
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void Application::pushState(AppState* state)
{
    if (!statestack.empty()) statestack.back()->onFreeze();
    statestack.push_back(state);
}

void Application::popState()
{
    AppState* state = statestack.back();
    todestroy.push_back(state); // destructing state instance in main loop
    statestack.pop_back();
    if (!statestack.empty()) statestack.back()->onWakeUp();
}
