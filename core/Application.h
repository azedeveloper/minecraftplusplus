#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>
#include <SDL2/SDL.h>

class Application {
    public:
        void init();
        void update();
        void cleanup();

    private:
        SDL_Renderer* renderer = nullptr;
        SDL_Window* window = nullptr;
        bool running = true;
};

#endif
