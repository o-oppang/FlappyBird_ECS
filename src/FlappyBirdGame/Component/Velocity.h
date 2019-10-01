//
//  Velocity.h
//  EnTT_Pacman
//
//  Created by 심다은 on 01/10/2019.
//

#ifndef Velocity_h
#define Velocity_h

#include <glm/glm.hpp>

struct Velocity
{
    float mag;
    glm::vec2 dir;

    Velocity(float aMag, float dir_x, float dir_y)
    :mag(aMag), dir({dir_x, dir_y})
    {
        float r = sqrt(pow(dir_x, 2) + pow(dir_y, 2));
        if( r != 1 ) {
            dir.x = dir_x / r;
            dir.y = dir_y / r;
        }
    }

    float x() {
        return mag * dir.x;
    }

    float y() {
        return mag * dir.y;
    }
};

#endif /* Velocity_h */
