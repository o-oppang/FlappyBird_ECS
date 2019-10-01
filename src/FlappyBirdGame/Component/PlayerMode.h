//
//  PlayerMode.h
//  EnTT_Pacman
//
//  Created by 심다은 on 29/09/2019.
//

#ifndef PlayerMode_h
#define PlayerMode_h

enum class PlayerModeEnum {
  FlyingMode,
  GroundMode,
  DeadMode,
};

struct PlayerMode
{
    PlayerModeEnum mode;
};

#endif /* PlayerMode_h */
