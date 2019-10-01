//
//  FBEntityManager.cpp
//  Game
//
//  Created by 심다은 on 29/09/2019.
//

#include "FBEntityFactory.hpp"
#include "Component/Components.h"
//#include <cstdlib>

using namespace game;

entt::entity FBEntityFactory::makeBackGround(entt::registry& reg, Sprite::ID id)
{
    const entt::entity e = reg.create();
    reg.assign<Position>(e, glm::vec2{0.f, 0.f});
    reg.assign<HasSprite>(e, id);
    reg.assign<RenderBaseLayer>(e);
    return e;
}

entt::entity FBEntityFactory::makeGround(entt::registry& reg, Sprite::ID id)
{
    const entt::entity e = reg.create();
    reg.assign<Position>(e, glm::vec2{0.f,202.f});
    reg.assign<Hittable>(e);
    reg.assign<Ground>(e);
    reg.assign<HasSprite>(e, id);
    reg.assign<RenderMiddleLayer>(e);
    return e;
}


entt::entity FBEntityFactory::makeFlappyBird(entt::registry& reg, Sprite::ID id)
{
    const entt::entity e = reg.create();
    reg.assign<KeyInput>(e);
    reg.assign<Flappable>(e, 100.f);
    reg.assign<PlayerMode>(e, PlayerModeEnum::GroundMode);
    reg.assign<AffectedGravity>(e);
    reg.assign<Mass>(e, 15.f);
    reg.assign<Velocity>(e, 0.f, 0.f, -1.f);
    reg.assign<Position>(e, glm::vec2{20.f, 100.f});
    reg.assign<Hittable>(e);
    reg.assign<HasSprite>(e, id);
    reg.assign<RenderTopLayer>(e);
    return e;
}

entt::entity FBEntityFactory::makePipe(entt::registry& reg, Sprite::ID topId, Sprite::ID bottomId)
{
    if( rand() % 2 ) {
        return makeTopPipe(reg, topId);
    } else {
        return makeBottomPipe(reg, bottomId);
    }
}

entt::entity FBEntityFactory::makeBottomPipe(entt::registry& reg, Sprite::ID id)
{
    double random = ( rand() % 100 ) / 100.0;
    const entt::entity e = reg.create();
    reg.assign<Velocity>(e, 50.f + random * 10.f, -1.f, -1.f);
    reg.assign<Position>(e, glm::vec2{150.f, 120.f + random * 50});
    reg.assign<Hittable>(e);
    reg.assign<Timer>(e, 0.0);
    reg.assign<VelocityChangeTime>(e, random * 4 + 0.3);
    reg.assign<ShouldNotHit>(e);
    reg.assign<HasSprite>(e, id);
    reg.assign<RenderMiddleLayer>(e);
    return e;
}

entt::entity FBEntityFactory::makeTopPipe(entt::registry& reg, Sprite::ID id)
{
    double random = ( rand() % 100 ) / 100.0;
    const entt::entity e = reg.create();
    reg.assign<Velocity>(e, 50.f + random * 10.f, -1.f, 1.f);
    reg.assign<Position>(e, glm::vec2{150.f, -50.f - random * 50});
    reg.assign<Hittable>(e);
    reg.assign<Timer>(e, 0.0);
    reg.assign<VelocityChangeTime>(e, random * 4 + 0.3);
    reg.assign<ShouldNotHit>(e);
    reg.assign<HasSprite>(e, id);
    reg.assign<RenderMiddleLayer>(e);
    return e;
}
