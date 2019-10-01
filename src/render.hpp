//
//  render.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_RENDER_HPP
#define SYS_RENDER_HPP

#include <Simpleton/SDL/quad writer.hpp>

void fullRender(SDL::QuadWriter &writer, Sprite::ID id);

void renderByPosition(SDL::QuadWriter &writer, const Sprite::ID sprite, const Sprite::Rect rect, const glm::ivec2 pos);

#endif
