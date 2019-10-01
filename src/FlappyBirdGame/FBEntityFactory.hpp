//
//  FBEntityManager.hpp
//  Game
//
//  Created by 심다은 on 29/09/2019.
//

#include <stdio.h>
#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>
#include "Simpleton/Sprite/sheet.hpp"
#include "Utill/Singleton.hpp"

namespace game {
    class FBEntityFactory: public Singleton<FBEntityFactory>
    {
    public:
        entt::entity makeBackGround(entt::registry& reg, Sprite::ID id);
        entt::entity makeGround(entt::registry& reg, Sprite::ID id);
        entt::entity makeFlappyBird(entt::registry& reg, Sprite::ID id);
        entt::entity makePipe(entt::registry& reg, Sprite::ID topId, Sprite::ID bottomId);

    private:
        entt::entity makeBottomPipe(entt::registry& reg, Sprite::ID id);
        entt::entity makeTopPipe(entt::registry& reg, Sprite::ID id);
    };
}

