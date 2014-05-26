#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include "AppState.h"
#include <vector>

class Application
{
    public:
        virtual ~Application();
        static Application* getInstance()
        {
            static Application instance;
            return &instance;
        }

        int run(int, char**);   // runs application

        void pushState(AppState*);  // pushes state on statestack
        void popState();    // pops the last state
        void clearStateStack(); // quits

    protected:
    private:
        Application();
        bool init(int, char**);  // initiates SDL

        std::vector<AppState*> statestack;
        std::vector<AppState*> todestroy;

        SDL_Window* window;
        SDL_Renderer* renderer;
};

#endif // APPLICATION_H
