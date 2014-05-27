#include "Application.h"
#include "ASTest.h"

Application::Application()
{
    window = NULL;
    renderer = NULL;
    dtmin = 40; // 25 FPS
}

Application::~Application()
{
    //dtor
}

bool Application::init(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;

    SDL_version compiled, linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    SDL_Log("Compiled with SDL %d.%d.%d",compiled.major, compiled.minor, compiled.patch);
    SDL_Log("Run with SDL %d.%d.%d rev. %s",linked.major, linked.minor, linked.patch, SDL_GetRevision());

    SDL_RendererInfo rendinfo;
    SDL_Log("Available:");
    int howmany = SDL_GetNumRenderDrivers();
    for (int i=0; i<howmany; i++)
    {
        SDL_GetRenderDriverInfo(i,&rendinfo);
        SDL_Log(" %d) %s", i+1, rendinfo.name);
    }

    SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
    if (window == NULL || renderer == NULL) return false;

    SDL_GetRendererInfo(renderer, &rendinfo);
    SDL_Log("Chosen: %s", rendinfo.name);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, 800, 600);

    return true;
}

int Application::run(int argc, char** argv)
{
    if (init(argc, argv) == false) return -1;
    // SDL initialized
    SDL_Log("Init OK.");

    pushState(new ASTest());
    SDL_Event event;

    unsigned frame = 0;
    int time_before = SDL_GetTicks();

    while(!statestack.empty())
    {
        AppState* state = statestack.back();

        int sizebefore = statestack.size();
        while(SDL_PollEvent(&event)) state->onEvent(&event);    // parse events, new state can happen
        int sizeafter = statestack.size();

        if (state->finished())
        {
            popState();
            continue;
        }

        if (sizeafter != sizebefore) continue;    // if new state happened

        state->onLoop();
        state->onRender(window, renderer);

        int dt = SDL_GetTicks() - time_before;
        if (dt <= dtmin) SDL_Delay(dtmin - dt);
        int time_now = SDL_GetTicks();
        SDL_assert(dt <= dtmin); // assert when fps lower (dt higher) than expected
        SDL_Log("Frame %d | FPS: %.2lf (%.2lf)", ++frame, 1000./(time_now-time_before), 1000./dt);
        time_before = time_now;
    }

    SDL_Log("Cleaning up...");
    //cleaning
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Log("Quitting.");
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
    delete state;
    statestack.pop_back();
    if (!statestack.empty()) statestack.back()->onWakeUp();
}
