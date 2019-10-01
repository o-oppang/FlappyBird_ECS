//
//  Rect.h
//  EnTT_Pacman
//
//  Created by 심다은 on 01/10/2019.
//

#ifndef Rect_h
#define Rect_h

#include <glm/glm.hpp>

namespace game {
    struct Rect {
        glm::vec2 pos;
        glm::vec2 size;

        bool overlap(Rect rect) {
            glm::vec2 r1 = pos + size;
            glm::vec2 r2 = rect.pos + rect.size;
            if( pos.x > r2.x || rect.pos.x > r1.x ) {
                return false;
            }

            if( pos.y > r2.y || rect.pos.y > r1.y ) {
                return false;
            }
            return true;
        }
    };
}

#endif /* Rect_h */
