//
//  FBEntityManager.hpp
//  Game
//
//  Created by 심다은 on 29/09/2019.
//

#ifndef FBEntityManager_hpp
#define FBEntityManager_hpp

#include <stdio.h>
#include <entt/entity/registry.hpp>
#include <SDL_scancode.h>
#include <Simpleton/SDL/quad writer.hpp>
#include "FBSpriteManager.hpp"
#include "Utill/Rect.h"


namespace game {
    class FBEntityManager
    {
    public:
        FBEntityManager();
        ~FBEntityManager() = default;
        void init(std::shared_ptr<FBSpriteManager> spriteManager);
        void reset();
        
        entt::registry& getRegistry();

        void updateKeyInput(const SDL_Scancode key);
        void updatePosition(const double elapsedTime);
        void regenPipeIfNeeded(const double elapsedTime);
        void changePipeVelocityDir(const double elapsedTime);
        void hitCheck();
        bool deadCheck();

        void renderEntities(SDL::QuadWriter& writer);

    private:
        void setEntities();
        
        void updateFlappableEntityByKeyInput(const SDL_Scancode key);
        void updateAffectedGravityEntity(const double elapsedTime);
        void updateEntityPosition(const double elapsedTime);
        void updateFlappableSprite();
        Rect getRect(entt::entity e);

        entt::registry _reg;
        std::shared_ptr<FBSpriteManager> _spriteManager;
    };
}
#endif /* FBEntityManager_hpp */
