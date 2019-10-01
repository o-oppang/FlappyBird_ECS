//
//  FBEntityManager.cpp
//  Game
//
//  Created by 심다은 on 29/09/2019.
//

#include "FBEntityManager.hpp"
#include "FBEntityFactory.hpp"
#include "Component/Components.h"
#include "../render.hpp"

using namespace game;

FBEntityManager::FBEntityManager()
{

}

void FBEntityManager::init(std::shared_ptr<FBSpriteManager> spriteManager)
{
    _spriteManager = spriteManager;
    setEntities();
}

void FBEntityManager::setEntities()
{
    FBEntityFactory::Instance()->makeBackGround(_reg, _spriteManager->backgroundSprite);
    FBEntityFactory::Instance()->makeGround(_reg, _spriteManager->groundSprite);
    FBEntityFactory::Instance()->makeFlappyBird(_reg, _spriteManager->flappyBird.normal);
    FBEntityFactory::Instance()->makePipe(_reg, _spriteManager->pipe.top, _spriteManager->pipe.bottom);
}

void FBEntityManager::reset()
{
    auto view = _reg.template view<Position>();
    for (const entt::entity e : view) {
        _reg.destroy(e);
    }
    setEntities();
}

entt::registry& FBEntityManager::getRegistry()
{
    return _reg;
}

#pragma - system
#pragma -
void FBEntityManager::updateKeyInput(const SDL_Scancode key)
{
    updateFlappableEntityByKeyInput(key);
}

void FBEntityManager::updateFlappableEntityByKeyInput(const SDL_Scancode key)
{
    auto view = _reg.template view<KeyInput, Velocity, Flappable>();
    for (const entt::entity e : view) {
        float vel = view.get<Flappable>(e).flapVelocity;
        view.get<Velocity>(e).mag = vel ;
    }
    return;
}

#pragma -
void FBEntityManager::updatePosition(const double elapsedTime)
{
    updateAffectedGravityEntity(elapsedTime);
    updateEntityPosition(elapsedTime);
    updateFlappableSprite();
}

void FBEntityManager::updateAffectedGravityEntity(const double elapsedTime)
{
   auto view = _reg.template view<AffectedGravity, Velocity, Mass>();
   for (const entt::entity e : view) {
       if( _reg.has<PlayerMode>(e) ) {
           if( _reg.get<PlayerMode>(e).mode == PlayerModeEnum::GroundMode ) {
               continue;
           }
       }
       float g = view.get<AffectedGravity>(e).gravity;
       float m = view.get<Mass>(e).m;
       float a = m * g;
       view.get<Velocity>(e).mag += (a * elapsedTime) ;
   }
   return;
}

void FBEntityManager::updateEntityPosition(const double elapsedTime)
{
   auto view = _reg.template view<Position, Velocity>();
   for (const entt::entity e : view) {
       view.get<Position>(e).pos.x += ( view.get<Velocity>(e).x() * elapsedTime );
       view.get<Position>(e).pos.y += ( view.get<Velocity>(e).y() * elapsedTime );
   }
   return;
}

void FBEntityManager::updateFlappableSprite()
{
    auto view = _reg.view<Flappable, Velocity, HasSprite>();
    for (const entt::entity e : view) {
        Sprite::ID birdID;
        auto val = view.get<Velocity>(e);
        if( val.y() > 30 ) {
            birdID = _spriteManager->flappyBird.up;
        } else if (val.y() < -30) {
            birdID = _spriteManager->flappyBird.down;
        } else {
            birdID = _spriteManager->flappyBird.normal;
        }
        view.get<HasSprite>(e).identifier = birdID;
    }
}

void FBEntityManager::changePipeVelocityDir(const double elapsedTime) {
    auto view = _reg.view<Timer, VelocityChangeTime, Velocity>();
    for (const entt::entity e : view) {
        view.get<Timer>(e).t += elapsedTime;
        if( view.get<VelocityChangeTime>(e).t < view.get<Timer>(e).t) {
            view.get<Timer>(e).t = 0.0;
            view.get<Velocity>(e).dir.y *= -1.f;
        }
    }
}

void FBEntityManager::regenPipeIfNeeded(const double elapsedTime)
{
    static double time = 0;
    constexpr double regenTime = 3;
    time += elapsedTime;
    if( time > regenTime ) {
        FBEntityFactory::Instance()->makePipe(_reg, _spriteManager->pipe.top, _spriteManager->pipe.bottom);
        time = 0;
    }
}

void FBEntityManager::hitCheck()
{
    auto view = _reg.view<PlayerMode, Hittable>();
    for (const entt::entity e : view) {
        bool isGroundMode = false;
        auto hittableEntities = _reg.view<Hittable>();
        for (const entt::entity hittable : hittableEntities) {
            if (_reg.has<PlayerMode>(hittable)) {
                continue;
            }

            auto rect1 = getRect(e);
            auto rect2 = getRect(hittable);

            if( !rect1.overlap(rect2) ) {
                continue;
            } 

            if (_reg.has<Ground>(hittable)) {
                _reg.get<PlayerMode>(e).mode = PlayerModeEnum::GroundMode;
                if (_reg.has<Velocity>(e)) {
                    _reg.get<Velocity>(e).mag = 0;
                }
                isGroundMode = true;
            }
            if (_reg.has<ShouldNotHit>(hittable)) {
                _reg.get<PlayerMode>(e).mode = PlayerModeEnum::DeadMode;
                return;
            }
        }
        if( !isGroundMode ) {
            _reg.get<PlayerMode>(e).mode = PlayerModeEnum::FlyingMode;
        }
    }
}

Rect FBEntityManager::getRect(entt::entity e)
{
    auto rect = Rect();
    auto spriteRect = _spriteManager->getSprite(_reg.get<HasSprite>(e).identifier);
    rect.size = spriteRect.size();
    rect.pos =  _reg.get<Position>(e).pos;
    return rect;
}

bool FBEntityManager::deadCheck() {
    auto view = _reg.template view<PlayerMode>();
    for (const entt::entity e : view) {
        if( _reg.get<PlayerMode>(e).mode == PlayerModeEnum::DeadMode ) {
            return true;
        }
    }
    return false;
}

//MARK : - render
void FBEntityManager::renderEntities(SDL::QuadWriter& writer)
{
    auto sRenderEntity = [&](entt::entity e){
        auto id = this->_reg.get<HasSprite>(e).identifier;
        auto sprite = this->_spriteManager->getSprite(id);
        auto pos = this->_reg.get<Position>(e).pos;
        renderByPosition(writer, id, sprite, pos);
    };
    auto baseLayer = this->_reg.template view<Position, HasSprite, RenderBaseLayer>();
    for (const entt::entity e : baseLayer) {
        sRenderEntity(e);
    }
    auto middleLayer = this->_reg.template view<Position, HasSprite, RenderMiddleLayer>();
    for (const entt::entity e : middleLayer) {
        sRenderEntity(e);
    }
    auto topLayer = this->_reg.template view<Position, HasSprite, RenderTopLayer>();
    for (const entt::entity e : topLayer) {
        sRenderEntity(e);
    }
//renderByPosition(writer, _spriteManager->pipe.bottom, _spriteManager->getSprite(_spriteManager->pipe.bottom), {100.f, 150.f});

}
