//
//  FlappyBirdGame.hpp
//  Game
//
//  Created by 심다은 on 29/09/2019.
//

#ifndef FlappyBirdGame_hpp
#define FlappyBirdGame_hpp

#include <SDL_render.h>
#include <Simpleton/SDL/library.hpp>
#include <Simpleton/SDL/quad writer.hpp>
#include "FBSpriteManager.hpp"
#include "FBEntityManager.hpp"

namespace game
{
    class FlappyBirdGame
    {
    public:
        FlappyBirdGame(const Sprite::Sheet& sheet);
        void init();

        bool logic();
        void input(const SDL_Scancode key);
        void render(SDL::QuadWriter &writer);

    private:
        enum class State {
          playing,
          lost
        } state = State::playing;
        
        std::shared_ptr<FBSpriteManager> _spriteManager;
        std::shared_ptr<FBEntityManager> _entityManager;
    };
}

#include <stdio.h>

#endif /* FlappyBirdGame_hpp */
