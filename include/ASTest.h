#ifndef ASTEST_H
#define ASTEST_H

#include "AppState.h"
#include "Application.h"

class ASTest : public AppState
{
    public:
        ASTest();
        ~ASTest();
        void onEvent(SDL_Event*);
        void onLoop();
        void onRender(SDL_Window*, SDL_Renderer*);

        void onFreeze();
        void onWakeUp();
        bool finished();

    protected:
    private:
        bool running;
        int frame;
};

#endif // ASTEST_H
