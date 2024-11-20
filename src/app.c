#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "app.h"
#include "stdio.h"

#define SCREEN_WIDTH (320)
#define SCREEN_HEIGHT (240)

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *screen;
static SDL_Rect screen_rect = {0, 0, 0, 0};
static SDL_Event event;

static int screen_scale = 1;
static int working = 1;

static void adjust_frame(int width, int height) {
    float screenAR = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    float windowAR = (float)width / (float)height;
    if (screenAR < windowAR) {
        screen_rect.h = height;
        screen_rect.y = 0;
        screen_rect.w = height * screenAR;
        screen_rect.x = (width - screen_rect.w) / 2;
    } else {
        screen_rect.w = width;
        screen_rect.x = 0;
        screen_rect.h = width / screenAR;
        screen_rect.y = (height - screen_rect.h) / 2;
    }
}

static void set_scale(int scale) {
    SDL_SetWindowSize(window, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    screen_rect.x = 0;
    screen_rect.y = 0;
    screen_rect.w = SCREEN_WIDTH * scale;
    screen_rect.h = SCREEN_HEIGHT * scale;
}

void appInit(const char *title, int scale) {
    screen_scale = scale;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * screen_scale, SCREEN_HEIGHT * screen_scale, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    screen_rect.w = SCREEN_WIDTH * screen_scale;
    screen_rect.h = SCREEN_HEIGHT * screen_scale;

    working = 1;
}

void appFinish() {
    SDL_DestroyTexture(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int appProcessEvents() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                working = 0;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    int window_width = event.window.data1;
                    int window_height = event.window.data2;
                    adjust_frame(window_width, window_height);
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.mod & KMOD_ALT) {
                    switch (event.key.keysym.sym) {
                        case SDLK_1:
                            set_scale(1);
                            break;
                        case SDLK_2:
                            set_scale(2);
                            break;
                        case SDLK_3:
                            set_scale(3);
                            break;
                        case SDLK_4:
                            set_scale(4);
                            break;
                        case SDLK_5:
                            set_scale(5);
                            break;
                        case SDLK_6:
                            set_scale(6);
                            break;
                    }
                } else {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            working = 0;
                            break;
                    }
                }
                break;
        }
    }
    return working;
}

void appBeginRender() {
    SDL_SetRenderTarget(renderer, screen);
}

void appEndRender() {
    SDL_SetRenderTarget(renderer, NULL);
}

void appPresent() {
    SDL_RenderCopy(renderer, screen, NULL, &screen_rect);
    SDL_RenderPresent(renderer);

    SDL_Delay(5);
}