//
//  FBSpriteManager.cpp
//  GraphicsExample
//
//  Created by 심다은 on 28/09/2019.
//

#include "FBSpriteManager.hpp"
#include <SDL_render.h>
#include <Simpleton/SDL/texture.hpp>

using namespace game;

FBSpriteManager::FBSpriteManager(const Sprite::Sheet& sheet)
: _sheet(sheet)
{

}

void FBSpriteManager::init()
{
    backgroundSprite = _sheet.getIDfromName("background");
    groundSprite = _sheet.getIDfromName("ground");
    gameOverSprite = _sheet.getIDfromName("gameover");
    flappyBird.normal = _sheet.getIDfromName("flappy center");
    flappyBird.down = _sheet.getIDfromName("flappy down");
    flappyBird.up = _sheet.getIDfromName("flappy top");
    pipe.bottom = _sheet.getIDfromName("pipe bottom");
    pipe.top = _sheet.getIDfromName("pipe top");
    score.n0 = _sheet.getIDfromName("score 0");
    score.n1 = _sheet.getIDfromName("score 1");
    score.n2 = _sheet.getIDfromName("score 2");
    score.n3 = _sheet.getIDfromName("score 3");
    score.n4 = _sheet.getIDfromName("score 4");
    score.n5 = _sheet.getIDfromName("score 5");
    score.n6 = _sheet.getIDfromName("score 6");
    score.n7 = _sheet.getIDfromName("score 7");
    score.n8 = _sheet.getIDfromName("score 8");
    score.n9 = _sheet.getIDfromName("score 9");
}

Sprite::Rect FBSpriteManager::getSprite(const Sprite::ID id) const
{
    return _sheet.getSprite(id);
}
