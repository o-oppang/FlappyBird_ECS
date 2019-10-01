//
//  FBSpriteManager.hpp
//  GraphicsExample
//
//  Created by 심다은 on 28/09/2019.
//

#ifndef FBSpriteManager_hpp
#define FBSpriteManager_hpp

#include <stdio.h>
#include "Simpleton/Sprite/sheet.hpp"
#include "Simpleton/SDL/renderer.hpp"

//using namespace elsa;

namespace game {
    class FBSpriteManager
    {
    public:
        FBSpriteManager(const Sprite::Sheet& sheet);
        void init();
        Sprite::Rect getSprite(Sprite::ID id) const;

        Sprite::ID backgroundSprite;
        Sprite::ID groundSprite;
        Sprite::ID gameOverSprite;

        struct {
            Sprite::ID normal;
            Sprite::ID down;
            Sprite::ID up;
        } flappyBird;

        struct {
            Sprite::ID bottom;
            Sprite::ID top;
        } pipe;

        struct {
            Sprite::ID n0;
            Sprite::ID n1;
            Sprite::ID n2;
            Sprite::ID n3;
            Sprite::ID n4;
            Sprite::ID n5;
            Sprite::ID n6;
            Sprite::ID n7;
            Sprite::ID n8;
            Sprite::ID n9;
        } score;

    private:
        const Sprite::Sheet& _sheet;
    };
}

#endif /* FBSpriteManager_hpp */
