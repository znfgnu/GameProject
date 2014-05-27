/**
 * AppState.h
 * klasa reprezentujaca stan programu (menu/rozgrywka/whatever)
*/

#ifndef APPSTATE_H
#define APPSTATE_H

#include <SDL2/SDL.h>

class AppState
{
    public:
        AppState() {};
        virtual ~AppState() {};

        virtual bool onInit() {return 1;};   // initializes state - returns if everything is alright

        // loop methods
        virtual void onEvent(SDL_Event*) {};    // handles events
        virtual void onLoop() {};   // moves objects, counts AI, whatever
        virtual void onRender(SDL_Window*, SDL_Renderer*) {};   // render image

        virtual void onFreeze() {}; // when next state happens
        virtual void onWakeUp() {}; // when next state finishes, we go back

        virtual bool finished() {return 1;}

    protected:
    private:
};

#endif // APPSTATE_H
