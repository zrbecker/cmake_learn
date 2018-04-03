#ifndef GAME_CAT_GAME_LOGIC
#define GAME_CAT_GAME_LOGIC

#include <vector>

#include "frame_counter.h"
#include "game_logic.h"

class CatGameLogic : public GameLogic {
public:
  CatGameLogic();

  virtual void setup(SDLApplication& app) override;
  virtual void cleanup(SDLApplication& app) override {};
  virtual void render(
    SDLApplication& app,
    double last_update_seconds,
    double last_frame_seconds
  ) override;
  virtual void update(SDLApplication& app, double last_update_seconds) override;

private:
  FrameCounter update_counter_;
  FrameCounter frame_counter_;
};

#endif  // GAME_CAT_GAME_LOGIC