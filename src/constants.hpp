//
//  constants.hpp
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef CORE_CONSTANTS_HPP
#define CORE_CONSTANTS_HPP

#include <Simpleton/Grid/pos.hpp>
#include <Simpleton/Grid/dir.hpp>

// The width and height of view
constexpr glm::ivec2 viewSize = {144, 256};
// The frame rate. The game speed in set as 8 times slower than the frame rate
constexpr int fps = 20;

#endif
