//
//  render.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "render.hpp"
#include "constants.hpp"

// MARK : - falppy bird render
void fullRender(SDL::QuadWriter &writer, const Sprite::ID sprite)
{
  writer.tilePos({0, 0}, viewSize);
  writer.tileTex(sprite);
  writer.render();
}

void renderByPosition(SDL::QuadWriter &writer, const Sprite::ID sprite, const Sprite::Rect rect, const glm::ivec2 pos)
{
  writer.tilePos(pos, rect.size());
  writer.tileTex(sprite);
  writer.render();
}
