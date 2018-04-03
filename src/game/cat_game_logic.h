#ifndef GAME_CAT_GAME_LOGIC
#define GAME_CAT_GAME_LOGIC

#include "game_logic.h"

class CatGameLogic : public GameLogic {
  virtual void setup(SDLApplication& app) override;
  virtual void cleanup(SDLApplication& app) override {};
  virtual void render(SDLApplication& app) override {};
};

#endif  // GAME_CAT_GAME_LOGIC