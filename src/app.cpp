//
//  app.cpp
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "app.hpp"

#include "../FlappyBirdGame/FlappyBirdGame.hpp"
#include "constants.hpp"
#include <Simpleton/SDL/texture.hpp>
#include <Simpleton/SDL/library.hpp>
#include <Simpleton/Time/synchronizer.hpp>

namespace {

SDL::Window::Desc getWinDesc(const int scaleFactor) {
    SDL::Window::Desc desc;
    desc.title = "Flappy bird";
    desc.size = viewSize * scaleFactor;
    desc.resizable = false;
    desc.openGL = false;
    return desc;
}

int getScaleFactor() {
        // Make the largest window possible with an integer scale factor
        SDL_Rect bounds;
        #if SDL_VERSION_ATLEAST(2, 0, 5)
        CHECK_SDL_ERROR(SDL_GetDisplayUsableBounds(0, &bounds));
        #else
        #warning SDL 2.0.5 or later is recommended
        CHECK_SDL_ERROR(SDL_GetDisplayBounds(0, &bounds));
        #endif
        const glm::ivec2 scale = {bounds.w / viewSize.x, bounds.h / viewSize.y};
        return std::max(1, std::min(scale.x, scale.y));
    }

}

void runFlappyBirdGame() {
    SDL::Window window = SDL::makeWindow(getWinDesc(getScaleFactor()));
    SDL::Renderer renderer = SDL::makeRenderer(window, true);
    SDL::Texture flappybirdTexture = renderer.texture("flappySprites.png");
    flappybirdTexture.blend(SDL_BLENDMODE_BLEND);
    Sprite::Sheet sheet = Sprite::makeSheetFromFile("flappySprites.atlas");
    CHECK_SDL_ERROR(SDL_RenderSetLogicalSize(renderer.get(), viewSize.x, viewSize.y));
    SDL::QuadWriter writer{renderer, sheet, flappybirdTexture};
    game::FlappyBirdGame game(sheet);
    game.init();

    int frame = 0;
    bool quit = false;
    // align the synchronizer with vsync
    renderer.present();
    while (!quit) {
    Time::Synchronizer sync{Time::sync_fps, fps};

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
            break;
        } else if (e.type == SDL_KEYDOWN) {
            game.input(e.key.keysym.scancode);
        }
    }

    if (!game.logic()) {
        quit = true;
    }

    renderer.clear();
    game.render(writer);
    ++frame;
    renderer.present();
    }
}
