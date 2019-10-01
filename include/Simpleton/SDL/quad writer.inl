//
//  quad writer.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

inline SDL::QuadWriter::QuadWriter(
  Renderer &renderer,
  const Sprite::Sheet &sheet,
  const Texture &texture
) : renderer{renderer},
    spritesheet{sheet},
    texture{texture},
    srcRect{0, 0, 0, 0},
    dstRect{0, 0, 0, 0},
    angle{0.0} {}

inline void SDL::QuadWriter::tilePos(
  const glm::ivec2 pos,
  const glm::ivec2 size,
  const double ang
) {
  dstRect.x = pos.x;
  dstRect.y = pos.y;
  dstRect.w = size.x;
  dstRect.h = size.y;
  angle = ang;
}

inline void SDL::QuadWriter::tileTex(const Sprite::Rect rect) {
  // swap rect.min.y and rect.max.y
//  const uint32_t width = spritesheet.getWidth();
//  const uint32_t height = spritesheet.getHeight();
    srcRect.x = rect.min.x;
    srcRect.y = rect.min.y;
  srcRect.w = (rect.max.x - rect.min.x) ;
  srcRect.h = (rect.max.y - rect.min.y) ;
}

inline void SDL::QuadWriter::tileTex(const Sprite::ID id) {
  tileTex(spritesheet.getSprite(id));
}

inline void SDL::QuadWriter::render() const {
  CHECK_SDL_ERROR(SDL_RenderCopyEx(
    renderer.get(), texture.get(), &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE
  ));
}

inline const Sprite::Sheet &SDL::QuadWriter::sheet() const {
  return spritesheet;
}
