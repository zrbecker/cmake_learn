#ifndef GAME_CAT_GAME_LOGIC
#define GAME_CAT_GAME_LOGIC

#include "game_logic.h"
#include <vector>

class CatGameLogic : public GameLogic {
public:
  CatGameLogic();

  virtual void setup(SDLApplication& app) override;
  virtual void cleanup(SDLApplication& app) override {};
  virtual void render(SDLApplication& app, double seconds) override;
  virtual void update(SDLApplication& app, double seconds) override;

private:
  double last_output_;
  double total_seconds_;
  std::vector<int> frame_counts_;
};

#endif  // GAME_CAT_GAME_LOGIC