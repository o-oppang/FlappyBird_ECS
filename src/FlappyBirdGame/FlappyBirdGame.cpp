//
//  FlappyBirdGame.cpp
//  Game
//
//  Created by 심다은 on 29/09/2019.
//

#include "FlappyBirdGame.hpp"
#include <thread>
#include "../render.hpp"
#include "Component/Components.h"

using namespace game;

FlappyBirdGame::FlappyBirdGame(const Sprite::Sheet& sheet)
:_spriteManager(new FBSpriteManager(sheet)), _entityManager(new FBEntityManager())
{

}

void FlappyBirdGame::init()
{
    _spriteManager->init();
    _entityManager->init(_spriteManager);
}

void FlappyBirdGame::input(const SDL_Scancode key)
{
    if (state == State::playing) {
        _entityManager->updateKeyInput(key);
        std::this_thread::sleep_for(std::chrono::microseconds(200));
    } else {
        _entityManager->reset();
        state = State::playing;
    }
}

bool FlappyBirdGame::logic()
{
    if(state == State::lost) {
        return true;
    }

    static auto previous = std::chrono::system_clock::now();
    auto current = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = current - previous;
    previous = current;

    auto elapsed = elapsedTime.count();
    _entityManager->regenPipeIfNeeded(elapsed);
    _entityManager->updatePosition(elapsed);
    _entityManager->changePipeVelocityDir(elapsed);
    _entityManager->hitCheck();
    if( _entityManager->deadCheck() ) {
        state = State::lost;
    }

    return true;
}

void FlappyBirdGame::render(SDL::QuadWriter &writer)
{
    _entityManager->renderEntities(writer);

    if( state == State::lost ) {
        auto sp = _spriteManager->gameOverSprite;
        renderByPosition(writer, sp, _spriteManager->getSprite(sp), {24, 60});
        return;
    }
}
